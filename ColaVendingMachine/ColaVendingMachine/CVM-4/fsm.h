#ifndef FSM_H
#define FSM_H

#include "events.h"

event_e generateEvent(void);
void eventHandler(event_e evnt);

event_e CVMinitialise(void);
event_e CVMcheckCents(int coinValue);
event_e CVMcheckChange(void);

#endif // FSM_H
