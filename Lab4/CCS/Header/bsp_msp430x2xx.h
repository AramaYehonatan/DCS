///NOT relevant for lab 3 (DMA)

#ifndef _bsp_H_
#define _bsp_H_

 #include  <msp430g2553.h>          // MSP430x2xx

#define   debounceVal      250

// RGB abstraction
#define RGBArrPort         P2OUT
#define RGBArrPortSel      P2SEL
#define RGBArrPortDir      P2DIR

#define RGB_B              0x01
#define RGB_G              0x02
#define RGB_R              0x04
#define RGB_ALL            0x07

//BUZZER abstraction
#define BuzzerArrPort     P2OUT
#define BuzzerArrPortDir  P2DIR
#define BuzzerArrPortSel  P2SEL

#define BUZZER            0x10

//Potenciometer Input
#define ANArrPort         P1IN
#define ANArrPortSel      P1SEL
#define ANArrPortDir      P1DIR

#define AN                0x08

//LCD abstraction
#define LCDDataArrPort    P1OUT
#define LCDDataArrPortDir P1DIR
#define LCDDataArrPortSel P1SEL

#define LCDDataEntries    0xF0

#define LCD_DATA_WRITE    P1OUT
#define LCD_DATA_DIR      P1DIR
#define LCD_DATA_READ     P1IN

#define LCDCTLArrPort     P2OUT
#define LCDCTLArrPortDir  P2DIR
#define LCDCTLArrPortSel  P2SEL

#define LCDE                 0x20
#define LCDRS                0x40
#define LCDRW                0x80
#define LCDControlEntries    0xE0

//UART abstraction
#define UARTArrPortSel       P1SEL
#define UARTArrPortSel2      P1SEL2
#define UART_RX              0x02
#define UART_TX              0x04
#define receiveBuffer        UCA0RXBUF
#define transmitBuffer       UCA0TXBUF
#define UARTIntVector        IE2
#define UARTRecieveIE        UCA0RXIE
#define UARTTransIE          UCA0TXIE


//Timer abstraction
#define TimerA0CTL          TA0CTL
#define TimerA0Reg0         TA0CCR0

#define TimerA1Reg0         TA1CCR0
#define TimerA1RegBuz       TA1CCR2
#define TimerA1CTL          TA1CTL
#define TimerA1BuzCTL       TA1CCTL2

extern void GPIOconfig(void);
extern void TIMERconfig(void);
extern void ADCconfig(void);
extern void UARTconfig(void);


#endif



