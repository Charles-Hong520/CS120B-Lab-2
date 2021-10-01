/*	Author: Charles Hong
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #2  Exercise #3
 *	Exercise Description: Parking sensor 2
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
	DDRC = 0x00; PORTC = 0xFF; // Configure port C's 8 pins as inputs
	DDRD = 0xFF; PORTD = 0x00; // Configure port D's 8 pins as outputs, initialize to 0s
	unsigned char tmpA = 0x00; 
	unsigned char tmpB = 0x00; 
	unsigned char tmpC = 0x00; 
	unsigned char cond1 = 0x00; //exceed 140kg
	unsigned char cond2 = 0x00; //balance |A-C| > 80
	while(1) {
		// 1) Read input
		tmpA = PINA & 0xFF;
		tmpB = PINB & 0xFF;
		tmpC = PINC & 0xFF;

		unsigned short us_total_weight = tmpA+tmpB+tmpC;
		const unsigned short us_max_weight = 140;
		if(us_total_weight > us_max_weight) {
			cond1 = 0x01;
		}

		unsigned char diff = 0x00;
		if(tmpA>tmpC) diff = tmpA-tmpC;
		else diff = tmpC-tmpA;

		if(diff>80) {
			cond2 = 0x02;
		}

		us_total_weight = (us_total_weight>>2) & 0xFC;

		// 2) Perform computation
		PORTD = us_total_weight + cond2 + cond1;
	}
	return 0;
}

