#include <nvboard.h>
#include "Vcode38.h"

void nvboard_bind_all_pins(Vcode38* top) {
	nvboard_bind_pin( &top->i_code, 8, SW7, SW6, SW5, SW4, SW3, SW2, SW1, SW0);
	nvboard_bind_pin( &top->i_en, 1, SW15);
	nvboard_bind_pin( &top->o_code, 3, LD2, LD1, LD0);
	nvboard_bind_pin( &top->o_seg, 8, SEG0A, SEG0B, SEG0C, SEG0D, SEG0E, SEG0F, SEG0G, DEC0P);
	nvboard_bind_pin( &top->o_en_flag, 1, LD15);
}
