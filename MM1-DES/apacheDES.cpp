//
// See http://stdcxx.apache.org/doc/stdlibug/2-2.html#225
// Apache C++ Standard Library User's Guide

#include "apacheDES.h"

void apacheDES::run () {

    while (! eventQueue.empty () && simtime < MAX_SIMTIME) { //enquanto existir eventos na fila de eventos

        event * nextEvent = eventQueue.top (); //captura evento no topo da fila
        eventQueue.pop ();  //retira evento da fila
        simtime = nextEvent->time;  //ajusta tempo de simulação
        nextEvent->processEvent ();  //processa evento
        delete nextEvent;  //remove evento
    }

}
