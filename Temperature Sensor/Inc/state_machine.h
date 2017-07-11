/*
 * state_machine.h
 *
 *  Created on: Jul 3, 2017
 *      Author: Prince
 */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum{
	UART_RX_CPL_EVT,
	UART_TX_CPL_EVT,
	TIMEOUT_EVT
}EventType;

typedef enum{
	INIT_STATE,
	RESPONSE_STATE
}State;

typedef struct Event Event;
struct Event{
	EventType type;
	void *data;
};

typedef struct bitSearchSM bitSearchSM;
struct bitSearchSM{
	Event event;
	State state;
};

int fsm(State state);

#endif /* STATE_MACHINE_H */
