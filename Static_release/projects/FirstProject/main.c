#include "MDR32FxQI_config.h"
#include "MDR32F9Q2I.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_ssp.h"
#include "RTE_Components.h"

//Begin_Include
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_adc.h"
#include "MDR32FxQI_uart.h"
//End_Include

//Begin_prototype_Func
void Ini_GPIO_A0();
void Ini_GPIO_A1();
void Ini_GPIO_A2();
void Ini_GPIO_A3();
void Ini_ADC_1();
void Ini_Uart_1();
//End_prototype_Func

//Begin_Init_struct
ADC_InitTypeDef sADC;
ADCx_InitTypeDef sADCx;
UART_InitTypeDef sUART;
//End_Init_struct

int main(){
	
	//Begin_Init_config
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);
	RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_ADC),ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_UART1, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
	//End_Init_config
	
	//Begin_call_Func
	Ini_GPIO_A0();
	Ini_GPIO_A1();
	Ini_GPIO_A2();
	Ini_GPIO_A3();
	Ini_ADC_1();
	Ini_Uart_1();
	//End_call_Func

	
	while(1){ // endless cycle
		//Begin_Result
		uint8_t data_A3_res = PORT_ReadInputDataBit(MDR_PORTA, PORT_Pin_3);
		
		uint16_t adc1_res;
		adc1_res = MDR_ADC->ADC1_RESULT & 0x0FFF;
		
		//uint16_t dataUart = 0;		

		//if(UART_GetFlagStatus (MDR_UART1, UART_FLAG_TXFE) == SET){
		//	UART_SendData(MDR_UART1, 0xAA);
		//}
		
		//if(UART_GetFlagStatus (MDR_UART1, UART_FLAG_RXFE) != SET){
		//	dataUart = UART_ReceiveData(MDR_UART1);
		//}
		
		//End_Result
	}
}

//Begin_Func
void Ini_GPIO_A0(){
	static PORT_InitTypeDef PortInit;
	PortInit.PORT_OE = PORT_OE_OUT;
	PortInit.PORT_FUNC = PORT_FUNC_PORT;
	PortInit.PORT_MODE = PORT_MODE_DIGITAL;
	PortInit.PORT_SPEED = PORT_SPEED_SLOW;
	PortInit.PORT_Pin = (PORT_Pin_0);
	PORT_Init(MDR_PORTA, &PortInit);
}

void Ini_GPIO_A1(){
	static PORT_InitTypeDef PortInit;
	PortInit.PORT_OE = PORT_OE_OUT;
	PortInit.PORT_FUNC = PORT_FUNC_PORT;
	PortInit.PORT_MODE = PORT_MODE_DIGITAL;
	PortInit.PORT_SPEED = PORT_SPEED_SLOW;
	PortInit.PORT_Pin = (PORT_Pin_1);
	PORT_Init(MDR_PORTA, &PortInit);
}

void Ini_GPIO_A2(){
	static PORT_InitTypeDef PortInit;
	PortInit.PORT_OE = PORT_OE_OUT;
	PortInit.PORT_FUNC = PORT_FUNC_PORT;
	PortInit.PORT_MODE = PORT_MODE_DIGITAL;
	PortInit.PORT_SPEED = PORT_SPEED_SLOW;
	PortInit.PORT_Pin = (PORT_Pin_2);
	PORT_Init(MDR_PORTA, &PortInit);
}

void Ini_GPIO_A3(){
	static PORT_InitTypeDef PortInit;
	PortInit.PORT_OE = PORT_OE_IN;
	PortInit.PORT_FUNC = PORT_FUNC_PORT;
	PortInit.PORT_MODE = PORT_MODE_DIGITAL;
	PortInit.PORT_SPEED = PORT_SPEED_SLOW;
	PortInit.PORT_Pin = (PORT_Pin_3);
	PORT_Init(MDR_PORTA, &PortInit);
}

void Ini_ADC_1(){
	static PORT_InitTypeDef PortInit;
	ADC_InitTypeDef sADC;
	ADCx_InitTypeDef sADCx;

	PortInit.PORT_Pin   = PORT_Pin_7;
	PortInit.PORT_OE    = PORT_OE_IN;
	PortInit.PORT_MODE  = PORT_MODE_ANALOG;
	PORT_Init(MDR_PORTD, &PortInit);

	ADC_DeInit();
	ADC_StructInit(&sADC);
	ADC_Init (&sADC);

	ADCx_StructInit (&sADCx);
	sADCx.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;
	sADCx.ADC_SamplingMode     = ADC_SAMPLING_MODE_CYCLIC_CONV;
	sADCx.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;
	sADCx.ADC_ChannelNumber    = ADC_CH_ADC7;
	sADCx.ADC_Channels         = 0;
	sADCx.ADC_LevelControl     = ADC_LEVEL_CONTROL_Disable;
	sADCx.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;
	sADCx.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;
	sADCx.ADC_Prescaler        = ADC_CLK_div_None;
	sADCx.ADC_DelayGo          = 0x00;
	ADC1_Init (&sADCx);

	ADC1_Cmd(ENABLE);
}

void Ini_Uart_1(){
	static PORT_InitTypeDef PortInit;

	PortInit.PORT_Pin        = PORT_Pin_5; // TX 
	PortInit.PORT_OE         = PORT_OE_OUT;
	PortInit.PORT_PULL_UP    = PORT_PULL_UP_OFF;
	PortInit.PORT_PULL_DOWN  = PORT_PULL_DOWN_OFF;
	PortInit.PORT_PD_SHM     = PORT_PD_SHM_OFF;
	PortInit.PORT_PD         = PORT_PD_DRIVER;
	PortInit.PORT_GFEN       = PORT_GFEN_OFF;
	PortInit.PORT_FUNC       = PORT_FUNC_ALTER;
	PortInit.PORT_SPEED      = PORT_SPEED_MAXFAST;
	PortInit.PORT_MODE       = PORT_MODE_DIGITAL;
	PORT_Init(MDR_PORTB, &PortInit);

	PortInit.PORT_Pin        = PORT_Pin_6; //RX
	PortInit.PORT_OE         = PORT_OE_IN;
	PortInit.PORT_FUNC       = PORT_FUNC_ALTER;
	PORT_Init(MDR_PORTB, &PortInit);
		
	UART_BRGInit(MDR_UART1, UART_HCLKdiv1);
	
	sUART.UART_BaudRate = 9600; 
	sUART.UART_WordLength = UART_WordLength8b;
	sUART.UART_StopBits = UART_StopBits1;
	sUART.UART_Parity = UART_Parity_No;
	sUART.UART_FIFOMode = UART_FIFO_OFF;
	sUART.UART_HardwareFlowControl = UART_HardwareFlowControl_TXE | UART_HardwareFlowControl_RXE;

	UART_Init(MDR_UART1, &sUART);
	UART_Cmd(MDR_UART1,ENABLE);
}

//End_Func
