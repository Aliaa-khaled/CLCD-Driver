#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_prv.h"
#include "CLCD_cfg.h"


void CLCD_voidSendCmd(uint8 Copy_u8Cmd)
{
	/*Set RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_u8PIN_LOW);

	/*Set RW pin to low for writing*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_u8PIN_LOW);

	/*Send the command*/
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,Copy_u8Cmd);

	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN, DIO_u8PIN_LOW);
	
}
void CLCD_voidSendData(uint8 Copy_u8Data)
{
	/*Set RS pin to high for command*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_u8PIN_HIGH);

	/*Set RW pin to low for writing*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_u8PIN_LOW);

	/*Send the Data*/
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,Copy_u8Data);

	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN, DIO_u8PIN_LOW);
	
}
void CLCD_voidInit(void)
{
	/*Wait for more than 30 ms after power on*/
	_delay_ms(40);

	/*Function set command: 2 lines, Font size: 5x7*/
	CLCD_voidSendCmd(0b00111000);

	/*Display on off control : Display on, cursor off, blink cursor off*/
	CLCD_voidSendCmd(0b00001100);

	/*Clear display*/
	CLCD_voidSendCmd(1);
	
}
uint8 CLCD_voidSendString(const char* Copy_Pu8SrTRING)
{
	uint8 Local_U8ErrorStata = OK ;
	if(Copy_Pu8SrTRING!= NULL)
	{
		while (*Copy_Pu8SrTRING != '\0') 
		{
			CLCD_voidSendData( *Copy_Pu8SrTRING); 
			Copy_Pu8SrTRING++; 
		}
	}
	else
	{
		Local_U8ErrorStata=NULL_PTR_ERR;
	}
	return Local_U8ErrorStata;
}

void CLCD_voidSendNumber(sint32 Copy_s32NUMBER)
{
	uint8 Num_Array[12];
	uint8 Array_index = 0;
	
	if (Copy_s32NUMBER == 0)
	{
		CLCD_voidSendData('0');
		return;
	}
	else if(Copy_s32NUMBER<0)
	{
		Copy_s32NUMBER*=-1;
		CLCD_voidSendData( '-');
	}
	 while (Copy_s32NUMBER > 0)
	 {
		 Num_Array[Array_index++] = (Copy_s32NUMBER % 10) + '0'; 
		 Copy_s32NUMBER /= 10;
	 }
	for (uint8 i = 0; i < Array_index / 2; i++)
	{
		char temp = Num_Array[i];
		Num_Array[i] = Num_Array[Array_index - i - 1];
		Num_Array[Array_index - i - 1] = temp;
	}
	CLCD_voidSendString( Num_Array);
	
}
void CLCD_voidGoToXY(uint8 Copy_u8XPos,uint8 Copy_u8YPos)
{
	uint8 Local_u8Address ;
	Local_u8Address = 0x40 * Copy_u8YPos + Copy_u8XPos;
	SET_BIT(Local_u8Address,7);
	CLCD_voidSendCmd(Local_u8Address);
	
}
uint8 CLCD_u8SendSpecialCharacter(uint8 Copy_u8LocationNum, uint8* Copy_pu8Pattern, uint8 Copy_u8XPos, uint8 Copy_u8YPos)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_pu8Pattern != NULL)
	{
		uint8 Local_u8Counter;

		uint8 Local_u8CGRAMAddress = Copy_u8LocationNum * 8;

		/*Set bit 6 for CGRAM Address command*/
		SET_BIT(Local_u8CGRAMAddress , 6u);

		/*Set ACGRAM Address*/
		CLCD_voidSendCmd(Local_u8CGRAMAddress);

		/*Write the input pattern inside CGRAM*/
		for(Local_u8Counter=0u; Local_u8Counter<8u; Local_u8Counter++)
		{
			CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);
		}

		/*Go back to DDRAM*/
		CLCD_voidGoToXY(Copy_u8XPos, Copy_u8YPos);

		/*Display the special pattern inside CGRAM*/
		CLCD_voidSendData(Copy_u8LocationNum);

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}