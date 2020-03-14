//
// Created by Irene Chen on 2020/2/3.
//

#ifndef GNQTS_SELECTSTOCK_MODEL_H
#define GNQTS_SELECTSTOCK_MODEL_H

#include "Logger.h"
#include "Stock.h"
#include "Particle.h"

#define ROTATE_ANGLE 0.0004
#define FEE 0.001425
#define TAX 0.003
#define SHARE 1000.0
#define FUND 10000000.0

class Model {
public:
    Model();

    ~Model();

    double getFitness(int *binarySolution, int gen,int individual, int HW);

    int NUM_OF_STOCK;
    int NUM_OF_DAY;
    Stock *stock;

    void readfile(int period);

    void getStock(int period);
};

#endif //GNQTS_SELECTSTOCK_MODEL_H
