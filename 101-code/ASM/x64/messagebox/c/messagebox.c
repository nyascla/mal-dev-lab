#include <windows.h>

int main() {
    MessageBoxA(
        NULL,                  // Ventana padre (NULL = ninguna)
        "Here !", // Texto del mensaje
        "Title",     // Título de la ventana
        MB_OK | MB_ICONINFORMATION   // Botón OK y icono informativo
    );

    return 0;
}
