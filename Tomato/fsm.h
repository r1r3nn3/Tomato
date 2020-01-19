#ifndef FSM_H
#define FSM_H

#include "events.h"

event_e generateEvent(void);
void eventHandler(event_e event);
void FSMinitialise(void);
event_e TAGinitialise(void);


#endif // FSM_H
