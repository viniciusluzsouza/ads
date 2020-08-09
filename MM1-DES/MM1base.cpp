// Inspired on http://archive.cone.informatik.uni-freiburg.de/teaching/lecture/protocol-design-s09/slides/07-Simulation_1.pdf
//

#include "MM1base.h"

void standardArrival::processEvent ()
{
//    std::cout << "ARRIVAL: processando evento no tempo " << time  << '\n';
    if (myMM1->getServerState()==IDLE) {
        myMM1->setServerState(ACTIVE);
        myMM1->MeuSimulador->scheduleEvent (new standardDeparture(myMM1->rngService.exp()+myMM1->MeuSimulador->simtime
        , myMM1));
    } else {
        enqueueTime = myMM1->MeuSimulador->simtime;
        myMM1->pushQueue(this->clone());
    }
    myMM1->MeuSimulador->scheduleEvent  (new standardArrival(myMM1->rngArrival.exp() + myMM1->MeuSimulador->simtime,
            myMM1));

    myMM1->MeuSimulador->queueSizeCounter += myMM1->sizeQueue();
    myMM1->MeuSimulador->queueSizeCountedTimes++;
}


void standardDeparture::processEvent () {
//    std::cout << "SERVICE:processando evento no tempo " << time  << '\n';
    if (myMM1->emptyQueue()) {
        myMM1->setServerState(IDLE);
    } else{
        class standardArrival *p = (class standardArrival *) myMM1->getFrontAndPopQueue();
        myMM1->MeuSimulador->serviceTimeCounter += time - p->time;
        myMM1->MeuSimulador->processedEvents++;
        myMM1->MeuSimulador->timeBusy += (time - p->enqueueTime);
        delete p;
        myMM1->MeuSimulador->scheduleEvent (new standardDeparture(myMM1->rngService.exp() + myMM1->MeuSimulador->simtime,
                myMM1));
    }

    myMM1->MeuSimulador->queueSizeCounter += myMM1->sizeQueue();
    myMM1->MeuSimulador->queueSizeCountedTimes++;
}
