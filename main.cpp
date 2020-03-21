#include "GNQTS.h"
#include <cfloat>
#include <chrono>

int main() {
    auto start = std::chrono::steady_clock::now();

    srand(114);

    Model *model;
    model = new Model();

    double fitness;

    for (int i = 0; i < 1; i++) {
        double gBestFitness = -DBL_MAX;
        model->nextPeriod(i);

        Align *align = new Align();
        model->align = align;
        align->setStock(model->num_of_stock, model->num_of_day);
        align->theta_upper = THETA_UPPER;
        align->theta_lower = THETA_LOWER;
        align->theta = THETA;
        align->round = 0;
        align->initial_fund = FUND;
        align->final_fund = 0;
        align->expect_reward = 0;
        align->risk = 0;
        align->gBest = 0;
        align->find_gBest_gen = 0;
        align->find_gBest_round = 0;
        align->find_gBest_time = 0;
        align->num = 0;
        for (int j = 0; j < model->num_of_stock; j++) {
            align->binarySolution[j] = 0;
            align->stock[j].avg_fund = 0;
            align->balance[i] = 0;
            align->amount[i] = 0;
            for (int k = 0; k < model->num_of_day; k++) {
                align->stock[j].fs[k] = 0.0;
                align->FS[k] = 0.0;
            }
        }

        Align *allAlign = new Align();
        allAlign->setStock(model->num_of_stock, model->num_of_day);
        for (int j = 0; j < model->num_of_stock; j++) {
            align->stock[j].symbol = model->stock[j].symbol;
            allAlign->stock[j].symbol = model->stock[j].symbol;
        }
        allAlign->num = 0;
        for (int j = 0; j < model->num_of_stock; j++) {
            allAlign->binarySolution[j] = 0;
        }
        allAlign->gBest = -DBL_MAX;
        allAlign->expect_reward = 0;
        allAlign->risk = 0;
        allAlign->find_gBest_round = 0;
        allAlign->find_gBest_gen = 0;
        allAlign->find_gBest_time = 0;

        for (int j = 0; j < ROUND; j++) {
            GNQTS qts(model);
            fitness = qts.run();
            if (fitness > gBestFitness) {
                align->gBest = fitness;
                align->find_gBest_time = 1;
                align->find_gBest_round = j;
            } else if (fitness == gBestFitness) {
                align->find_gBest_time++;
            }
        }
        allAlign->num = align->num;
        for (int i = 0; i < model->num_of_stock; i++) {
            allAlign->binarySolution[i] = align->binarySolution[i];
        }
        allAlign->gBest = align->gBest;
        allAlign->expect_reward = align->expect_reward;
        allAlign->risk = align->risk;
        allAlign->find_gBest_round = align->find_gBest_round;
        allAlign->find_gBest_gen = align->find_gBest_gen;
        allAlign->find_gBest_time = align->find_gBest_time;

        align->align(i);
        allAlign->allAlign(i);
        delete align;
        delete allAlign;
    }
    delete model;

    auto end = std::chrono::steady_clock::now();
    std::cout << endl << "Time taken: " << std::chrono::duration<double>(end - start).count() << "s" << std::endl;
    return 0;
}
