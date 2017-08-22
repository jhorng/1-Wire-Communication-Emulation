/*
 * event.h
 *
 *  Created on: Jul 18, 2017
 *      Author: TARUC
 */

#ifndef EVENT_H_
#define EVENT_H_

typedef enum{
	START_EVT,			// 0
	UART_TX_CPL_EVT,	// 1
	UART_RX_CPL_EVT,	// 2
	TIMEOUT_EVT			// 3
}Event;

typedef int(*EventCallbackFunc)(Event evt);

typedef struct EventCallback EventCallback;
struct EventCallback{
	EventCallbackFunc ongoing;
	EventCallbackFunc next;
};

void registerCallbacks(EventCallback eventCallback, EventCallbackFunc ongoing, EventCallbackFunc next);

#endif /* EVENT_H_ */
