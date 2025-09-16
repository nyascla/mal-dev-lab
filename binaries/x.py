import subprocess

# Ruta a tu ejecutable
exe_path = r".\main2.exe"

# Número de ejecuciones
runs = 1000

# Guardamos todas las bases
bases = []

for i in range(runs):
    result = subprocess.run([exe_path], capture_output=True, text=True)
    # Extraemos la línea que contiene "Base address"
    for line in result.stdout.splitlines():
        if "Base address" in line:
            bases.append(line.strip())

# Mostramos resultados únicos
unique_bases = sorted(set(bases))
print(f"Total ejecuciones: {runs}")
print(f"Bases únicas encontradas ({len(unique_bases)}):")
for b in unique_bases:
    print(b)
