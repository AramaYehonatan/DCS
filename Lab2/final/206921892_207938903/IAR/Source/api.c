#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer

    unsigned int startTime;
    unsigned int endTime;

int DispFreqFromInput(int lastValueDiff){
 
        unsigned int freq;
        char clcFreq[6];
    
        disable_interrupts();
        startTime = 0;
        endTime = 0;
        enableCaptureRegister();

        __bis_SR_register(LPM0_bits + GIE);
        
        //asm(" nop");
    
        if(startTime == 0 && endTime == 0){
          return lastValueDiff;
        }
    
        if ((endTime-startTime > lastValueDiff+1 )||(endTime-startTime < lastValueDiff-1 )){ 
          freq = CalcFreq(endTime , startTime);
          //asm(" nop");
  
  
          NumToString(clcFreq,6,(unsigned int)freq);
          LCDSetCursor(4);
          lcd_puts(clcFreq);
          cursor_off;
          //DelayMs(500);
          enable_interrupts();
          return (endTime-startTime);
        }
        else{
          enable_interrupts();
          return lastValueDiff;
        }
}

void PrepareLCDState1(void){
    lcd_clear();
    lcd_home();
    writeToLCD("fin=");
    moveLCDRight(5);
    writeToLCD("Hz");
}

unsigned int CalcFreq(unsigned int end,unsigned int start){
    return (SMCLKFREQ/(end-start));
}

void NumToString(char* str,int strLen , int num){
  str[strLen-1] = '\0';
  int i;
  for (i=strLen-2;i>=0;i--){
      if (num==0)
          str[i] = ' ';
      else{
          str[i] = num%10 + '0';
          num = num/10;
      }
  }
}


void CountSec(void){
        char timeString[6];
        SetTimeStrTo0(timeString);
        while (state == state2){
          lcd_home();
          lcd_puts(timeString);
          cursor_off;
          WaitOneSec();
          if(SampleSW()){
            UpdateTime(timeString);
          }
        }
        disable_TimerA0();
        return;
}

void SetTimeStrTo0(char* timeString){
  timeString[0] = '0';
  timeString[1] = '0';
  timeString[2] = ':';
  timeString[3] = '0';
  timeString[4] = '0';
  timeString[5] = '\0';
}

void WaitOneSec(void){
  setTimeTimer0(0xFFFF);
  enable_TimerA0();
  enterLPM(0);
  enable_TimerA0();
  enterLPM(0); 
}


void UpdateTime(char* timeString){
  if(timeString[4] < '9'){
    timeString[4] = timeString[4]+1;
    return;
  }
  timeString[4] = '0';
  if (timeString[3] < '5'){
    timeString[3] = timeString[3] + 1;
    return;
  }
  timeString[3] = '0';
  if (timeString[1] < '9'){
    timeString[1] = timeString[1] + 1;
    return;
  }
  timeString[1] = '0';
  if (timeString[0] < '9'){
    timeString[0] = timeString[0] + 1;
    return;
  }
  timeString[0] = '0';
  return;
}


void genBuzz(void){
    unsigned int Nadc = 0;
    EnableADC();
    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
    Nadc = GetNadc();
    //DisableADC();
    //unsigned int fout = mulByCoeff(Nadc) + 1000;
    //unsigned int NumForRegister = SMCLKFREQ/fout;
    
    unsigned int NumForRegister = 1057 - mulByNewCoeff(Nadc);

    InsertToRegistersForADC(NumForRegister); //1057 - 425


}
unsigned int mulByNewCoeff (unsigned int x){ //NewCoeff = 0.617, 0.1001
    unsigned int tmp = x;
    unsigned int sum = 0;
    tmp = tmp >> 1;
    sum = sum + tmp;
    tmp = tmp >> 2;
    sum = sum + tmp;
    return sum;
}


unsigned int mulByCoeff(unsigned int x){ //coef = 1.466 = 1.0111
    unsigned int tmp = x;
    unsigned int sum = 0;
    sum = tmp;
    tmp = tmp >> 2;
    sum = sum + tmp;
    tmp = tmp >> 1;
    sum = sum + tmp;
    tmp = tmp >> 1;
    sum = sum + tmp;
    return sum;
}


void printBs(void){
        char place = 0;
        while (state == state4){
          if (place == 32){
            lcd_clear();
            lcd_home();
            place = 0;
          }
          if (place != 0){
            lcd_cursor_left();
            lcd_putchar(' ');
          }
          if (place == 16){
            lcd_new_line;
          }
          lcd_putchar('B');
          cursor_off;
          place++;
          Wait09Sec();
        }
        disable_TimerA0();
        return;
}

void Wait09Sec (void){
  setTimeTimer0(0xFFFF);
  enable_TimerA0();
  enterLPM(0);
  setTimeTimer0(0xCCCC);
  enable_TimerA0();
  enterLPM(0);
}