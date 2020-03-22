#include "GNQTS.h"
#include <cfloat>
#include <chrono>

int main() {
    auto start = std::chrono::steady_clock::now();

    srand(114);

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

    auto end = std::chrono::steady_clock::now();
    std::cout << endl << "Time taken: " << std::chrono::duration<double>(end - start).count() << " s" << std::endl;
    return 0;
}
