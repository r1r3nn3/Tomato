#ifndef DISPLAY_H
#define DISPLAY_H

//--------------------display--------------------//

#define DISPLAY_SIZE_STR "70"
#define DISPLAY_SIZE 70

void DSPinitialise(void);
void DSPshow(const char *text);
void DSPsimulationSystemInfo(const char *text, int value);
void DSPshowSystemError(const char *text);
void DSPhelp(int helpType);
void DSPclearScreen(void);
void DSPsystemInfo(int systemInfoType);
void DSPprintSeperator(void);

#endif // DISPLAY_H
