#ifndef DISPLAY_H
#define DISPLAY_H

//--------------------display--------------------//
void DSPinitialise(void);
void DSPshow(const char *text);
void DSPdebugSystemInfo(const char *text);
void DSPsimulationSystemInfo(const char *text);
void DSPshowSystemError(const char *text);
void DSPsystemInfo(void);
void calculateTime(double);

#endif // DISPLAY_H
