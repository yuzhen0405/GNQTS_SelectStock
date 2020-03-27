//
// Created by Irene Chen on 2020/2/3.
//

#ifndef GNQTS_SELECTSTOCK_MODEL_H
#define GNQTS_SELECTSTOCK_MODEL_H

#include "Particle.h"
#include "Align.h"
#include "Stock.h"
#include <string>

#define ROUND 50
#define THETA 0.0004
#define THETA_UPPER 0.0004;
#define THETA_LOWER 0.0004;
#define FEE 0.001425
#define TAX 0.003
#define SHARE 1000.0
#define FUND 10000000.0
#define PERCENT 1000

class Model {
public:
    Align *align;

    Model();

    ~Model();

    double getFitness(int *binarySolution, int HW);

    double one_to_two(int period, int *binarySolution, int stock_a, int stock_b, int stock_c, int stock_d, int allot_a,
                      int allot_b, int allot_c, int allot_d, int HW);

    int num_of_stock;
    int num_of_day;
    Stock *stock;

    void nextPeriod(int period);

    void readfile(const std::string &path);

    void getStock(const std::string &path);
};

#endif //GNQTS_SELECTSTOCK_MODEL_H
