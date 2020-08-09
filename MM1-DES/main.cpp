#include <iostream>
#include "apacheDES.h"
#include "MM1base.h"
// #include "rngUn.h"
#include "rngExp.h"
#include <math.h>

using namespace std;

class simuladorFilas : public apacheDES  {
public:
    simuladorFilas (unsigned seed_arrival, double lambda_arrival, unsigned seed_dep, double mu_dep) :
        MM1(seed_arrival, lambda_arrival, seed_dep, mu_dep, this) { }
    simuladorFilas () :
        MM1(0, 5, 0, 10, this) { }
    class MM1base MM1;

};

int main() {
    int n = 10;
    double tmrs[n], us[n], vs[n], tmf[n];
    double x_tmrs=0, x_us=0, x_vs=0, x_tmf=0;
    double var_tmrs=0, var_us=0, var_vs=0, var_tmf=0;
    double des_tmrs=0, des_us=0, des_vs=0, des_tmf=0;
    int i, r;

    for(r = 0;r<n;r++) {
        simuladorFilas MeuSimulador(r, 5, r, 10);
        tmrs[r]=0, us[r]=0, vs[r]=0, tmf[r]=0;

        //Gerar primeira chegada
        MeuSimulador.scheduleEvent (new standardArrival (MeuSimulador.MM1.rngArrival.exp(), &MeuSimulador.MM1));
        // MeuSimulador.scheduleEvent (new standardArrival (MeuSimulador.MM1.rngArrival.exp()+0.5, &MeuSimulador.MM1));

        // Executar simulador
        MeuSimulador.run ();

        tmrs[r] = MeuSimulador.MM1.MeuSimulador->serviceTimeCounter / MeuSimulador.MM1.MeuSimulador->processedEvents;
        us[r] = (MeuSimulador.MM1.MeuSimulador->timeBusy / MeuSimulador.MM1.MeuSimulador->simtime) * 100;
        vs[r] = MeuSimulador.MM1.MeuSimulador->processedEvents / MeuSimulador.MM1.MeuSimulador->simtime;
        tmf[r] = MeuSimulador.MM1.MeuSimulador->queueSizeCounter / MeuSimulador.MM1.MeuSimulador->queueSizeCountedTimes;

        x_tmrs += tmrs[r];
        x_us += us[r];
        x_vs += vs[r];
        x_tmf += tmf[r];

        printf("[R=%d] tmrs=%.3f, us=%.3f, vs=%.3f, tmf=%.3f\n", r+1, tmrs[r], us[r], vs[r], tmf[r]);

    }

    x_tmrs = x_tmrs/r;
    x_us = x_us/r;
    x_vs = x_vs/r;
    x_tmf = x_tmf/r;

    for(i=0;i<n;i++){
        var_tmrs += pow(tmrs[i] - x_tmrs, 2.0);
        var_us += pow(us[i] - x_us, 2.0);
        var_vs += pow(vs[i] - x_vs, 2.0);
        var_tmf += pow(tmf[i] - x_tmf, 2.0);
    }

    // Variancia
    var_tmrs = var_tmrs / (n-1);
    var_us = var_us / (n-1);
    var_vs = var_vs / (n-1);
    var_tmf = var_tmf / (n-1);

    // Desvio padrao
    des_tmrs = sqrt(var_tmrs);
    des_us = sqrt(var_us);
    des_vs = sqrt(var_vs);
    des_tmf = sqrt(var_tmf);

    cout << "\n<=============== Resultados " << r << " Repetições ===============>\n" << endl;
    printf("Tempo médio de requisições no sistema: %.3f (σ²=%.3f, σ=%.3f)\n", x_tmrs, var_tmrs, des_tmrs);
    printf("Utilização do servidor: %.3f (σ²=%.3f, σ=%.3f)\n", x_us, var_us, des_us);
    printf("Vazão do sistema: %.3f (σ²=%.3f, σ=%.3f)\n", x_vs, var_vs, des_vs);
    printf("Tamanho médio da fila: %.3f (σ²=%.3f, σ=%.3f)\n", x_tmf, var_tmf, des_tmf);

    cout << endl;

    double t90=1.8331, t95=2.2622, t99=3.2498;
    double n90=0, n95=0, n99=0;
    double erro = 5; // 5%

    n90 = pow((100*t90*des_tmf)/(erro*x_tmf), 2.0);
    n95 = pow((100*t95*des_tmf)/(erro*x_tmf), 2.0);
    n99 = pow((100*t99*des_tmf)/(erro*x_tmf), 2.0);

    printf("Intervalo de confiança para tempo medio na fila\n");
    printf("Número de repetições para intervalo de confiança de 90%% e erro 5%%: %.2f\n", n90);
    printf("Número de repetições para intervalo de confiança de 95%% e erro 5%%: %.2f\n", n95);
    printf("Número de repetições para intervalo de confiança de 99%% e erro 5%%: %.2f\n", n99);

    cout << endl;

    return 0;
}
