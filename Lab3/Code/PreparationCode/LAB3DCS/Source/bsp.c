#include  "../header/bsp_msp430x4xx.h"    // private library - BSP layer

//-----------------------------------------------------------------------------  
//           GPIO congiguration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
   
  // PushButtons Setup
  PBsArrPortSel &= ~PBs0_3;
  PBsArrPortDir &= ~PBs0_3;
  PBsArrIntEdgeSel |= (PB0 + PB1);          // pull-up mode
  PBsArrIntEdgeSel &= ~(PB2 + PB3);         // pull-down mode
  PBsArrIntEn |= PBs0_3;
  PBsArrIntPend &= ~PBs0_3;            // clear pending interrupts

  //LCD Setup
   LCDDataArrPort      &= ~LCDDataEntries;
   LCDDataArrPortDir   |= LCDDataEntries;
   LCDDataArrPortSel   &= ~LCDDataEntries;
   LCDCTLArrPortSel    &= ~LCDControlEntries;
   LCDCTLArrPortDir    |= LCDControlEntries;
   LCDCTLArrPort       &= ~LCDControlEntries;

   //Keypad
   KeysPortSel    &= ~(KEYPADOUT + KEYPADIN);
   KeysPortDir    &= ~(KEYPADIN);
   KeysPortDir    |= KEYPADOUT;
   KeysPortOut    &= ~KEYPADOUT;


   KeysIRQIntSel  &= ~KEYPADIRQ;
   KeysIRQIntDir  &= ~KEYPADIRQ;
   KeysIRQIntIes  |= (KEYPADIRQ);
   KeysIRQIntIE   &= ~KEYPADIRQ;
   KeysIRQIntPend &= ~KEYPADIRQ;

   //LEDs
   LEDsPortSel    &= ~LEDFULLPORT;
   LEDsPortDir    |= LEDFULLPORT;
   LEDsPortOut    &= ~LEDFULLPORT;

  _BIS_SR(GIE);                     // enable interrupts globally
}                             
//------------------------------------------------------------------------------------- 
//            Timers configuration
//-------------------------------------------------------------------------------------
void TIMERconfig(void){
    TimerBCTL = TBSSEL_1 + TBCLR; //Configure ACLK (2^15 Hz) and clear. Timer is Halted.
    TimerBCMP0CTL = 0; //set timer register 0 as a compare register
} 

//------------------------------------------------------------------------------------- 
//            DMA configuration
//-------------------------------------------------------------------------------------
void DMAconfig(void){
    DMACTL0 = DMA0TSEL_0 + DMA1TSEL_8; //first channel is for state 2 SW trigger, Second channel is for state 3 , timer triggered
    DMA0CTL = DMADT_1 + DMADSTBYTE + DMASRCBYTE + DMAIE; // block , byte byte , interrupt enable
    DMA1CTL = DMADT_1 + DMADSTBYTE + DMASRCBYTE + DMAIE; // block , byte byte , interrupt enable
    DMA1SZ = 1;
    DMA1DA = &LEDsPortOut;
}
           
             

 
             
             
            
  

