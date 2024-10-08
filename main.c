#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "CLCD_interface.h"

void main(void)
{
	uint8 Local_u8Pattern[8] = {0b00000100, 0b00001110, 0b00011111,0b00011111,0b00001110,0b00001110,0b00001110,0b00001110};
		
	DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN2,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_OUTPUT);

	DIO_u8SetPortDirection(DIO_u8PORTB,DIO_u8PORT_OUTPUT);

	CLCD_voidInit();
	CLCD_voidSendString("1+1");
	CLCD_u8SendSpecialCharacter(0, Local_u8Pattern,0,1);

	while(1)
	{

	}
}
