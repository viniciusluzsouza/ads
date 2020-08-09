//
// See http://stdcxx.apache.org/doc/stdlibug/2-2.html#225
// Apache C++ Standard Library User's Guide
//

#ifndef SIMULADORMM1_APACHEDES_H
#define SIMULADORMM1_APACHEDES_H

#include <queue>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <queue>


#define MAX_SIMTIME 100

//==================================================================
// classes evento e simulação - base para o desenvolvimento da simulação
//==================================================================

class event {
public:
    // A estampa de tempo é setada na criação do objeto evento
    event (double t) : time (t)
    { }

    // Este método deve ser chamado no momento do processamento do evento
    virtual void processEvent () = 0;

    const double time;
};


class apacheDES {
public:
    apacheDES () : simtime (0), eventQueue ()
    {
        num_events = 0;
        serviceTimeCounter = 0;
        processedEvents = 0;
        timeBusy = 0;
        queueSizeCounter = 0;
        queueSizeCountedTimes = 0;
    }
    void run (); // loop de execução da simulação
    void  scheduleEvent (event * newEvent) {
        eventQueue.push (newEvent);
    }
    double simtime;

    // Para calcular tempo médio das requisições no sistema
    double serviceTimeCounter;
    int processedEvents;

    // Para calcular utilização do servidor
    double timeBusy;

    // Para calcular o tamanho médio da fila
    double queueSizeCounter;
    double queueSizeCountedTimes;

protected:
    int num_events;
    class eventComparator {
    public:
        bool operator() (const event * left, const event * right) const {
            return left->time > right->time;
        }
    };
    std::priority_queue<event*,
            std::vector<event *, std::allocator<event*> >,
            eventComparator> eventQueue;  //fila de eventos
};

#endif //SIMULADORMM1_APACHEDES_H
