//
// Created by Irene Chen on 2020/2/8.
//

#include "GNQTS.h"
#include <climits>
#include <cfloat>

GNQTS::GNQTS(Model *m) {
    this->model = m;
    betaMatrix = new double[model->num_of_stock];

    gBestParticle = new Particle();
    gBestParticle->setSize(model->num_of_stock);

    worstParticle = new Particle();
    worstParticle->setSize(model->num_of_stock);

    gBestParticle->fitness = -INT_MAX;
    particle = new Particle[PARTICLE];

    for (int i = 0; i < PARTICLE; i++) {
        particle[i].setSize(model->num_of_stock);
    }

    for (int i = 0; i < model->num_of_stock; i++) {
        betaMatrix[i] = 0.5;
    }
    gBestParticle->fitness = -DBL_MAX;
}

GNQTS::~GNQTS() {
    delete[] betaMatrix;
    delete[] particle;
    delete gBestParticle;
    delete worstParticle;
}

int GNQTS::run() {
    int best_gen = 0;
    double fitness = -DBL_MAX;
    for (int i = 0; i < GENERATION; i++) {
        GNQTS::measure();
        GNQTS::mutate();
        if (fitness < this->gBestParticle->fitness) {
            fitness = this->gBestParticle->fitness;
            best_gen = i;
        }
    }
    model->getFitness(gBestParticle->binarySolution, 1);
    return best_gen;
}

void GNQTS::measure() {
    worstParticle->fitness = INT_MAX;
    double random;
    for (int i = 0; i < PARTICLE; i++) {
        for (int j = 0; j < model->num_of_stock; j++) {
            random = rand() / (double) RAND_MAX;

            if (random < betaMatrix[j]) {
                particle[i].binarySolution[j] = 1;
            } else {
                particle[i].binarySolution[j] = 0;
            }
        }
        particle[i].fitness = model->getFitness(particle[i].binarySolution, 0);

        if (gBestParticle->fitness < particle[i].fitness) {
            if (particle[i].fitness < 0) {
                gBestParticle->fitness = 0.0;
                for (int j = 0; j < model->num_of_stock; j++) {
                    gBestParticle->binarySolution[j] = 0;
                }
            } else {
                gBestParticle->fitness = particle[i].fitness;
                for (int j = 0; j < model->num_of_stock; j++) {
                    gBestParticle->binarySolution[j] = particle[i].binarySolution[j];
                }
            }
        }

        if (worstParticle->fitness > particle[i].fitness) {
            worstParticle->fitness = particle[i].fitness;
            for (int j = 0; j < model->num_of_stock; j++) {
                worstParticle->binarySolution[j] = particle[i].binarySolution[j];
            }
        }
    }
}

void GNQTS::mutate() {
    for (int i = 0; i < model->num_of_stock; i++) {
        if (gBestParticle->binarySolution[i] == 0 && worstParticle->binarySolution[i] == 1) {
            if (betaMatrix[i] > 0.5) {
                betaMatrix[i] = 1 - betaMatrix[i];
                betaMatrix[i] = betaMatrix[i] - THETA;
            } else if (betaMatrix[i] <= 0.5) {
                betaMatrix[i] = betaMatrix[i] - THETA;
            }
        }
        if (gBestParticle->binarySolution[i] == 1 && worstParticle->binarySolution[i] == 0) {
            if (betaMatrix[i] < 0.5) {
                betaMatrix[i] = 1 - betaMatrix[i];
                betaMatrix[i] = betaMatrix[i] + THETA;
            } else if (betaMatrix[i] >= 0.5) {
                betaMatrix[i] = betaMatrix[i] + THETA;
            }
        }
    }
}
