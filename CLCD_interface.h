
#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H



void CLCD_voidSendCmd(uint8 Copy_u8Cmd);
void CLCD_voidSendData(uint8 Copy_u8Data);
void CLCD_voidInit(void);
uint8 CLCD_voidSendString(const char* Copy_Pu8SrTRING);
void CLCD_voidSendNumber(sint32 Copy_s32NUMBER);
void CLCD_voidGoToXY(uint8 Copy_u8XPos,uint8 Copy_u8YPos);

#endif