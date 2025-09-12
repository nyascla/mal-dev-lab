#!/usr/bin/env python3
"""
Hash generator for DLL module names and WinAPI function names.
"""

from typing import Union


def rol(val: int, r_bits: int, max_bits: int) -> int:
    """Rotate bits left (circular shift)."""
    mask = (1 << max_bits) - 1         # Ej: 32 bits -> 0xFFFFFFFF
    r_bits %= max_bits                 # Aseguramos que no exceda max_bits

    left = (val << r_bits) & mask      # Desplaza a la izquierda y aplica máscara
    right = (val >> (max_bits - r_bits)) & mask  # Parte que se "recicla"
    
    return left | right


def create_hash(export_name: str) -> int:
    """Creates a hash from a WinAPI function name"""
    result = 0
    print(f"== Creando hash para '{export_name}' ==")
    
    for i, ch in enumerate(export_name.lower()):
        before = result
        result = rol(result, 7, 32)
        after_rol = result
        result ^= ord(ch)
        
        print(f"[{i}] char='{ch}' ascii={ord(ch)} "
              f"before=0x{before:08X} "
              f"after_rol=0x{after_rol:08X} "
              f"result=0x{result:08X}")
    
    print(f"== Hash final: 0x{result:08X} ==")
    return result


def main(module_name: str, api_name: str) -> None:
    """Main entry point: prints module and API hashes."""
    module_hash = create_hash(module_name)    
    api_hash = create_hash(api_name)

    print(f"[+] Module: {module_name} -> {hex(module_hash)}")
    print(f"[+] API: {api_name} -> {hex(api_hash)}")


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(
        description="Generate custom hashes for DLL and WinAPI names."
    )
    parser.add_argument("module", help="Name of the DLL module (e.g., kernel32.dll)")
    parser.add_argument("api", help="Name of the WinAPI function (e.g., LoadLibraryA)")

    args = parser.parse_args()

    main(args.module, args.api)

# [+] Module: kernel32.dll -> 0x4b1ffe8e
# [+] API: LoadLibraryA -> 0xc8ac8026