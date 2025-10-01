#include <stdio.h>
#include <windows.h>

__declspec(dllimport) void ReflectiveLoader();


int main() {
    ReflectiveLoader();
    return 0;
}
