//
// Created by Irene Chen on 2020/2/8.
//

#include "QTS.h"

Logger logger_update("../log/update.csv", 4);

int bestGen = -1;
int bestPar = -1;
int HW = -1;

QTS::QTS(Model *m) {
    model = m;
    try {
        betaMatrix = new double[model->NUM_OF_STOCK];

        gBestParticle = new Particle();
        gBestParticle->setSize(model->NUM_OF_STOCK);

        worstParticle = new Particle();
        worstParticle->setSize(model->NUM_OF_STOCK);

        gBestParticle->fitness = -INT_MAX;
        particle = new Particle[INDIVIDUAL];

        for (int i = 0; i < INDIVIDUAL; i++) {
            particle[i].setSize(model->NUM_OF_STOCK);
        }
    } catch (const bad_alloc &e) {
        cout << e.what();
    }
    for (int i = 0; i < model->NUM_OF_STOCK; i++) {
        betaMatrix[i] = 0.5;
    }
    /*******************************************************************************/
    for (int i = 0; i < model->NUM_OF_STOCK; i++) {
        logger_update.writeComma(i);
    }
    logger_update.writeLine("");
    /*******************************************************************************/
    gBestParticle->fitness = -INT_MAX;
}

QTS::~QTS() {
    delete[] betaMatrix;
    delete[] particle;
    delete gBestParticle;
    delete worstParticle;
}

void QTS::run() {
    for (int i = 0; i < GENERATION; i++) {
        QTS::measure(i);
        QTS::update(i);
        QTS::mutate(i);
    }
    HW = 1;
    model->getFitness(gBestParticle->binarySolution, bestGen, bestPar, HW);
}

void QTS::measure(int gen) {
    worstParticle->fitness = INT_MAX;
    for (int i = 0; i < INDIVIDUAL; i++) {
        for (int j = 0; j < model->NUM_OF_STOCK; j++) {
            if ((double) rand() / RAND_MAX < betaMatrix[j]) {
                particle[i].binarySolution[j] = 1;
            } else {
                particle[i].binarySolution[j] = 0;
            }
        }
        particle[i].fitness = model->getFitness(particle[i].binarySolution, gen, i, HW);
        if (gBestParticle->fitness < particle[i].fitness) {
            gBestParticle->fitness = particle[i].fitness;
            for (int j = 0; j < model->NUM_OF_STOCK; j++) {
                gBestParticle->binarySolution[j] = particle[i].binarySolution[j];
            }
            bestGen = gen;
            bestPar = i;
        }

        if (worstParticle->fitness > particle[i].fitness) {
            worstParticle->fitness = particle[i].fitness;
            for (int j = 0; j < model->NUM_OF_STOCK; j++) {
                worstParticle->binarySolution[j] = particle[i].binarySolution[j];
            }
        }
    }
}

void QTS::update(int gen) {
    for (int i = 0; i < model->NUM_OF_STOCK; i++) {
        if (gBestParticle->binarySolution[i] == 1 && worstParticle->binarySolution[i] == 0) {
            betaMatrix[i] += ROTATE_ANGLE;
        } else if (worstParticle->binarySolution[i] == 1 && gBestParticle->binarySolution[i] == 0) {
            betaMatrix[i] -= ROTATE_ANGLE;
        }
    }
}

void QTS::mutate(int gen) {
    for (int i = 0; i < model->NUM_OF_STOCK; i++) {
        if (betaMatrix[i] < 0.5 && gBestParticle->binarySolution[i] == 1 &&
            worstParticle->binarySolution[i] == 0) {
            betaMatrix[i] = 1 - betaMatrix[i] - ROTATE_ANGLE;
        } else if (betaMatrix[i] > 0.5 && worstParticle->binarySolution[i] == 1 &&
                   gBestParticle->binarySolution[i] == 0) {
            betaMatrix[i] = 1 - betaMatrix[i] + ROTATE_ANGLE;
        }
    }
    /*******************************************************************************/
    for (int i = 0; i < model->NUM_OF_STOCK; i++) {
        logger_update.writeComma(betaMatrix[i]);
    }
    logger_update.writeLine("");
    /*******************************************************************************/
}


