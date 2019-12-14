#include "display.h"
#include <stdio.h>

//---------------------------------------------------------------------- DiSPlay

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
   printf("\n-- DEBUG %-" DISPLAY_SIZE_STR "s\n", text);
}

void DSPsimulationSystemInfo(const char *text)
{
   printf("\n-- SIMULATION %-" DISPLAY_SIZE_STR "s", text);
}

void DSPshowSystemError(const char *text)
{
   printf("\n## SYSTEM ERROR %-" DISPLAY_SIZE_STR "s ##\n", text);
}
