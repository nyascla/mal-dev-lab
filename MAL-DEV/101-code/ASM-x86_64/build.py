#!/usr/bin/env python3
import subprocess
import argparse
from pathlib import Path
import logging
import os

# --- Configuración ---
logging.basicConfig(level=logging.INFO, format='[%(levelname)s] %(message)s', encoding='utf-8')

# --- Constantes ---
PROJECT_ROOT = Path(__file__).parent.resolve()
NASM_EXECUTABLE = "C:\\Users\\test\\AppData\\Local\\bin\\NASM\\nasm.exe"
SCLAUNCHER_EXECUTABLE = "C:\\Users\\test\\Desktop\\win\\sclauncher-main\\sclauncher-main\\sclauncher.exe"


# --- Funciones ---

def run_command(command, cwd):
    """
    Ejecuta un comando en el subproceso, pero redirige su salida a NUL.
    """
    try:
        cmd_str_list = [str(item) for item in command]
        logging.info(f"Ejecutando en '{cwd}': {' '.join(cmd_str_list)}")
        
        subprocess.run(
            cmd_str_list, 
            check=True, 
            cwd=cwd, 
            text=True,
            stdout=subprocess.PIPE,  # <-- CAMBIO: Captura stdout
            stderr=subprocess.PIPE   # <-- CAMBIO: Captura stderr
        )
        
    except FileNotFoundError:
        logging.error(f"Error: El ejecutable '{command[0]}' no se encontró en la ruta especificada.")
        exit(1)
    except subprocess.CalledProcessError as e:
        # Si falla, imprimimos el error que capturamos
        logging.error(f"Error al ejecutar el comando. Código de retorno: {e.returncode}")
        if e.stdout:
            logging.error(f"STDOUT:\n{e.stdout}")
        if e.stderr:
            logging.error(f"STDERR:\n{e.stderr}")
        exit(1)
    except Exception as e:
        logging.error(f"Error inesperado: {e}")
        exit(1)


def convert_bin_to_c_array(bin_file_path, c_file_path, array_name="shellcode"):
    """
    Lee un archivo binario (.bin) y lo convierte en un archivo de cabecera (.h)
    que contiene un array 'unsigned char[]' de C.
    """
    try:
        with open(bin_file_path, 'rb') as f_bin:
            data = f_bin.read()
    except FileNotFoundError:
        logging.error(f"Error: No se pudo encontrar el archivo binario: {bin_file_path}")
        return False

    # Generar el contenido del header
    c_content = f"// Archivo generado automáticamente. No editar.\n\n"
    c_content += f"unsigned char {array_name}[] = {{\n    "
    
    line_count = 0
    for byte in data:
        # Formatea cada byte como hex de 2 dígitos (ej: 0x0A)
        c_content += f"0x{byte:02x}, "
        line_count += 1
        if line_count % 12 == 0: # Salto de línea cada 12 bytes
            c_content += "\n    "
    
    # Quitar la última coma y espacio si el archivo no está vacío
    if data:
        c_content = c_content.rstrip(", ")

    # Añade el cierre del array y la variable de tamaño
    c_content += f"\n}};\n\nunsigned int {array_name}_len = {len(data)};\n"

    # Escribir el archivo .h
    try:
        with open(c_file_path, 'w', encoding='utf-8') as f_c:
            f_c.write(c_content)
        logging.info(f"Array de C guardado en: {c_file_path}")
        return True
    except IOError as e:
        logging.error(f"Error al escribir el archivo de C: {e}")
        return False


def compile_target(architecture, project_name, execute=False):
    """
    Compila el shellcode para una arquitectura específica (x86 o x64).
    """
    logging.info(f"--- Iniciando compilación para {project_name} [{architecture}] ---")

    # Define las rutas y nombres de archivo.
    source_dir = PROJECT_ROOT / project_name / architecture
    build_dir = source_dir / "build"
    bin_dir = source_dir / "bin"
    
    asm_file = source_dir / f"{project_name}.asm"
    bin_file = build_dir / f"{project_name}.bin"
    exe_file = bin_dir / f"{project_name}.exe"
    
    # --- (NUEVO) Ruta para el archivo .h ---
    c_array_file = build_dir / f"{project_name}.h"
    c_array_var_name = f"{project_name}_{architecture}" # ej: messagebox_x64

    # Crea los directorios 'build' y 'bin' si no existen.
    build_dir.mkdir(exist_ok=True)
    bin_dir.mkdir(exist_ok=True)

    # 1. Ensamblar el código ASM a binario con NASM.
    nasm_cmd = [NASM_EXECUTABLE, "-f", "bin", asm_file, "-o", bin_file]
    run_command(nasm_cmd, cwd=PROJECT_ROOT)
    logging.info(f"ASM ensamblado correctamente en: {bin_file}")

    # --- (NUEVO PASO 2) ---
    # 2. Convertir el .bin a un array de C (.h)
    if not convert_bin_to_c_array(bin_file, c_array_file, c_array_var_name):
        logging.error("Fallo al convertir el binario a array de C.")
        exit(1)
    
    # 3. Convertir el binario a un ejecutable PE con sclauncher.
    sclauncher_cmd = [
        SCLAUNCHER_EXECUTABLE,
        f"-f={bin_file}",
        "-pe"
    ]
    if architecture == "x64":
        sclauncher_cmd.append("-64")
    
    sclauncher_cmd.append(f"-o={exe_file}")
        
    run_command(sclauncher_cmd, cwd=PROJECT_ROOT)
    logging.info(f"Ejecutable creado correctamente en: {exe_file}")

    # 4. (Opcional) Ejecutar el programa compilado.
    if execute:
        logging.info(f"Ejecutando {exe_file}...")
        try:
            os.startfile(exe_file)
        except OSError as e:
            logging.error(f"No se pudo ejecutar el archivo {exe_file}: {e}")

    logging.info(f"--- Compilación para [{architecture}] finalizada con éxito ---")

def main():
    """Función principal para parsear argumentos y lanzar la compilación."""
    
    parser = argparse.ArgumentParser(
        description="Script de compilación para proyectos de ASM a PE.",
        formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument(
        "project_name", 
        help="Nombre de la carpeta del proyecto a compilar (ej: messagebox)."
    )
    parser.add_argument(
        "-a", "--arch", 
        choices=['x86', 'x64', 'all'], 
        default='all', 
        help="Arquitectura a compilar. 'all' compila ambas (default: 'all')."
    )
    parser.add_argument(
        "-e", "--execute", 
        action="store_true", 
        help="Ejecuta el binario tras la compilación."
    )
    
    args = parser.parse_args()

    try:
        logging.info(f"\n\n=== Build del proyecto '{args.project_name}' iniciando... === \n\n")

        if args.arch == 'all':
            compile_target("x86", args.project_name, args.execute)
            compile_target("x64", args.project_name, args.execute)
        else:
            compile_target(args.arch, args.project_name, args.execute)
            
        logging.info(f"=== Build del proyecto '{args.project_name}' completado. ===")
        
    except Exception as e:
        logging.error(f"Ha ocurrido un error inesperado: {e}")
        exit(1)

if __name__ == "__main__":
    main()