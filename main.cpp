#include "GNQTS.h"
#include <cfloat>
#include <chrono>

void test(int a, int b, int c) {
    int period = a - 1;
    int stock_a = b;
    int stock_b = c;
    double best = -DBL_MAX;
    int allot_a = 0;
    Model *model = new Model();
    model->nextPeriod(period);

    std::cout << "|" << tag << ", period " << period + 1 << " <br> " << trainPeriod[period];

    Particle particle;
    particle.setSize(model->num_of_stock);
    Align align;
    align.setStock(model->num_of_stock, model->num_of_day);
    for (int i = 0; i < model->num_of_stock; i++) {
        if (i == stock_a || i == stock_b)
            particle.binarySolution[i] = 1;
        else
            particle.binarySolution[i] = 0;

        for (int i = 0; i <= 10000; i++) {
            double fitness = model->one_to_two(particle.binarySolution, stock_a, stock_b, i, 10000 - i, -1);
            if (best < fitness) {
                best = fitness;
                allot_a = i;
            }
        }
    }
    model->one_to_two(particle.binarySolution, stock_a, stock_b, 0, 0, 6);
    std::cout << "|" << tag << ", period " << period + 1;
    model->one_to_two(particle.binarySolution, stock_a, stock_b, allot_a, 10000 - allot_a, 7);
}

int main() {
    auto start = std::chrono::steady_clock::now();
    if (tag == "H2H") {
        test(2, 5, 39);
    } else if (tag == "Q2Q") {
        test(2, 4, 5);
        test(8, 21, 24);
        test(20, 2, 7);
    } else if (tag == "M2M") {
        test(3, 4, 13);
        test(14, 4, 17);
        test(24, 10, 45);
        test(29, 0, 37);
        test(35, 0, 42);
        test(43, 33, 46);
        test(64, 10, 35);
        test(66, 10, 18);
        test(70, 27, 47);
        test(84, 3, 35);
    } else if (tag == "Y2H") {
        test(6, 18, 45);
    } else if (tag == "Y2Q") {
        test(11, 18, 45);
    } else if (tag == "Y2M") {
        test(30, 18, 45);
        test(33, 22, 45);
        test(77, 2, 24);
    } else if (tag == "H2Q") {
        test(3, 5, 39);
        test(24, 2, 33);
    } else if (tag == "H2M") {
        test(7, 5, 39);
        test(8, 5, 39);
        test(11, 24, 40);
        test(21, 40, 41);
        test(23, 24, 45);
        test(24, 24, 45);
        test(27, 45, 46);
        test(60, 7, 20);
        test(70, 2, 33);
        test(74, 16, 24);
    } else if (tag == "Q2M") {
        test(3, 20, 28);
        test(4, 4, 5);
        test(17, 0, 44);
        test(22, 21, 24);
        test(24, 16, 45);
        test(27, 42, 48);
        test(30, 15, 46);
        test(58, 2, 7);
    } else if (tag == "H#") {
        test(3, 5, 39);
    } else if (tag == "Q#") {
        test(5, 4, 5);
        test(11, 21, 24);
        test(23, 2, 7);
    } else if (tag == "M#") {
        test(14, 4, 13);
        test(25, 4, 17);
        test(35, 10, 45);
        test(40, 0, 37);
        test(46, 0, 42);
        test(54, 33, 46);
        test(75, 10, 35);
        test(77, 10, 18);
        test(81, 27, 47);
        test(95, 3, 35);
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
    std::cout << endl << endl << "Time taken: " << std::chrono::duration<double>(end - start).count() << " s"
              << std::endl;
    return 0;
}
