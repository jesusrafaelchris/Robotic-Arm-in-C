#include "librobot.h"

void init_button_sensor(void){
	/* --------------- Begin Answer to Task 1a Here ------------ */
    // Make port 7 input
    DDRB &= 0b00000000;
    // enable pull-up resistor on port 7
    PORTB |= 0b10000000;
	/* --------------- End Answer to Task 1a Here -------------- */
	return;
}

int read_button_sensor(void){
	int pressed;
	/* --------------- Begin Answer to Task 1b Here ------------ */
    //Read the state of pin 10
    
    //0 if pressed, 1 if otherwise
    if (PIND & 0b10000000) {
        pressed = 0;
    }
    else {
        pressed = 1;
    }

	/* --------------- End Answer to Task 1b Here -------------- */
	return pressed;
}

float read_knob_sensor(int knob){
	float reading = 0; /* Sensor reading, normalised
						  (i.e., scaled) to be between 
						  zero and one. */
	/* --------------- Begin Answer to Task 2 Here ------------ */
    //ADC0 is Analogue 0
    //ADC1 is Analogue 1 PORTC
    
    //Set all analoue pins to input
    DDRC = 0x00;
    
    
    if (knob == 0) {
        //Read from ADC0
        ADMUX &= ~(1<<MUX0); //clear register
        ADMUX |= (0<<MUX0);
    }
    else if (knob == 1) {
        //Read from ADC1
        ADMUX &= ~(0<<MUX0); //clear register
        ADMUX |= (1<<MUX0);
    }
    
    //Switch on ADC
    ADCSRA |= (1<<ADSC);
    
    //wait for it
    while(ADCSRA & (1 << ADSC));
    reading = (float)ADCH/(255); //scales between 0 and 1

	/* --------------- End Answer to Task 2 Here -------------- */
	return reading;
}


void init_arm_motors(void) {
	/* --------------- Begin Answer to Task 3 Here ------------ */
    
    //PB1 is port 9
    //PB2 is port 10
    //Set as output
    DDRB |= (1<<PB1);
    DDRB |= (1<<PB2);
    
    // set non-inverting mode
    TCCR1A |= (1<<COM1A1) | (1<<COM1B1);
    
    // fast PWM Mode
    TCCR1A |= TCCR1A | (1<<WGM11);
    
    // set pre-scaler to 8 and starts PWM
    TCCR1B |= (1<<WGM12) | (1<<WGM13);
    
    TCCR1B |= (0<<CS10) | (1<<CS11);
    
    // set time period to 20ms
    //ICS0A = 4999;
    ICR1 = 40000; //resolution = 0.5us

	/* --------------- End Answer to Task 3 Here -------------- */
	return;
}


