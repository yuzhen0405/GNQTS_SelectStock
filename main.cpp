#include "GNQTS.h"
#include <cfloat>
#include <chrono>

void test(int a, int b) {
    int period = a - 1;
    int stock_a = b;
    int stock_b = 0;
    double best = -DBL_MAX;
    int allot_a = 0;
    Model *model = new Model();
    model->nextPeriod(period);

    std::cout << "|" << tag << ", period " << period + 1 << " <br> " << trainPeriod[period];

    Particle particle;
    particle.setSize(model->num_of_stock);
    Align align;
    align.setStock(model->num_of_stock, model->num_of_day);
    for (int j = 0; j < model->num_of_stock; j++) {
        for (int i = 0; i < model->num_of_stock; i++) {
            if (i == stock_a || i == j)
                particle.binarySolution[i] = 1;
            else
                particle.binarySolution[i] = 0;
        }
        if (stock_a != j) {
            for (int i = 0; i <= 10000; i++) {
                double fitness = model->one_to_two(particle.binarySolution, stock_a, j, i, 10000 - i, -1);
                if (best < fitness) {
                    best = fitness;
                    allot_a = i;
                    stock_b = j;
                }
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
        test(13, 24);
    } else if (tag == "M2M") {
        test(9, 4);
        test(15, 44);
        test(21, 26);
        test(25, 42);
        test(58, 7);
        test(67, 38);
        test(68, 24);
        test(69, 2);
        test(72, 45);
        test(73, 16);
    } else if (tag == "Y2H") {
        test(14, 24);
    } else if (tag == "Y2Q") {
        test(27, 24);
    } else if (tag == "Y2M") {
        test(74, 24);
        test(78, 24);
        test(79, 24);
    } else if (tag == "H2Q") {
        test(25, 24);
    } else if (tag == "H2M") {
        test(71, 2);
        test(72, 24);
        test(73, 24);
    } else if (tag == "Q2M") {
        test(6, 27);
        test(8, 40);
        test(23, 26);
        test(59, 20);
        test(60, 42);
        test(69, 24);
        test(74, 16);
    } else if (tag == "H#") {
        test(14, 24);
    } else if (tag == "M#") {
        test(6, 25);
        test(20, 4);
        test(26, 44);
        test(32, 26);
        test(36, 42);
        test(69, 7);
        test(78, 38);
        test(79, 24);
        test(80, 2);
        test(83, 45);
        test(84, 16);
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
