global _get_proc_address
global _get_module_handle
global _rol_xor
global _multi_import

section .text

%include "C:\Users\test\Desktop\mal-dev-lab\shellcodes\x86\runtime_linking/asm/rol_xor.asm"
%include "C:\Users\test\Desktop\mal-dev-lab\shellcodes\x86\runtime_linking/asm/get_proc_address.asm"
%include "C:\Users\test\Desktop\mal-dev-lab\shellcodes\x86\runtime_linking/asm/get_module_handle.asm" 
%include "C:\Users\test\Desktop\mal-dev-lab\shellcodes\x86\runtime_linking/asm/imports.asm" 