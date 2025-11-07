global _get_proc_address
global _get_module_handle
global _rol_xor
global _multi_import

section .text

%include "C:\Users\test\Desktop\mal-dev-lab\101-code\ASM\runtime_linking\x86\rol_xor.asm"
%include "C:\Users\test\Desktop\mal-dev-lab\101-code\ASM\runtime_linking\x86\get_proc_address.asm"
%include "C:\Users\test\Desktop\mal-dev-lab\101-code\ASM\runtime_linking\x86\get_module_handle.asm" 
%include "C:\Users\test\Desktop\mal-dev-lab\101-code\ASM\runtime_linking\x86\imports.asm" 