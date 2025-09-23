import pefile

def get_export_offset(dll_path, func_name):
    pe = pefile.PE(dll_path)

    if not hasattr(pe, 'DIRECTORY_ENTRY_EXPORT'):
        print(f"[!] {dll_path} no tiene tabla de exports.")
        return None

    for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
        if exp.name and exp.name.decode() == func_name:
            return exp.address            

    print(f"[!] No se encontró la función {func_name} en {dll_path}")
    return None


if __name__ == "__main__":

    dll_path = ".\\reflective_dll.dll"
    func_name = "ReflectiveLoader"

    offset = get_export_offset(dll_path, func_name)
    
    print(f"Offset de {func_name} en {dll_path}: 0x{offset:X}")

    """
    Ante dudes comprobar con Detect it easy
    """
