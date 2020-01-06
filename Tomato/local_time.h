#ifndef LOCAL_TIME_H
#define LOCAL_TIME_H

#define TIME_BUFFER_SIZE 5
//--------------------local time--------------------//

void LTinitialise(void);
const char * LTgetTime(char* output);
void LTincreaseTime(int minutes);
int LTgetMinutes(void);
int LTgetHours(void);
int LTgetDays(void);
long int LTgetTimeObject(void);

#endif // LOCAL_TIME_H