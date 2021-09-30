/*	Author: Charles Hong
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #2  Exercise #2
 *	Exercise Description: Parking sensor
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
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
//	unsigned char tmpC = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
while(1) {
		// 1) Read input
		tmpA = PINA & 0x0F; //read in A3 A2 A1 and A0
		// 2) Perform computation
		// count the 0's from A3-A0
		unsigned char taken = 0;
		for(unsigned char i = 0; i < 4; i++) {
			if((tmpA&0x01) == 0x01) {
				taken++;
			}
			tmpA = tmpA>>1;
		}
		
	// 3) Write output
	PORTC = 4-taken;
	}
	return 0;
}

