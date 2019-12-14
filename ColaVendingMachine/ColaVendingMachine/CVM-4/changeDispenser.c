#include "display.h"
#include "changeDispenser.h"
#include <stdio.h>

//------------------------------------------------------------- CHange Dispenser

void CHDinitialise(void)
{
   DSPdebugSystemInfo("Change Dispenser: initialised");
}

void CHDdispenseChange(int change)
{
   char info[DISPLAY_SIZE];
   sprintf(info, "%s%d",
           "Change Dispenser: dispensed change = ",
           change);
   DSPdebugSystemInfo(info);
}
