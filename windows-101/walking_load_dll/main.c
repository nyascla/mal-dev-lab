#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "headers.h"

void *setup_dll(long *dll_size)
{
    FILE *f = fopen("./dllmock.dll", "rb"); // Lectura binaria
    if (!f)
    {
        perror("fopen");
        return NULL;
    }

    fseek(f, 0, SEEK_END); // Mueve el puntero del fichero
    long size = ftell(f);  // Devuelve la posición actual del puntero
    fseek(f, 0, SEEK_SET); // Mueve el puntero del fichero al principio

    unsigned char *buffer = malloc(size); // Reservar memoria en el heap
    if (!buffer)
    {
        perror("malloc");
        fclose(f);
        return NULL;
    }

    fread(
        buffer, // Dirección de memoria donde se almacenarán los bytes leídos del archivo
        1,      // Tamaño de cada elemento a leer en bytes (1 byte por elemento)
        size,   // Número de elementos a leer (en total se leerán 'size' bytes)
        f       // Puntero al archivo abierto desde el que se leerán los datos
    );

    fclose(f);

    printf("DLL cargada en memoria, tamanyo: %ld bytes, direccion: %p\n", size, (void *)buffer);
    *dll_size = size;
    return buffer;
}

int main(void)
{
    printf("; ============================================================\n");
    printf(";       MY DLL LOADER (x64)\n");
    printf("; ============================================================\n");
    
    // Cargamos en memoria la dll
    long dll_size = 0;
    void *buffer = setup_dll(&dll_size);

    show_dll_info(buffer, dll_size);

    // ------------------------------------------------------------
    // Reservar memoria en el proceso para la DLL (SizeOfImage)


    LPVOID allocated_mem = VirtualAlloc(
        NULL,                     // dirección preferida (NULL = sistema elige)
        dll_size,                 // tamaño en bytes
        MEM_COMMIT | MEM_RESERVE, // reservar y comprometer
        PAGE_EXECUTE_READWRITE    // permisos (ejecutable + lectura + escritura)
    );

    if (allocated_mem == NULL)
    {
        printf("VirtualAlloc failed: %u\n", GetLastError());
        return 1;
    }

    printf("Memory allocated at: %p\n", allocated_mem);

    // ------------------------------------------------------------
    // Copiar cabeceras PE (SizeOfHeaders)


    // ------------------------------------------------------------
    // Mapear las Secciones
    //      - Destino: destino = ImageBase + section[i].VirtualAddress
    //      - Origen: origen = BufferDelArchivo + section[i].PointerToRawData
    //      - Tamaño: tamaño = section[i].SizeOfRawData
    // .bss (o si PointerToRawData es 0), no copiar. En su lugar, usa memset(destino, 0, section[i].VirtualSize) para llenar esa sección de ceros.

    // ------------------------------------------------------------
    // Relocaciones
    //      - Calcular Delta: delta = NuevaImageBase - ImageBaseOriginal
    //      - Buscar Tabla .reloc: Encuentra la sección .reloc que acabas de mapear.
    //      - Iterar: Recorre esta tabla (que es una serie de bloques) y "parchea" cada dirección absoluta en tu código (.text, .data) sumándole el delta.

    // ------------------------------------------------------------
    // Importaciones
    //      - Buscar Tabla .idata: Encuentra la sección .idata que mapeaste.
    //      - Iterar (DLLs): Recorre la tabla. Verás los nombres de las DLLs que necesita (ej. "user32.dll", "kernel32.dll").
    //      - Llamar a LoadLibraryA: Llama a LoadLibraryA (ej. LoadLibraryA("user32.dll")) para cada una.
    //      - Iterar (Funciones): Dentro de cada DLL, recorre la lista de funciones que necesita (ej. "MessageBoxA").
    //      - Llamar a GetProcAddress: Llama a GetProcAddress (ej. GetProcAddress(hUser32, "MessageBoxA")).
    //      - Parchear la IAT: Escribe la dirección de la función devuelta en la Tabla de Direcciones de Importación (IAT) de tu DLL (que también está en la sección .idata).

    // ------------------------------------------------------------
    // call new entry point, DllMain with DLL_PROCESS_ATTACH
    //      - ImageBase + AddressOfEntryPoint


    // Cerrar handles sólo cuando existen
    printf("Pulsa ENTER para terminar\n");
    getchar();
    free(buffer);
    return 0;
}