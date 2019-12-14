#ifndef SUBSYSTEMS_H
#define SUBSYSTEMS_H

#include "fsm.h"

//--------------------------------------------------------------------- KeYBoard

void KYBinitialise(void);
char KYBgetchar(void);
int KYBgetint(int ifWrongValue);

//---------------------------------------------------------------------- DiSPlay

void DSPinitialise(void);
void DSPshow(const char *text);
void DSPdebugSystemInfo(const char *text);
void DSPsimulationSystemInfo(const char *text);
void DSPshowSystemError(const char *text);

//---------------------------------------------------------------- CoiN Acceptor

void CNAinitialise(void);
char CNAinputCoin(void);
event_e CNAcheckCoins(void);

//--------------------------------------------------------------- CoLa Dispenser

void CLDinitialise(void);
void CLDdispenseCola(void);

#endif
