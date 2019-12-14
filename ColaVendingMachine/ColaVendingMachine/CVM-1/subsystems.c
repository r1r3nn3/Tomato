#include "fsm.h"
#include "subsystems.h"
#include <stdio.h>

//--------------------------------------------------------------------- KeYBoard

void KYBinitialise(void)
{
   DSPdebugSystemInfo("Keyboard: initialised");
}

char KYBgetchar(void)
{
   int c = getchar();
   // First char read, empty input buffer
   while ((getchar()) != '\n')
   {
      // Remove all remaining buffered input chars
   }
   return c;
}

int KYBgetint(int ifWrongValue)
{
   int input = 0;
   int nOk = scanf(" %d", &input);
   // First int read, empty input buffer
   while ((getchar()) != '\n')
   {
      // Remove all remaining buffered input chars
   }
   // Check if input is an int (nOk == 1), if not return ifWrongValue
   if (nOk != 1) {
      input = ifWrongValue;
   }
   return input;
}

//---------------------------------------------------------------------- DiSPlay

#define DISPLAY_SIZE_STR "70"
#define DISPLAY_SIZE 70

void DSPinitialise(void)
{
   DSPdebugSystemInfo("Display: initialised");
}

void DSPshow(const char *text)
{
   printf("\n## %-" DISPLAY_SIZE_STR "s ##\n", text);
}

void DSPdebugSystemInfo(const char *text)
{
   printf("\n-- DEBUG      %-" DISPLAY_SIZE_STR "s\n", text);
}

void DSPsimulationSystemInfo(const char *text)
{
   printf("\n-- SIMULATION %-" DISPLAY_SIZE_STR "s", text);
}

void DSPshowSystemError(const char *text)
{
   printf("\n## SYSTEM ERROR %-" DISPLAY_SIZE_STR "s ##\n", text);
}

//---------------------------------------------------------------- CoiN Acceptor

void CNAinitialise(void)
{
   DSPdebugSystemInfo("Coin Acceptor: initialised");
}

char CNAinputCoin(void)
{
   int coinIsOK = 0;
   char coin = '0';
   while (!coinIsOK)
   {
      coin = KYBgetchar();
      switch (coin)
      {
      case '1':
      case '2':
         coinIsOK = 1;
         break;
      default:
         DSPdebugSystemInfo("Coin Acceptor: unknown coin");
         DSPsimulationSystemInfo("Coins: <1> 10c  <2> 20c");
         break;
      }
   }
   return coin;
}

event_e CNAcheckCoins(void)
{
   char coin = '0';
   event_e event = E_NO;

   DSPsimulationSystemInfo("Coins: <1> 10c  <2> 20c");
   coin = CNAinputCoin();
   switch(coin)
   {
   case '1':
      event = E_10C;
      break;
   case '2':
      event = E_20C;
      break;
   }
   return event;
}

//--------------------------------------------------------------- CoLa Dispenser

void CLDinitialise(void)
{
   DSPdebugSystemInfo("Cola Dispenser: initialised");
}

void CLDdispenseCola(void)
{
   DSPshow("Cola dispensed, please take your cola");
}
