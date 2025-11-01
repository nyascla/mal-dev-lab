#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h> // Para size_t
#include <inttypes.h> // <-- La biblioteca de formatos
#include <windows.h>

static void print_hex32(const char *label, DWORD v)
{
    printf("  %-24s 0x%08X (%u)\n", label, (unsigned)v, (unsigned)v);
}

static void print_hex16(const char *label, WORD v)
{
    printf("  %-24s 0x%04X (%u)\n", label, (unsigned)v, (unsigned)v);
}

static const char *machine_to_string(WORD machine)
{
    switch (machine)
    {
    case IMAGE_FILE_MACHINE_I386:
        return "i386";
    case IMAGE_FILE_MACHINE_AMD64:
        return "x64";
    case IMAGE_FILE_MACHINE_ARMNT:
        return "ARMNT";
    case IMAGE_FILE_MACHINE_ARM64:
        return "ARM64";
    default:
        return "UNKNOWN";
    }
}

void print_dos_header(const IMAGE_DOS_HEADER *dos)
{
    printf("=== IMAGE_DOS_HEADER ===\n");
    print_hex16("e_magic", dos->e_magic);
    print_hex32("e_lfanew (offset PE)", (DWORD)dos->e_lfanew);
    printf("\n");
}

void print_file_header(const IMAGE_FILE_HEADER *fh)
{
    printf("=== IMAGE_FILE_HEADER ===\n");
    printf("  %-24s 0x%04X (%s)\n", "Machine", fh->Machine, machine_to_string(fh->Machine));
    print_hex16("NumberOfSections", fh->NumberOfSections);
    print_hex32("TimeDateStamp", fh->TimeDateStamp);
    print_hex32("PointerToSymbolTable", fh->PointerToSymbolTable);
    print_hex32("NumberOfSymbols", fh->NumberOfSymbols);
    print_hex16("SizeOfOptionalHeader", fh->SizeOfOptionalHeader);
    print_hex16("Characteristics", fh->Characteristics);
    printf("\n");
}

void print_optional_header32(const IMAGE_OPTIONAL_HEADER32 *opt)
{
    printf("=== IMAGE_OPTIONAL_HEADER32 (PE32) ===\n");
    print_hex16("Magic", opt->Magic);
    print_hex32("AddressOfEntryPoint", opt->AddressOfEntryPoint);
    print_hex32("ImageBase", opt->ImageBase);
    print_hex32("SectionAlignment", opt->SectionAlignment);
    print_hex32("FileAlignment", opt->FileAlignment);
    print_hex32("SizeOfImage", opt->SizeOfImage);
    print_hex32("SizeOfHeaders", opt->SizeOfHeaders);
    print_hex32("CheckSum", opt->CheckSum);
    print_hex16("Subsystem", opt->Subsystem);
    print_hex32("NumberOfRvaAndSizes", opt->NumberOfRvaAndSizes);
    printf("\n");
}

void print_optional_header64(const IMAGE_OPTIONAL_HEADER64 *opt)
{
    printf("=== IMAGE_OPTIONAL_HEADER64 (PE32+) ===\n");
    print_hex16("Magic", opt->Magic);
    printf("  %-24s 0x%016llX\n", "ImageBase", (unsigned long long)opt->ImageBase);
    print_hex32("AddressOfEntryPoint", opt->AddressOfEntryPoint);
    print_hex32("SectionAlignment", opt->SectionAlignment);
    print_hex32("FileAlignment", opt->FileAlignment);
    print_hex32("SizeOfImage", opt->SizeOfImage);
    print_hex32("SizeOfHeaders", opt->SizeOfHeaders);
    print_hex32("CheckSum", opt->CheckSum);
    print_hex16("Subsystem", opt->Subsystem);
    print_hex32("NumberOfRvaAndSizes", opt->NumberOfRvaAndSizes);
    printf("\n");
}

