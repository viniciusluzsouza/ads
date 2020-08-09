//
// Created by eraldo on 23/06/2020.
//

#ifndef SIMULADORMM1_MM1BASE_H
#define SIMULADORMM1_MM1BASE_H

#include "rngExp.h"
#include "apacheDES.h"

#define IDLE 0
#define ACTIVE 1

// classe base para implementação de uma MM1
class MM1base {
public:
    MM1base (unsigned seed_arrival, double lambda_arrival, unsigned seed_dep, double mu_dep, apacheDES *pSim) :
            rngArrival(seed_arrival, lambda_arrival), rngService(seed_dep, mu_dep), server_state(IDLE),
            mu(mu_dep), lambda(lambda_arrival), MeuSimulador(pSim)
    { }
    rngExp rngArrival, rngService;
    int getServerState(){ return server_state; };
    void setServerState(int state){ server_state=state;};
    void pushQueue(event *x){ myqueue.push(x);};
    bool emptyQueue(){return myqueue.empty();}
    int  sizeQueue(){return myqueue.size();}
    class event *getFrontAndPopQueue(){
        event *p = myqueue.front();
        myqueue.pop();
        return p;
    }
    apacheDES *MeuSimulador;
private:
    std::queue<event*> myqueue;
    int server_state;
    double mu;
    double lambda;
};

//===================================================================
//Customização dos eventos e do simulador
//===================================================================

class standardArrival : public event {
public:
    standardArrival(standardArrival *p, class MM1base *pMM1): event(p->time), myMM1(pMM1)
    {
        enqueueTime = p->enqueueTime;
    }
    standardArrival (double creationTime, class MM1base *pMM1)
            : event (creationTime), myMM1(pMM1)
    { }
    virtual void processEvent ();
    double enqueueTime;
protected:
    class MM1base *myMM1;
    class standardArrival* clone() { return new standardArrival(this, myMM1); }
};

class standardDeparture : public event {
public:
    standardDeparture (double t, class MM1base *pMM1)
            : event (t), myMM1(pMM1)//, service_time_counter(0), processedEvents(0)
    { }
    virtual void processEvent ();
//    double service_time_counter;
//    int processedEvents;
protected:
    class MM1base *myMM1;
};
#endif //SIMULADORMM1_MM1BASE_H
