/*Preprocessor file guard*/
#ifndef CLCD_H
#define CLCD_H

#define CLCD_DATA_PORT    DIO_PORTC
#define CLCD_CTRL_PORT    DIO_PORTD

#define CLCD_RS_PIN       DIO_PIN3
#define CLCD_RW_PIN       DIO_PIN4
#define CLCD_E_PIN        DIO_PIN5


void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidInit(void);

void CLCD_voidSendString(const char* Copy_pcString);

void CLCD_voidLCDClear(void);

void CLCD_GotoPosition(u8 Row , u8 Col);
void CLCD_voidDisplayInteger(u16 number);
#endif

