# Protecciones

## Generales
- **ASLR**: aleatoriza direcciones
- **NX / DEP**: evita ejecución en zonas de datos

## Stack (Buffer Overflow)
- **Stack canaries**: detectan corrupción antes de `return`
- **CFI**: protege el flujo de ejecución

## Heap (Heap Overflow)
- **Heap metadata protections**: checks internos del allocator
- **Safe unlinking / tcache**: mitigan exploits clásicos
- **Hardened allocators** (jemalloc, hardened malloc)