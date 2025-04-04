#include "pelican.h"
#include "qpc.h"
#include "bsp.h"
#include "safe_std.h"

static const QEvt * pelicanQSto [10];
// static const QEvt * pelicaStackSto [100];


void Pelican_start(){

    Pelican_const((void *)0);   



    QActive_start(Pelican_AO,
        7U,            // QP prio. of the AO
        pelicanQSto,           // event queue storage
        Q_DIM(pelicanQSto),    // queue length [events]
        // pelicaStackSto, Q_DIM(pelicaStackSto),           //testing per thread pointer
        (void *)0, 0,    // no stack storage
        (void *)0);              // no initialization param
    }



int main(int argc, char *argv[]){
    WELCOME_SMS;

    QF_init();
    BSP_init(argc, argv);
    Pelican_start();

    


    QF_run();
    
    return 1;
}