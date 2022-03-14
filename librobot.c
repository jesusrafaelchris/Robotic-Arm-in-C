#include "librobot.h"

void init_gripper_motor(void) {
	DDRD  = (1<<PD5);                   /* Set PORTD pin 6 as output. */

	/* Set up timer0 to used phase-correct PWM to control the gripper motor. */
	TCCR0A = (0<<WGM01) | (1<<WGM00);   /* Set the waveform generation mode. */
	TCCR0B = (1<<WGM02);               

	TCCR0A |= (1<<COM0B1) | (0<<COM0B0);/* Set the compare mode. */ 

	TCCR0B |= (1<<CS02) | (1<<CS00);    /* Select the clock source. */

	OCR0A = OCR0_TOP;                   /* Set TOP. */

	return;
}

void init_knob_sensors(void){
   ADMUX = (1<<REFS0) | (1<<ADLAR); /* Set up ADMUX to use left-justified data
									   representation with AVCC as reference */

   ADCSRA = (1<<ADEN) | (1<<ADPS2)| (1<<ADPS1) | (1<<ADPS0); /* Enable the ADC and 
																set the prescaler */
   return;
}

void write_arm_motors(float motor0, float motor1){
	OCR1A = OCR1_GAIN*motor0+OCR1_MIN; /* Write commands to motors. */
	OCR1B = OCR1_GAIN*motor1+OCR1_MIN;
	return;
}

void write_gripper_motor(int open){
	if( open ) /* If open gripper signal detected, send open command. */
		OCR0B = OCR0_OPEN;
	else       /* Otherwise, send close command */
		OCR0B = OCR0_CLOSE;

	return;
}
