import pefile

dll = pefile.PE('calibre-launcher.dll')

print("EXPORTS")
for export in dll.DIRECTORY_ENTRY_EXPORT.symbols:
    if export.name:
        print('{}=calibre-launcher-old.{} @{}'.format(export.name.decode(), export.name.decode(), export.ordinal))