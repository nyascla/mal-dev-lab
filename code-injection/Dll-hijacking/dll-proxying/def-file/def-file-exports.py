import pefile

dll = pefile.PE('./real.dll')

print("EXPORTS")
for export in dll.DIRECTORY_ENTRY_EXPORT.symbols:
    if export.name:
        print('{}=real-old.{} @{}'.format(export.name.decode(), export.name.decode(), export.ordinal))