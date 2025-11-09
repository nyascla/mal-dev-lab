#!/usr/bin/env python3
import subprocess
import argparse
from pathlib import Path
import logging

# --- Configuración ---

# Configura un logger para mostrar mensajes informativos y de error.
logging.basicConfig(level=logging.INFO, format='[%(levelname)s] %(message)s')

# Define la ruta base del proyecto. El script asume que se ejecuta desde su propio directorio.
PROJECT_ROOT = Path(__file__).parent.resolve()

# Ubicación de las herramientas de compilación.
# Se asume que están en el PATH del sistema. Si no, especifica la ruta completa.
# Ejemplo: NASM_EXECUTABLE = Path("C:/path/to/nasm.exe")
NASM_EXECUTABLE = "nasm"
SCLAUNCHER_EXECUTABLE = "sclauncher.exe"

# --- Funciones ---

def run_command(command, cwd):
    """
    Ejecuta un comando en el subproceso y captura errores.
    
    Args:
        command (list): El comando y sus argumentos como una lista.
        cwd (Path): El directorio de trabajo para ejecutar el comando.
    """
    try:
        logging.info(f"Ejecutando: {' '.join(map(str, command))}")
        subprocess.run(command, check=True, cwd=cwd, capture_output=True, text=True)
    except FileNotFoundError:
        logging.error(f"Error: El ejecutable '{command[0]}' no se encontró. Asegúrate de que esté en el PATH.")
        exit(1)
    except subprocess.CalledProcessError as e:
        logging.error(f"Error al ejecutar el comando:\n{e.stderr}")
        exit(1)

def compile_target(architecture, execute=False):
    """
    Compila el shellcode para una arquitectura específica (x86 o x64).

    Args:
        architecture (str): La arquitectura de destino ('x86' o 'x64').
        execute (bool): Si es True, ejecuta el binario compilado.
    """
    logging.info(f"--- Iniciando compilación para {architecture} ---")

    # Define las rutas y nombres de archivo según la arquitectura.
    source_dir = PROJECT_ROOT / architecture
    build_dir = source_dir / "build"
    bin_dir = source_dir / "bin"
    asm_file = source_dir / f"{architecture}_messagebox.asm"
    bin_file = build_dir / f"{architecture}_messagebox.bin"
    exe_file = bin_dir / f"{architecture}_messagebox.exe"

    # Crea los directorios 'build' y 'bin' si no existen.
    build_dir.mkdir(exist_ok=True)
    bin_dir.mkdir(exist_ok=True)
    logging.info(f"Directorios creados/verificados en: {source_dir}")

    # 1. Ensamblar el código ASM a binario con NASM.
    nasm_cmd = [NASM_EXECUTABLE, "-f", "bin", asm_file, "-o", bin_file]
    run_command(nasm_cmd, cwd=PROJECT_ROOT)
    logging.info(f"ASM ensamblado correctamente en: {bin_file}")

    # 2. Convertir el binario a un ejecutable PE con sclauncher.
    sclauncher_cmd = [SCLAUNCHER_EXECUTABLE, f"-f={bin_file}", "-pe", f"-o={exe_file}"]
    if architecture == "x64":
        sclauncher_cmd.insert(3, "-64") # Añade el flag para 64 bits
    
    run_command(sclauncher_cmd, cwd=PROJECT_ROOT)
    logging.info(f"Ejecutable creado correctamente en: {exe_file}")

    # 3. (Opcional) Ejecutar el programa compilado.
    if execute:
        logging.info(f"Ejecutando {exe_file}...")
        run_command([exe_file], cwd=bin_dir)

    logging.info(f"--- Compilación para {architecture} finalizada con éxito ---")

def main():
    """Función principal para parsear argumentos y lanzar la compilación."""
    parser = argparse.ArgumentParser(description="Script de compilación para shellcodes de MessageBox.")
    parser.add_argument("arch", choices=["x86", "x64", "all"], help="La arquitectura a compilar (x86, x64, o all).")
    parser.add_argument("--execute", action="store_true", help="Ejecuta el binario después de compilar.")
    args = parser.parse_args()

    if args.arch == "all":
        compile_target("x86", args.execute)
        compile_target("x64", args.execute)
    else:
        compile_target(args.arch, args.execute)

if __name__ == "__main__":
    main()