global _get_proc_address
global _get_module_handle
global _rol_xor
global _multi_import

section .text

%include "./asm/rol_xor.asm"
%include "./asm/get_proc_address.asm"
%include "./asm/get_module_handle.asm" 
%include "./asm/multi_import.asm" 