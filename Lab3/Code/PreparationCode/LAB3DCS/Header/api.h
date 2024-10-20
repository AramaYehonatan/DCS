#ifndef _api_H_
#define _api_H_

#include  "../header/halGPIO.h"     // private library - HAL layer

extern void PrepareLCDState1(void);
extern void WriteWord(void);
extern void Merge(void);
extern void LEDsByDMA(void);
extern void MirrorByDMA(void);

void PrepareLCDState2(void);
void PromptTwoNums(char*, char*);
char DMAMerge(char*, char , char);
void printToLDCScrolling(char* , char);
void writeStrMirrorToLCD(char*);
char countChars (char* );


#endif







