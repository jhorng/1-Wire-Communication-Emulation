/*
 * event.c
 *
 *  Created on: Aug 22, 2017
 *      Author: Jaan Horng
 */

#include <stdlib.h>
#include "event.h"

EventCallback uart1Tx = {NULL, NULL};
EventCallback uart1Rx = {NULL, NULL};
EventCallback timer2 = {NULL, NULL};

void registerCallbacks(EventCallback eventCallback, EventCallbackFunc ongoing, EventCallbackFunc next){
  eventCallback.ongoing = ongoing;
  eventCallback.next = next;
}

