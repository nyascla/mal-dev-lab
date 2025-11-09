[bits 64]

; ============================================================
; DOWNLOADER_STUB (x64)
; ------------------------------------------------------------
; uint64_t multi_import(
;    uint64_t base_module,   ; RCX (hash 64-bit del módulo)
;    uint32_t* ptr_source,   ; RDX (puntero 64-bit a lista de DWORDs)
;    uint64_t* ptr_dest      ; R8  (puntero 64-bit a lista de QWORDs)
; );
; ============================================================


; ---------------------------------------
%include "C:\Users\test\Desktop\mal-dev-lab\101-code\ASM\runtime_linking\x64\x64_exports.asm"
; ---------------------------------------
