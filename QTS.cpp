//
// Created by Irene Chen on 2020/2/8.
//

#include "QTS.h"

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
    Logger logger_update("../log/update.csv", 4);

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
    double random;
    for (int i = 0; i < INDIVIDUAL; i++) {
        for (int j = 0; j < model->NUM_OF_STOCK; j++) {
            random = (double)rand() / RAND_MAX;
            if (random < betaMatrix[j]) {
                particle[i].binarySolution[j] = 1;
            } else {
                particle[i].binarySolution[j] = 0;
            }
//            if (j == 3 || j == 4 || j == 6 || j == 7 || j == 8 || j == 9 || j == 13 || j == 17 || j == 18 || j == 19 ||
//                j == 20 || j == 22 || j == 24 || j == 25 || j == 26 || j == 30 || j == 31 || j == 32 || j == 37 ||
//                j == 41 || j == 43 || j == 46 || j == 47) { //train_2009_12(2009 Q1)
//                if (j == 3 || j == 4 || j == 15 || j == 16 || j == 17 || j == 18 || j == 20 || j == 21 || j == 32 ||
//                                                   j == 34 || j == 36 || j == 41 || j == 43 || j == 47 || j == 48) { //train_2010_01(2010 Q1)
//                particle[i].binarySolution[j] = 1;
//            } else {
//                particle[i].binarySolution[j] = 0;
//            }
        }
        particle[i].fitness = model->getFitness(particle[i].binarySolution, gen, i, HW);

        if (gBestParticle->fitness < particle[i].fitness) {
            if (gBestParticle->fitness < 0) {
                particle[i].fitness = 0.0;
                gBestParticle->fitness = 0.0;
                for (int j = 0; j < model->NUM_OF_STOCK; j++) {
                    gBestParticle->binarySolution[j] = 0;
                }
            } else {
                gBestParticle->fitness = particle[i].fitness;
                for (int j = 0; j < model->NUM_OF_STOCK; j++) {
                    gBestParticle->binarySolution[j] = particle[i].binarySolution[j];
                }
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
//    for (int i = 0; i < model->NUM_OF_STOCK; i++) {
//        if (gBestParticle->binarySolution[i] == 1 && worstParticle->binarySolution[i] == 0) {
//            betaMatrix[i] += ROTATE_ANGLE;
//        } else if (worstParticle->binarySolution[i] == 1 && gBestParticle->binarySolution[i] == 0) {
//            betaMatrix[i] -= ROTATE_ANGLE;
//        }
//    }
}

void QTS::mutate(int gen) {
    for (int i = 0; i < model->NUM_OF_STOCK; i++) {
        if (gBestParticle->binarySolution[i] == 0 && worstParticle->binarySolution[i] == 1) {
            if (betaMatrix[i] > 0.5) {
                betaMatrix[i] = 1 - betaMatrix[i];
                betaMatrix[i] = betaMatrix[i] - ROTATE_ANGLE;
            } else if (betaMatrix[i] <= 0.5) {
                betaMatrix[i] = betaMatrix[i] - ROTATE_ANGLE;
            }
        }
        if (gBestParticle->binarySolution[i] == 1 && worstParticle->binarySolution[i] == 0) {
            if (betaMatrix[i] < 0.5) {
                betaMatrix[i] = 1 - betaMatrix[i];
                betaMatrix[i] = betaMatrix[i] + ROTATE_ANGLE;
            } else if (betaMatrix[i] >= 0.5) {
                betaMatrix[i] = betaMatrix[i] + ROTATE_ANGLE;
            }
        }
    }
    /*******************************************************************************/
    Logger logger_update("../log/update.csv", 4);

    for (int i = 0; i < model->NUM_OF_STOCK; i++) {
        logger_update.writeComma(betaMatrix[i]);
    }
    logger_update.writeLine("");
    /*******************************************************************************/
}

