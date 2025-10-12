#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <windows.h>


static void print_hex32(const char *label, DWORD v) {
    printf("  %-24s 0x%08X (%u)\n", label, (unsigned)v, (unsigned)v);
}

static void print_hex16(const char *label, WORD v) {
    printf("  %-24s 0x%04X (%u)\n", label, (unsigned)v, (unsigned)v);
}

static const char* machine_to_string(WORD machine) {
    switch (machine) {
        case IMAGE_FILE_MACHINE_I386:   return "i386";
        case IMAGE_FILE_MACHINE_AMD64:  return "x64";
        case IMAGE_FILE_MACHINE_ARMNT:  return "ARMNT";
        case IMAGE_FILE_MACHINE_ARM64:  return "ARM64";
        default: return "UNKNOWN";
    }
}

void print_dos_header(const IMAGE_DOS_HEADER *dos) {
    printf("=== IMAGE_DOS_HEADER ===\n");
    print_hex16("e_magic", dos->e_magic);
    print_hex32("e_lfanew (offset PE)", (DWORD)dos->e_lfanew);
    printf("\n");
}

void print_file_header(const IMAGE_FILE_HEADER *fh) {
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

void print_optional_header32(const IMAGE_OPTIONAL_HEADER32 *opt) {
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

void print_optional_header64(const IMAGE_OPTIONAL_HEADER64 *opt) {
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

void print_section_headers(const IMAGE_SECTION_HEADER *sections, DWORD numberOfSections) {
    printf("=== SECTION HEADERS (count=%u) ===\n", (unsigned)numberOfSections);
    for (DWORD i = 0; i < numberOfSections; ++i) {
        char name[9] = {0};
        memcpy(name, sections[i].Name, 8);
        printf("  [%2u] %-8s  VA=0x%08X  VSize=0x%08X  RawOff=0x%08X  RawSize=0x%08X  Char=0x%08X\n",
               (unsigned)i,
               name,
               sections[i].VirtualAddress,
               sections[i].Misc.VirtualSize,
               sections[i].PointerToRawData,
               sections[i].SizeOfRawData,
               sections[i].Characteristics);
    }
    printf("\n");
}


void* load_dll_buffer(const char *path, long *out_size) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        perror("fopen");
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char*)malloc((size_t)size);
    if (!buffer) {
        perror("malloc");
        fclose(f);
        return NULL;
    }

    fread(buffer, 1, (size_t)size, f);
    fclose(f);

    if (out_size) *out_size = size;
    return buffer;
}


int main(void) {
    long bufsize = 0;
    const char *path = ".\\bin\\dll_simple.dll";

    unsigned char *buffer = load_dll_buffer(path, &bufsize);
    if (!buffer) {
        fprintf(stderr, "No se pudo cargar %s\n", path);
        return 1;
    }

    const IMAGE_DOS_HEADER *dos = (const IMAGE_DOS_HEADER*)buffer;
    print_dos_header(dos);

    const size_t nt_offset = (size_t)dos->e_lfanew;
    const IMAGE_NT_HEADERS *nt = (const IMAGE_NT_HEADERS*)(buffer + nt_offset);

    printf("=== IMAGE_NT_HEADERS ===\n");
    printf("  Signature: 0x%08X\n\n", nt->Signature);

    const IMAGE_FILE_HEADER *filehdr = &nt->FileHeader;
    print_file_header(filehdr);

    const unsigned char *optional_ptr = (const unsigned char*)&nt->OptionalHeader;
    const WORD optMagic = *(const WORD*)optional_ptr;
    const int is64 = (optMagic == IMAGE_NT_OPTIONAL_HDR64_MAGIC);

    if (is64) {
        const IMAGE_OPTIONAL_HEADER64 *opt64 = (const IMAGE_OPTIONAL_HEADER64*)optional_ptr;
        print_optional_header64(opt64);
    } else {
        const IMAGE_OPTIONAL_HEADER32 *opt32 = (const IMAGE_OPTIONAL_HEADER32*)optional_ptr;
        print_optional_header32(opt32);
    }

    const IMAGE_SECTION_HEADER *sections = (const IMAGE_SECTION_HEADER*)(optional_ptr + filehdr->SizeOfOptionalHeader);
    print_section_headers(sections, filehdr->NumberOfSections);

    free(buffer);
    return 0;
}
