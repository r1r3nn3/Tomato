#ifndef FSM_H
#define FSM_H

#include "events.h"

event_e generateEvent(void);
void evenHandler(event_e evnt);
void FSMinitialise(void);


#endif // FSM_H
