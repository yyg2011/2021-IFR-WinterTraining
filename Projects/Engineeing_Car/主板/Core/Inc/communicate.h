#define Send_Begin_Message      12
#define Send_Finish_Message     34
#define Receive_Begin_Message   56
#define Receive_Finish_Message  78

typedef enum 
{
    Begin_Send,
    Sending,
    Confirm_Send,
    Finish_Send,
    Begin_Receive,
    Receiving,
    Confirm_Receive,
    Finish_Receive,
}Communicate_State;

typedef struct
{
	uint8_t begin;
	
}Send_Message;

typedef struct
{
	uint8_t* Buffer[2];
	uint8_t Buffer_Num;
	uint16_t Length_Max;
}UART_RX_BUFFER;

void Usart_Init(void);