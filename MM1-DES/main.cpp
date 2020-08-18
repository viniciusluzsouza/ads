#include <iostream>
#include <stdio.h>
#include "apacheDES.h"
#include "MM1base.h"
// #include "rngUn.h"
#include "rngExp.h"
#include <math.h>
#include "ConfInterval.h"

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
    int aux = 100000;
    double tmrs[n], us[n], vs[n], tmf[n], var[aux], semente, lamb;
    int r;

    ConfInterval confInterval(tmrs, us, vs, tmf, n);

    printf("\n<========================================================>\n\n");

    for(r = 0;r<n;r++) {
        simuladorFilas MeuSimulador(r+1, 5, r+1, 10);
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

        printf("[R=%d] tmrs=%.3f, us=%.3f, vs=%.3f, tmf=%.3f\n", r+1, tmrs[r], us[r], vs[r], tmf[r]);

    }

    confInterval.calc_all();

    printf("\n<=============== Resultados %d Repetições ===============>\n\n", r);
    printf("Tempo médio de requisições no sistema: %.4f (σ²=%.4f, σ=%.4f)\n", confInterval.x_tmrs, confInterval.var_tmrs, confInterval.des_tmrs);
    printf("Utilização do servidor: %.4f (σ²=%.4f, σ=%.4f)\n", confInterval.x_us, confInterval.var_us, confInterval.des_us);
    printf("Vazão do sistema: %.3f (σ²=%.4f, σ=%.4f)\n", confInterval.x_vs, confInterval.var_vs, confInterval.des_vs);
    printf("Tamanho médio da fila: %.4f (σ²=%.4f, σ=%.4f)\n\n", confInterval.x_tmf, confInterval.var_tmf, confInterval.des_tmf);

    printf("\n<==== Intervalo de confiança para tempo médio na fila ====>\n\n");
    printf("Número de repetições para intervalo de confiança de 90%% e erro 5%%: %.2f\n", confInterval.get_repeticoes(CI_90, 5));
    printf("Número de repetições para intervalo de confiança de 95%% e erro 5%%: %.2f\n", confInterval.get_repeticoes(CI_95, 5));
    printf("Número de repetições para intervalo de confiança de 99%% e erro 5%%: %.2f\n\n", confInterval.get_repeticoes(CI_99, 5));

    printf("\n<================== Geração exponencial =================>\n\n");

    semente = 1;
    lamb = 5;
    rngExp rng(semente, lamb);

    FILE *p_arq;
	int i;

	if ((p_arq=fopen("var.txt", "w")) == NULL) {
		printf("Problemas na abertura do arquivo\n");
		return 0;
	}else{
		printf("Iniciando geração exponencial...\n\n");
		for (int i = 0; i < aux; i++){
		        var[i] = rng.exp();
		}
		for (int j = 0; j < aux; j++) {
			if((fprintf(p_arq,"%f\n",var[j]))==EOF) {
			printf("Erro ao escrever no arquivo!\n");
			return -1;
			}
		}
		printf("Fim da escrita, observe o arquivo 'var.txt'\n");
		fclose(p_arq);
	}
    printf("\n<========================================================>\n\n");


    return 0;
}