void print_section_headers(const IMAGE_SECTION_HEADER *sections, DWORD numberOfSections)
{
    printf("=== SECTION HEADERS (count=%u) ===\n", (unsigned)numberOfSections);
    for (DWORD i = 0; i < numberOfSections; ++i)
    {
        char name[9] = {0};
        memcpy(name, sections[i].Name, 8);
        printf("  [%2u] %-8s  VirtualSize=0x%08X  VirtualAddress=0x%08X  SizeOfRawData=0x%08X  PointerToRawData=0x%08X  Characteristics=0x%08X\n",
                (unsigned)i,
                name,
                sections[i].Misc.VirtualSize,
                sections[i].VirtualAddress,
                sections[i].SizeOfRawData,
                sections[i].PointerToRawData,
                sections[i].Characteristics);
    }
    printf("\n");
}

void print_export_directory(const DWORD rva_to_eat) {
    printf("=== IMAGE_EXPORT_DIRECTORY ===\n");
    print_hex32("RVA to Export Address Table", rva_to_eat);

    printf("\n");
}

void print_import_descriptors(DWORD rva_to_iat) {    
    printf("=== IMAGE_IMPORT_DESCRIPTOR (.idata) ===\n");
    print_hex32("RVA to Import Address Table", rva_to_iat);
 
    printf("\n");
}

void print_relocations(DWORD rva_to_reloc)
{
    printf("=== RELOCATION TABLE (.reloc) ===\n");
    print_hex32("RVA to Relocation Table", rva_to_reloc);

    printf("\n");
}

void *load_dll_buffer()
{
    const char *path = ".\\bin\\dllmock.dll";

    FILE *f = fopen(path, "rb");
    if (!f)
    {
        perror("fopen");
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc((size_t)size);
    if (!buffer)
    {
        perror("malloc");
        fclose(f);
        return NULL;
    }

    fread(buffer, 1, (size_t)size, f);
    fclose(f);

    return buffer;
}

int main(void)
{
    printf("; ============================================================ \n");
    printf(";       WALKING PE FILE (x64)\n");
    printf("; ============================================================ \n");

    // unsigned char *buffer = load_dll_buffer();

    const char *kernel32 = "kernel32.dll";
    HMODULE module_handle = LoadLibraryA(kernel32);
    unsigned char *buffer = (unsigned char*)module_handle;


    if (!buffer) {return 1;}

    const IMAGE_DOS_HEADER *dos = (const IMAGE_DOS_HEADER *)buffer;
    const IMAGE_NT_HEADERS64 *nt = (const IMAGE_NT_HEADERS64 *)(buffer + dos->e_lfanew);
    const IMAGE_FILE_HEADER *filehdr = &nt->FileHeader;
    const IMAGE_OPTIONAL_HEADER64 *opt64 = &nt->OptionalHeader;
    const DWORD *rva_to_eat = opt64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    const DWORD *rva_to_iat = opt64->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
    const DWORD *rva_to_reloc = opt64->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
    const IMAGE_SECTION_HEADER *sections = IMAGE_FIRST_SECTION(nt);

    // ------------------------------------------------------------
    // Comprobar arquitectura
    if (filehdr->Machine != IMAGE_FILE_MACHINE_AMD64) {
        printf("Arquitectura detectada: %s (0x%X)\n", machine_to_string(filehdr->Machine), filehdr->Machine);
        free(buffer);
        return 1;
    }

    // ------------------------------------------------------------
    // Printing zone edata
    printf("=== BASE %p=== \n\n", buffer);
    print_dos_header(dos);
    print_file_header(filehdr);
    print_optional_header64(opt64);
    print_section_headers(sections, filehdr->NumberOfSections);
    // La informacion esta en sus respectivas seccioens no en el header
    print_export_directory(rva_to_eat);    // .edata  
    print_import_descriptors(rva_to_iat);  // .idata
    print_relocations(rva_to_reloc);       // .reloc 

    free(buffer);
    return 0;
}
