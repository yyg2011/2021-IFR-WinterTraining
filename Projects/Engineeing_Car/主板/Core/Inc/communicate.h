#define USART1_RX_LEN_MAX 18
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

void Usart_Init(void);