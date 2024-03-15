#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->a, 4, SW0, SW1, SW2, SW3);
	nvboard_bind_pin( &top->b, 2, SW4, SW5);
	nvboard_bind_pin( &top->f, 1, LD0);
}
