//
// Created by Irene Chen on 2020/2/8.
//

#ifndef GNQTS_SELECTSTOCK_GNQTS_H
#define GNQTS_SELECTSTOCK_GNQTS_H

#include "Model.h"

#define GENERATION 100
#define PARTICLE 10

class GNQTS {
public:
    Model *model;

    GNQTS() = delete;

    GNQTS(Model *m);

    ~GNQTS();

    double *betaMatrix;
    Particle *particle;
    Particle *gBestParticle, *worstParticle;

    int run();

    void measure();

    void mutate();
};

#endif //GNQTS_SELECTSTOCK_GNQTS_H
