#include <cstdint>
#include <stdio.h>

typedef struct{
    union{
        union{
            uint32_t _32;//AL,DL,CL,BL,AH,DH,CH,BH
            uint16_t _16;//AX,DX,CX,BX,BP,SI,DI,SP
            uint8_t _8[2];
        }gpr[8];
        struct{
            //定义32为寄存器
        	uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
        };
    };
    uint32_t eip;//32位程序计数器
}CPU_state;
