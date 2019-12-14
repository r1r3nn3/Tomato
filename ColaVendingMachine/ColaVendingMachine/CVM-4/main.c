// Cola Vending Machine - 4 (CVM-4) --------------------------------------------

#include "fsm.h"

/// Executes the state machine (FSM: Finite State Machine) in
/// an endless loop processing the generated event by a subsystem. 
/// The state machine is excuted by the function #eventHandler. 
/// @author Jos Onokiewicz
int main(void)
{
   event_e currentEvent = E_START;

   eventHandler(currentEvent);
   // Endless loop
   while (1)
   {
      currentEvent = generateEvent();
      eventHandler(currentEvent);
   }

   return 0;
}
