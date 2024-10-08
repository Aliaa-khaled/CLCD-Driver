#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"
#include "DIO_interface.h"
#include "DIO_prv.h"
#include "DIO_cfg.h"
#include "DIO_reg.h"


uint8 DIO_u8SetPinDirection(uint8 copy_u8Port, uint8 copy_u8Pin, uint8 copy_u8Direction)
{
	uint8 Local_U8ErrorStata = OK ;
	if(copy_u8Pin <= DIO_u8PIN7)
	{
		if(copy_u8Direction == DIO_u8PIN_INPUT)
		{
			switch(copy_u8Port)
			{
				case DIO_u8PORTA : CLR_BIT(DDRA,copy_u8Pin); break;
				case DIO_u8PORTB : CLR_BIT(DDRB,copy_u8Pin); break;
				case DIO_u8PORTC : CLR_BIT(DDRC,copy_u8Pin); break;
				case DIO_u8PORTD : CLR_BIT(DDRD,copy_u8Pin); break;
				default: Local_U8ErrorStata = NOK;			  break;
			}
		}
		else if(copy_u8Direction == DIO_u8PIN_OUTPUT)
		{
			switch(copy_u8Port)
			{
				case DIO_u8PORTA : SET_BIT(DDRA,copy_u8Pin); break;
				case DIO_u8PORTB : SET_BIT(DDRB,copy_u8Pin); break;
				case DIO_u8PORTC : SET_BIT(DDRC,copy_u8Pin); break;
				case DIO_u8PORTD : SET_BIT(DDRD,copy_u8Pin); break;
				default: Local_U8ErrorStata = NOK;			  break;
			}
			
		}
		else
		{
			Local_U8ErrorStata = NOK;
		}
	}
	else
	{
		Local_U8ErrorStata = NOK;
	}
	
	return Local_U8ErrorStata;
	
}
uint8 DIO_u8SetPinValue(uint8 copy_u8Port, uint8 copy_u8Pin, uint8 copy_u8Value)
{
	uint8 Local_U8ErrorStata = OK ;
	if(copy_u8Pin <= DIO_u8PIN7)
	{
		if(copy_u8Value == DIO_u8PIN_LOW)
		{
			switch(copy_u8Port)
			{
				case DIO_u8PORTA : CLR_BIT(PORTA,copy_u8Pin); break;
				case DIO_u8PORTB : CLR_BIT(PORTB,copy_u8Pin); break;
				case DIO_u8PORTC : CLR_BIT(PORTC,copy_u8Pin); break;
				case DIO_u8PORTD : CLR_BIT(PORTD,copy_u8Pin); break;
				default: Local_U8ErrorStata = NOK;			  break;
			}
		}
		else if(copy_u8Value == DIO_u8PIN_HIGH)
		{
			switch(copy_u8Port)
			{
				case DIO_u8PORTA : SET_BIT(PORTA,copy_u8Pin); break;
				case DIO_u8PORTB : SET_BIT(PORTB,copy_u8Pin); break;
				case DIO_u8PORTC : SET_BIT(PORTC,copy_u8Pin); break;
				case DIO_u8PORTD : SET_BIT(PORTD,copy_u8Pin); break;
				default: Local_U8ErrorStata = NOK;			  break;
			}
			
		}
		else
		{
			Local_U8ErrorStata = NOK;
		}
	}
	else
	{
		Local_U8ErrorStata = NOK;
	}
	return Local_U8ErrorStata;
	
	
}
uint8 DIO_u8ReadPinDValue(uint8 copy_u8Port, uint8 copy_u8Pin,uint8 *copy_Pu8Value)
{
	uint8 Local_U8ErrorStata = OK ;
	if(copy_Pu8Value!= NULL)
	{
		if(copy_u8Pin <= DIO_u8PIN7)
		{
			switch(copy_u8Port)
			{
				case DIO_u8PORTA :*copy_Pu8Value= GET_BIT(PINA,copy_u8Pin); break;
				case DIO_u8PORTB :*copy_Pu8Value= GET_BIT(PINB,copy_u8Pin); break;
				case DIO_u8PORTC :*copy_Pu8Value= GET_BIT(PINC,copy_u8Pin); break;
				case DIO_u8PORTD :*copy_Pu8Value= GET_BIT(PIND,copy_u8Pin); break;
				default: Local_U8ErrorStata = NOK;			  break;
			}
			
		}
		else
		{
			Local_U8ErrorStata = NOK;
		}
	}
	else
	{
		Local_U8ErrorStata=NULL_PTR_ERR;
	}
	
	return Local_U8ErrorStata;
	
}

uint8 DIO_u8SetPortDirection(uint8 copy_u8Port, uint8 copy_u8Direction)
{
	uint8 Local_U8ErrorStata = OK ;
	
	switch(copy_u8Port)
	{
		case DIO_u8PORTA :DDRA=copy_u8Direction; break;
		case DIO_u8PORTB :DDRB=copy_u8Direction; break;
		case DIO_u8PORTC :DDRC=copy_u8Direction; break;
		case DIO_u8PORTD :DDRD=copy_u8Direction; break;
		default: Local_U8ErrorStata = NOK;		  break;
	}
	
	return Local_U8ErrorStata;
}
uint8 DIO_u8SetPortValue(uint8 copy_u8Port, uint8 copy_u8Value)
{
	uint8 Local_U8ErrorStata = OK ;
	
	switch(copy_u8Port)
	{
		case DIO_u8PORTA :PORTA=copy_u8Value; break;
		case DIO_u8PORTB :PORTB=copy_u8Value; break;
		case DIO_u8PORTC :PORTC=copy_u8Value; break;
		case DIO_u8PORTD :PORTD=copy_u8Value; break;
		default: Local_U8ErrorStata = NOK;	  break;
	}
	
	return Local_U8ErrorStata;
}

uint8 DIO_u8TogglePinValue(uint8 copy_u8Port, uint8 copy_u8Pin)
{
	uint8 Local_U8ErrorStata = OK ;
	if(copy_u8Pin <= DIO_u8PIN7)
	{
		switch(copy_u8Port)
		{
			case DIO_u8PORTA : TOG_BIT(PORTA,copy_u8Pin); break;
			case DIO_u8PORTB : TOG_BIT(PORTB,copy_u8Pin); break;
			case DIO_u8PORTC : TOG_BIT(PORTC,copy_u8Pin); break;
			case DIO_u8PORTD : TOG_BIT(PORTD,copy_u8Pin); break;
			default: Local_U8ErrorStata = NOK;		  break;
		}
	}
	else
	{
		Local_U8ErrorStata = NOK;
	}
	
	return Local_U8ErrorStata;
}