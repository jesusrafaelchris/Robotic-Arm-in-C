#include "librobot.h"

int main(void) {
	init_button_sensor();
	init_knob_sensors();
	init_arm_motors();
	init_gripper_motor();

    while (1)
    {
		write_arm_motors(read_knob_sensor(0),read_knob_sensor(1));
		write_gripper_motor(read_button_sensor());
	}

   return 0;
}


