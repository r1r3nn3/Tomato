#include "keyboard.h"
#include "display.h"
#include <stdio.h>

//--------------------------------------------------------------------- Keyboard

void KYBinitialise(void)
{
   DSPdebugSystemInfo("Keyboard: initialised");
}

/// Reads all input characters after pressing Enter.
/// @post All remaining buffered characters are removed from the input buffer
/// (stdin).
/// @return First read character.
char KYBgetchar(void)
{
   char c = getchar();
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
