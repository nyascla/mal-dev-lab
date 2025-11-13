import pefile

dll = pefile.PE('./bin/real.dll')

print("EXPORTS")
for export in dll.DIRECTORY_ENTRY_EXPORT.symbols:
    if export.name:
        print('{}=og_real.{} @{}'.format(export.name.decode(), export.name.decode(), export.ordinal))