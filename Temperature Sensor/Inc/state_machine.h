/*
 * state_machine.h
 *
 *  Created on: Jul 3, 2017
 *      Author: Prince
 */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum{
	INIT,
	SEARCH,
	RECEIVE
}State;

int fsm(State state);

#endif /* STATE_MACHINE_H */
