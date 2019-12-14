#include "coinAcceptor.h"
#include "display.h"
#include "keyboard.h"
#include <stdio.h>

//---------------------------------------------------------------- CoiN Acceptor

void CNAinitialise(void)
{
   DSPdebugSystemInfo("Coin Acceptor: initialised");
}

/// Checks in a loop if the input of a coin code is correct.
/// If the entered value is not correct this function will ask again for input.
/// @return Entered coin code.
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

/// Simulates the entering of coins.
/// @return Generated CNA subsystem event.
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
