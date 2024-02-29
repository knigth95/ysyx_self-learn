typedef struct{
    union{
        union{
            uint32_t _32;
            uint16_t _16;
            uint8_t _8[2];
        }gpr[8];
        struct{
        	uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
        };
    };
    uint32_t eip;
}CPU_state;