#ifndef DISPLAY_H
#define DISPLAY_H

#define DISPLAY_SIZE_STR "70"
#define DISPLAY_SIZE 70

//--------------------display--------------------//

#define DISPLAY_SIZE_STR "70"
#define DISPLAY_SIZE 70

void DSPinitialise(void);
void DSPshow(const char *text);
void DSPdebugSystemInfo(const char *text);
void DSPsimulationSystemInfo(const char *text);
void DSPshowSystemError(const char *text);
void DSPhelp(void);
void DSPsystemInfo(void);
void DSPserviceInfo(void);
void calculateTime(double);
void DSPprintSeperator(void);

#endif
