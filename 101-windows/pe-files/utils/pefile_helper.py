#!/usr/bin/env python3
import pefile
import os

def get_pe_sections(pe):
    for section in pe.sections:
        print(section.Name, hex(section.VirtualAddress), hex(section.Misc_VirtualSize), section.SizeOfRawData )


def pe_headers(pe):
    print(hex(pe.OPTIONAL_HEADER.AddressOfEntryPoint))
    pe.OPTIONAL_HEADER.ImageBase
    pe.FILE_HEADER.NumberOfSections

    # pe.OPTIONAL_HEADER.AddressOfEntryPoint = 0xdeadbeef
    # pe.write(filename='file_to_write.exe')


def pe_imports(pe):
    # If the PE file was loaded using the fast_load=True argument, we will need to parse the data directories:
    pe.parse_data_directories()

    for entry in pe.DIRECTORY_ENTRY_IMPORT:
        print(entry.dll)
        for imp in entry.imports:
            print('\t', hex(imp.address), imp.name)

def pe_exports(pe):
    for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
        print(hex(pe.OPTIONAL_HEADER.ImageBase + exp.address), exp.name, exp.ordinal)

if __name__ == "__main__":
    path = "./kernel32.dll"
    if not os.path.isfile(path):
        raise FileNotFoundError(f"No existe el fichero: {path}")

    pe = pefile.PE(path, fast_load=False)

    pe_exports(pe)