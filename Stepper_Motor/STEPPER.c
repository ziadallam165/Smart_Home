
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "avr/io.h"
#include "util/delay.h"
#include "STEPPER.h"



void Stepper_Init(void){
	
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN4,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN5,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN6,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN7,DIO_OUTPUT);
	
	
}

void Stepper_Open_90deg(void){
	
		DIO_SetPinValue(DIO_PORTA, DIO_PIN4, DIO_LOW);
		DIO_SetPinValue(DIO_PORTA, DIO_PIN6, DIO_LOW);
		DIO_SetPinValue(DIO_PORTA, DIO_PIN7, DIO_LOW);
		DIO_SetPinValue(DIO_PORTA, DIO_PIN5, DIO_HIGH);
		
		DIO_SetPinValue(DIO_PORTA, DIO_PIN4, DIO_LOW);
		DIO_SetPinValue(DIO_PORTA, DIO_PIN6, DIO_HIGH);
		DIO_SetPinValue(DIO_PORTA, DIO_PIN7, DIO_LOW);
		DIO_SetPinValue(DIO_PORTA, DIO_PIN5, DIO_HIGH);

		_delay_ms(100);	
	
}
void Stepper_Close_door(void){
		
		DIO_SetPinValue(DIO_PORTA, DIO_PIN4, DIO_HIGH);
		DIO_SetPinValue(DIO_PORTA, DIO_PIN5, DIO_HIGH);
		DIO_SetPinValue(DIO_PORTA, DIO_PIN7, DIO_LOW);
		DIO_SetPinValue(DIO_PORTA, DIO_PIN6, DIO_LOW);

		_delay_ms(100);
	
}
