//
// Created by Irene Chen on 2020/2/8.
//

#ifndef GNQTS_SELECTSTOCK_QTS_H
#define GNQTS_SELECTSTOCK_QTS_H

#include "Model.h"
#include "Stock.h"

#define GENERATION 1
#define INDIVIDUAL 1

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

    void run();

    void measure(int gen);

    void update(int gen);

    void mutate(int gen);
};

#endif //GNQTS_SELECTSTOCK_QTS_H