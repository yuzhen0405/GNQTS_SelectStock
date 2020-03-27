#include "GNQTS.h"
#include <cfloat>
#include <chrono>

#define STOCK 5


void test(int p, int a, int b, int c, int d, int e) {
    int period = p - 1;
    int stock_a = a;
    int stock_b = b;
    int stock_c = c;
    int stock_d = d;
    int stock_e = e;
    double best = -DBL_MAX;
    int allot_a = 0;
    int allot_b = 0;
    int allot_c = 0;
    int allot_d = 0;
    int allot_e = 0;
    Model *model = new Model();
    model->nextPeriod(period);
    Particle particle;
    particle.setSize(model->num_of_stock);
    Align align;
    align.setStock(model->num_of_stock, model->num_of_day);

    for (int i = 0; i < model->num_of_stock; i++) {
        if (i == stock_a || i == stock_b || i == stock_c || i == stock_d || i == stock_e)
            particle.binarySolution[i] = 1;
        else
            particle.binarySolution[i] = 0;
    }
    double fitness = 0.0;
    for (int i = 0; i <= PERCENT; i++) {
        for (int j = 0; j <= PERCENT - i; j++) {
            for (int k = 0; k <= PERCENT - i - j; k++) {
                for (int l = 0; l <= PERCENT - i - j - k; l++) {
                    fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c,
                                                stock_d, stock_e, i, j, k, l, 100 - i - j - k - l, -1);
                    if (best < fitness) {
                        best = fitness;
                        allot_a = i;
                        allot_b = j;
                        allot_c = k;
                        allot_d = l;
                    }
                }
            }
        }
    }
    model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c,
                      stock_d, stock_e, allot_a, allot_b, allot_c, allot_d, 100 - allot_a - allot_b - allot_c - allot_d,
                      6);
}

int main() {
    auto start = std::chrono::steady_clock::now();
    if (STOCK == 5) {
        if (tag == "Y2Y") {
        } else if (tag == "H2H") {
        } else if (tag == "Q2Q") {
        } else if (tag == "M2M") {
            for (int i = 1; i < 2; i++) {
                test(i, 0, 1, 2, 3, 4);
            }
        } else if (tag == "Y2H") {

        } else if (tag == "Y2Q") {

        } else if (tag == "Y2M") {

        } else if (tag == "H2Q") {

        } else if (tag == "H2M") {

        } else if (tag == "Q2M") {

        } else if (tag == "H#") {

        } else if (tag == "Q#") {

        } else if (tag == "M#") {
        }

    }

//    srand(114);
/*
    Model *model = new Model();

    for (int i = 0; i < numOfPeriod; i++) {
        model->nextPeriod(i);

        model->align->theta_upper = THETA_UPPER;
        model->align->theta_lower = THETA_LOWER;
        model->align->theta = THETA;
        model->align->round = 0;
        model->align->initial_fund = FUND;
        model->align->final_fund = 0;
        model->align->expect_reward = 0;
        model->align->risk = 0;
        model->align->gBest = 0;
        model->align->find_gBest_gen = 0;
        model->align->find_gBest_round = 0;
        model->align->find_gBest_time = 0;
        model->align->num = 0;
        double best = -DBL_MAX;
        Align *allAlign = new Align();
        allAlign->setStock(model->num_of_stock, model->num_of_day);

        for (int j = 0; j < ROUND; j++) {
            GNQTS qts(model);
            int gen = qts.run();
            if (best < model->align->gBest) {
                best = model->align->gBest;
                model->align->find_gBest_time = 1;
                model->align->find_gBest_round = j;
                model->align->find_gBest_gen = gen;
                allAlign->gBest = model->align->gBest;
                allAlign->fitness = model->align->fitness;
                allAlign->num_of_day = model->align->num_of_day;
                allAlign->num_of_stock = model->align->num_of_stock;
                allAlign->num = model->align->num;
                allAlign->find_gBest_gen = model->align->find_gBest_gen;
                allAlign->find_gBest_round = model->align->find_gBest_round;
                allAlign->find_gBest_time = model->align->find_gBest_time;
                allAlign->theta = model->align->theta;
                allAlign->theta_upper = model->align->theta_upper;
                allAlign->theta_lower = model->align->theta_lower;
                allAlign->round = model->align->round;
                allAlign->initial_fund = model->align->initial_fund;
                allAlign->expect_reward = model->align->expect_reward;
                allAlign->final_fund = model->align->final_fund;
                allAlign->risk = model->align->risk;
                for (int k = 0; k < model->num_of_stock; k++) {
                    allAlign->amount[k] = model->align->amount[k];
                    allAlign->balance[k] = model->align->balance[k];
                    allAlign->binarySolution[k] = model->align->binarySolution[k];
                    allAlign->stock[k].symbol = model->align->stock[k].symbol;
                    allAlign->stock[k].avg_fund = model->align->stock[k].avg_fund;
                    allAlign->stock[k].beta = model->align->stock[k].beta;
                    for (int l = 0; l < model->num_of_day; l++) {
                        allAlign->stock[k].fs[l] = model->align->stock[k].fs[l];
                        allAlign->stock[k].price[l] = model->stock[k].price[l];
                    }
                }
                for (int k = 0; k < model->num_of_day; k++) {
                    allAlign->FS[k] = model->align->FS[k];
                }
            } else if (best == model->align->gBest) {
                model->align->find_gBest_time++;
                allAlign->find_gBest_time = model->align->find_gBest_time;
            }
        }

        allAlign->align(i);
        allAlign->allAlign(i);
        delete allAlign;
    }

    delete model;
*/
    auto end = std::chrono::steady_clock::now();
    std::cout << endl << endl << "Time taken: " <<
              std::chrono::duration<double>(end
                                            - start).

                      count()

              << " s"
              <<
              std::endl;
    return 0;
}
