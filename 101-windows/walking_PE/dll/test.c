#include <stdio.h>
#include <windows.h>

__declspec(dllimport) void ReflectiveLoader(void);

void main(void) {
    ReflectiveLoader();
}
