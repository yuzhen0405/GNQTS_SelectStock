//
// Created by Irene Chen on 2020/2/8.
//

#ifndef GNQTS_SELECTSTOCK_QTS_H
#define GNQTS_SELECTSTOCK_QTS_H

#include "Model.h"
#include "Stock.h"

#define GENERATION 10000
#define INDIVIDUAL 10

using namespace std;

class QTS {
public:
    QTS() = delete;

    QTS(Model *m);

    ~QTS();

    Model *model;
    double *betaMatrix;
    Particle *particle;
    Particle *gBestParticle, *worstParticle;

    void run(int period);

    void measure(int gen,int period);

    void mutate(int gen);
};

#endif //GNQTS_SELECTSTOCK_QTS_H
