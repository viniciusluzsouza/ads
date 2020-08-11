//
// Created by eraldo on 23/06/2020.
//

#ifndef SIMULADORMM1_RNGEXP_H
#define SIMULADORMM1_RNGEXP_H

#include <math.h>

// Classe para geração de números randômicos uniformes

class rngUn {

public:
   void seed(unsigned int s) {
      _seed= s;
   }

   rngUn(double seed, double m, int a, int c) : _seed(seed), m(m), a(a), c(c) {}
   rngUn() : _seed(0), m(2147483648), a(1103515245), c(12345) {}
   rngUn(double seed) : _seed(seed), m(2147483648), a(1103515245), c(12345) {}
   double rnd() { _seed = (a * _seed + c) % m; return (double) _seed / (double) m; }

private:
   int a, c;
   unsigned int _seed, m;
};

// Classe para geração de números randômicos segundo distribuição expoenencial

class rngExp {
public:
    rngExp(double seed, double lambda) : myseed(seed), mylambda(lambda)
    { _randUni = rngUn(seed); }
    double exp() { return log(_randUni.rnd()) / -mylambda; };
private:
    rngUn _randUni;
    double myseed;
    double mylambda;
};


#endif //SIMULADORMM1_RNGEXP_H
