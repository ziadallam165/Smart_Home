/*
 * main.c
 *
 *  Created on: Sep 4, 2023
 *      Author: ManDo2020
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "CLCD.h"
#include "UART.h"
#include "TIMER.h"
#include "DIO.h"
#include "GIE.h"
#include "ADC.h"
#include <avr/io.h>
#define F_CPU 8000000
#include "util/delay.h"
#include "STEPPER.h"
#include "EXTI.h"

// Functions Prototypes
void LED_FUN1(void);
void LED_FUN2(void);
void INT0_ISR(void);

u32 count =0;
u8 countt=0;
u8 flag=0;
u16 temp=0;

int main(void)
{

	//Initializing local variables
	u8 PassCode [5] = "1234";
	u8 EnteredData;
	u8 EnteredPass[5];
	u8 Count1 =0;

	// Push Button Initialization
	 DIO_SetPinDirection(DIO_PORTD,DIO_PIN2,DIO_INPUT);
	 DIO_SetPinValue(DIO_PORTD,DIO_PIN2,DIO_HIGH);

	/*Initialization  Motors PINS*/
	DIO_SetPinDirection(DIO_PORTB , DIO_PIN3 , DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTB , DIO_PIN2 , DIO_OUTPUT);

	//making pin7 output (led pin)
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN7,DIO_OUTPUT);

	//making pin5 output (Buzzer pin)
	DIO_SetPinDirection(DIO_PORTB , DIO_PIN5 , DIO_OUTPUT);


	//Initializing lcd + lcd welcome msg
	DIO_SetPortDirection(DIO_PORTC,DIO_OUTPUT);
	/*LCD Control  pins direction*/
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN3,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN4,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT);

	CLCD_voidInit();

	 CLCD_GotoPosition(1,3);
	 CLCD_voidSendString(" HA M ZY ");
	 CLCD_GotoPosition(2,3);
	 CLCD_voidSendString(" SMART HOME <3");
	 _delay_ms(2000);
	 CLCD_voidLCDClear();
	 CLCD_voidSendString(" Enter pass");

	 ADC_voidInit();

	//Initializing usart + checking for password
	UARTInit();
	for(u8 i =0 ; i<3 ; i++)
	{
		USART_voidReceiveString();

		for(u8 j =0 ; j<5 ; j++)
		{
			EnteredPass[j] = GlobalArr[j];
		}
		for(u8 z =0 ;z<5;z++)
		{
			if(EnteredPass[z]==PassCode[z])
			{
				countt++;
			}
		}
		{
		// Continue normally if pass is correct
		}

		if ((EnteredPass[i]!=PassCode[i]))
		{
			//Display on LCD "PASS IS NOT CORRECT"
			Count1++;
			countt=0;
			CLCD_voidLCDClear();
			CLCD_voidSendString(" Pls Try Again");
			if(Count1==3)
			{
				CLCD_voidLCDClear();
				//DISPLAY ON LCD "INTRUDER ALERT"
				CLCD_voidSendString(" Wrong pass");
				DIO_SetPinValue(DIO_PORTB,DIO_PIN5,DIO_HIGH);
				_delay_ms(1000);
				DIO_SetPinValue(DIO_PORTB,DIO_PIN5,DIO_LOW);

				return 0;
				//Dont complete the rest of the code
			}
		}
		if(countt==4)
		{
			CLCD_voidLCDClear();
			CLCD_voidSendString(" Correct Pass");
			CLCD_GotoPosition(2,1);
			CLCD_voidSendString(" Welcome Home");
			break;
		}
	}


	while(1)
	{
		//Interrupt function (emergency button)
		GIE_Enable();
		EXTI_void_Int0Init();
		EXTI_u8Int0SetCallBack(&INT0_ISR);

		_delay_ms(2000);
		//Display options of smart home on LCD
	    //OPTION #1  >> TURN ON / OFF THE LED


		CLCD_voidLCDClear();
		CLCD_GotoPosition(1,1);
		CLCD_voidSendString(" Pls enter 1 to");
		CLCD_GotoPosition(2,1);
		CLCD_voidSendString(" CONTROL THE LED");
		
		//OPTION #2  >> CONTROL THE TEMPERATURE
		_delay_ms(2000);
		CLCD_voidLCDClear();
		CLCD_GotoPosition(1,1);
		CLCD_voidSendString(" Pls enter 2 to");
		CLCD_GotoPosition(2,1);
		CLCD_voidSendString(" CONTROL THE TEMP");
		
		//OPTION #3  >> OPEN / CLOSE THE DOOR
		_delay_ms(2000);
		CLCD_voidLCDClear();
		CLCD_GotoPosition(1,1);
		CLCD_voidSendString(" Pls enter 3 to");
		CLCD_GotoPosition(2,1);
		CLCD_voidSendString(" OPEN/CLOSE DOOR");
		
		//OPTION #4  >> REPEAT DISPLAYING THE OPTIONS
		_delay_ms(2000);
		CLCD_voidLCDClear();
		CLCD_GotoPosition(1,1);
		CLCD_voidSendString(" Pls enter 4 to");
		CLCD_GotoPosition(2,1);
		CLCD_voidSendString(" REPEAT");
		
		EnteredData = USART_RecieveData();


		if(EnteredData=='1') //Open Led For certain time (2 options 10 sec or  1 min)
		{
			//ask for how long to turn on
				CLCD_voidLCDClear();
				CLCD_voidSendString(" 1:FOR 60s");
				CLCD_GotoPosition(2,1);
				CLCD_voidSendString(" 2:FOR 10s");
				_delay_ms(2000);
			EnteredData = USART_RecieveData();
			if(EnteredData=='1') //if for 60 sec
			{
				DIO_SetPinValue(DIO_PORTD,DIO_PIN7,DIO_HIGH);
				GIE_Enable();
				TIMER0_Init();
				TIMER0_u8SetCallBack(&LED_FUN1);
			}
			else if (EnteredData=='2') //if for 10 sec
			{
				DIO_SetPinValue(DIO_PORTD,DIO_PIN7,DIO_HIGH);
				GIE_Enable();
				TIMER0_Init();
				TIMER0_u8SetCallBack(&LED_FUN2);
			}
			else
			{
				//Display error code on lcd and do nothing
				CLCD_voidLCDClear();
				CLCD_voidSendString(" Invalid Value");
			}



			}

		else if (EnteredData == '2') // Temp Control
		{
			CLCD_voidLCDClear();
			temp = ((ADC_u8GetChannelReading(ADC0_PIN)*7.99)/1023);
			CLCD_GotoPosition(1,1);
			CLCD_voidSendString(" Temp is :  ");
			CLCD_GotoPosition(1,10);
			CLCD_voidDisplayInteger(temp);
			CLCD_GotoPosition(1,13);
			CLCD_voidSendData('C');

			if(temp > 25)
			{
				DIO_SetPinValue(DIO_PORTB , DIO_PIN2 , DIO_HIGH);
				DIO_SetPinValue(DIO_PORTB , DIO_PIN3 , DIO_LOW);
			}
			else if(temp <= 25)
			{
				DIO_SetPinValue(DIO_PORTB , DIO_PIN2 , DIO_LOW);
				DIO_SetPinValue(DIO_PORTB , DIO_PIN3 , DIO_HIGH);
			}


	    }

		else if (EnteredData=='3') // Open or close door
		{
			//messages to display <3
			CLCD_voidLCDClear();
		    CLCD_voidSendString(" 1:TO OPEN DOOR");
		    CLCD_GotoPosition(2,1);
		    CLCD_voidSendString(" 2:TO CLOSE DOOR");

		    u8 value =USART_RecieveData();


		    if (value == '1' )
		    {
		    	if (flag==0)
		    	{
		    	//open the door
		    	Stepper_Init();
		    	Stepper_Open_90deg();
		    	flag=1;
		    	}
		    	else
		    	{
		    		//the door is already opened so we don't have to open it
			    	CLCD_voidLCDClear();
			    	CLCD_voidSendString(" Door is open");
				}
			}

			else if (value =='2')
			{
				if (flag==1)
				{
				//close door
				Stepper_Init();
				Stepper_Close_door();
				flag=0;
			    }
			    else
			    {
				//the door is already closed
			    	CLCD_voidLCDClear();
			    	CLCD_voidSendString(" Door is closed");
			    }
			}
			else
			{
				CLCD_voidLCDClear();
				CLCD_voidSendString(" Invalid Value");
			}

		}

		else if (EnteredData=='4') // Repeat Options For User
		{
		}

		else
		{
			//Display Invalid Value And Repeat the whole process
			CLCD_voidLCDClear();
			CLCD_voidSendString(" Invalid value");
			CLCD_GotoPosition(2,1);
			CLCD_voidSendString(" Pls Try Again");
			_delay_ms(1000);
		}

	}

	return 0;
}

void LED_FUN1(void)
{
	count++;
	if(count==1831)
	{
		count=0;
		DIO_SetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
		GIE_Disable();
	}
}

void LED_FUN2(void)
{

	count++;
		if(count==305)
		{
			count=0;
			DIO_SetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
			GIE_Disable();
			_delay_ms(1000);
		}
}

void INT0_ISR(void)
{

	if(DIO_GetPinValue(DIO_PORTD , DIO_PIN2) == 0 )
	{

		  DIO_SetPinDirection(DIO_PORTD,DIO_PIN6,DIO_OUTPUT);
		  DIO_SetPinValue(DIO_PORTD,DIO_PIN6,DIO_HIGH);
		  _delay_ms(5000);
		  DIO_SetPinValue(DIO_PORTD,DIO_PIN6,DIO_LOW);
	}
}
