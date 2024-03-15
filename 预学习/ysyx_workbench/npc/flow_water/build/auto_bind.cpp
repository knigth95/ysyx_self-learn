#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->led, 8, LD14, LD12, LD10, LD8, LD6, LD4, LD2, LD0);
}
