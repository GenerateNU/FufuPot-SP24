#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include "hardware/gpio.h"
#include "hardware/vreg.h"
#include "pico/sem.h"


//#include "dvi.h"
//#include "dvi_serialiser.h"
//#include "common_dvi_pin_configs.h"
//#include "sprite.h"


/*
#include "raspberry_128x128_rgab5515.h"
#include "eben_128x128_rgab5515.h"
*/
#define FRAME_WIDTH 400
#define FRAME_HEIGHT 240
#define VREG_VSEL VREG_VOLTAGE_1_20
#define DVI_TIMING dvi_timing_800x480p_60hz


//struct dvi_inst dvi0;

void core1_main() {
	/*
	dvi_register_irqs_this_core(&dvi0, DMA_IRQ_0);
	while (queue_is_empty(&dvi0.q_colour_valid))
		__wfe();
	dvi_start(&dvi0);
	dvi_scanbuf_main_16bpp(&dvi0);
	__builtin_unreachable();
	*/
}


int main() {


}