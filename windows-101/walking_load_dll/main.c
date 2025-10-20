#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "headers.h"


void* setup_dll(long *dll_size){
    FILE *f = fopen("./dllmock.dll", "rb"); // Lectura binaria
    if (!f) {
        perror("fopen");
        return NULL;
    }

    fseek(f, 0, SEEK_END);      // Mueve el puntero del fichero
    long size = ftell(f);       // Devuelve la posición actual del puntero
    fseek(f, 0, SEEK_SET);      // Mueve el puntero del fichero al principio

    unsigned char *buffer = malloc(size);   // Reservar memoria en el heap
    if (!buffer) {
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

    printf("DLL cargada en memoria, tamanyo: %ld bytes, direccion: %p\n", size, (void*)buffer);
    *dll_size = size;
    return buffer;
}

int main(void) {
    printf("; ============================================================\n");
    printf(";       MY DLL LOADER (x64)\n");
    printf("; ============================================================\n");
    int resultado = sumar(5, 3);
    
    printf("El resultado es: %d\n", resultado);
    getchar();

    // Cargamos en memoria la dll
    long dll_size = 0;
    void* buffer = setup_dll(&dll_size);

    LPVOID allocated_mem = VirtualAlloc(
        NULL,                          // dirección preferida (NULL = sistema elige)
        dll_size,                      // tamaño en bytes
        MEM_COMMIT | MEM_RESERVE,      // reservar y comprometer
        PAGE_EXECUTE_READWRITE         // permisos (ejecutable + lectura + escritura)
    );

    if (allocated_mem == NULL) {
        printf("VirtualAlloc failed: %u\n", GetLastError());
        return 1;
    }

    printf("Memory allocated at: %p\n", allocated_mem);

    // (cabeceras + secciones + datos)
    
    // import table

    // relocation table

    // call new entry point, DllMain with DLL_PROCESS_ATTACH

    // Cerrar handles sólo cuando existen
    printf("Pulsa ENTER para terminar\n");
    getchar();
    free(buffer);
    return 0;
}