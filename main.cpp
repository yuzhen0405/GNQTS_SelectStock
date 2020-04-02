#include "GNQTS.h"
#include <cfloat>
#include <chrono>

#define STOCK 5

void test(int p, int a, int b, int c, int d, int e, int f, int g) {
    int period = p - 1;
    int stock_a = a;
    int stock_b = b;
    int stock_c = c;
    int stock_d = d;
    int stock_e = e;
    int stock_f = f;
    int stock_g = g;
    double best = -DBL_MAX;
    int allot_a = 0;
    int allot_b = 0;
    int allot_c = 0;
    int allot_d = 0;
    int allot_e = 0;
    int allot_f = 0;
    int allot_g = 0;
    Model *model = new Model();
    model->nextPeriod(period);
    Particle particle;
    particle.setSize(model->num_of_stock);
    Align align;
    align.setStock(model->num_of_stock, model->num_of_day);

    for (int i = 0; i < model->num_of_stock; i++) {
        if (i == stock_a || i == stock_b || i == stock_c || i == stock_d || i == stock_e || i == stock_f ||
            i == stock_g)
            particle.binarySolution[i] = 1;
        else
            particle.binarySolution[i] = 0;
    }
    double fitness = 0.0;
#if STOCK == 1
    fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c, stock_d,
                                stock_e, stock_f, stock_g, PERCENT, PERCENT, PERCENT, PERCENT, PERCENT, PERCENT,
                                PERCENT, 6);
#elif STOCK == 2
    for (int i = 0; i <= PERCENT; i++) {
        fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c,
                                    stock_d, stock_e, stock_f, stock_g, i, i, i, i, i, i,
                                    PERCENT - i, -1);
        if (best < fitness) {
            best = fitness;
            allot_a = i;
            allot_b = i;
            allot_c = i;
            allot_d = i;
            allot_e = i;
            allot_f = i;
            allot_g = PERCENT - i;
        }
        std::cout << i << endl;
    }
    fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c, stock_d,
                                stock_e, stock_f, stock_g, allot_a, allot_b, allot_c, allot_d, allot_e, allot_f,
                                allot_g, 6);
#elif STOCK == 3
    for (int i = 0; i <= PERCENT; i++) {
        for (int j = 0; j <= PERCENT - i; j++) {
            std::cout << i << " / " << PERCENT << "    " << j << " / " << PERCENT << endl;
                        fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c,
                                                    stock_d, stock_e, stock_f,stock_g, i,i,i,i, i, j,
                                                    PERCENT - i - j , -1);
                        if (best < fitness) {
                            best = fitness;
                            allot_a = i;
                            allot_b = i;
                            allot_c = i;
                            allot_d = i;
                            allot_e = i;
                            allot_f = j;
                            allot_g = PERCENT - i - j  ;
                        }
                    }
                }
    fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c, stock_d,
                                stock_e, stock_f, stock_g, allot_a, allot_b, allot_c, allot_d, allot_e, allot_f,
                                allot_g, 6);
#elif STOCK == 4
    for (int i = 0; i <= PERCENT; i++) {
        for (int j = 0; j <= PERCENT - i; j++) {
            std::cout << i << " / " << PERCENT << "    " << j << " / " << PERCENT << endl;
            for (int k = 0; k <= PERCENT - i - j; k++) {
                fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c,
                                            stock_d, stock_e, stock_f, stock_g, i, i, i, i, j, k,
                                            PERCENT - i - j - k, -1);
                if (best < fitness) {
                    best = fitness;
                    allot_a = i;
                    allot_b = i;
                    allot_c = i;
                    allot_d = i;
                    allot_e = j;
                    allot_f = k;
                    allot_g = PERCENT - i - j - k;
                }
            }
        }
    }
    fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c, stock_d,
                                stock_e, stock_f, stock_g, allot_a, allot_b, allot_c, allot_d, allot_e, allot_f,
                                allot_g, 6);
#elif STOCK == 5
    for (int i = 0; i <= PERCENT; i++) {
        for (int j = 0; j <= PERCENT - i; j++) {
           std::cout << i << " / " << PERCENT << "    " << j << " / " << PERCENT << endl;
            for (int k = 0; k <= PERCENT - i - j; k++) {
                for (int l = 0; l <= PERCENT - i - j - k; l++) {
                    fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c,
                                                stock_d, stock_e, stock_f, stock_g, i, i, i, j, k, l,
                                                PERCENT - i - j - k - l, -1);
                    if (best < fitness) {
                        best = fitness;
                        allot_a = i;
                        allot_b = i;
                        allot_c = i;
                        allot_d = j;
                        allot_e = k;
                        allot_f = l;
                        allot_g = PERCENT - i - j - k - l;
                    }
                }
            }
        }
    }
    fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c, stock_d,
                                stock_e, stock_f, stock_g, allot_a, allot_b, allot_c, allot_d, allot_e, allot_f,
                                allot_g, 6);
#elif STOCK == 6
    for (int i = 0; i <= PERCENT; i++) {
        for (int j = 0; j <= PERCENT - i; j++) {
            std::cout << i << " / " << PERCENT << "    " << j << " / " << PERCENT << endl;
            for (int k = 0; k <= PERCENT - i - j; k++) {
                for (int l = 0; l <= PERCENT - i - j - k; l++) {
                    for (int m = 0; m <= PERCENT - i - j - k - l; m++) {
                        fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c,
                                                    stock_d, stock_e, stock_f, stock_g, i, i, j, k, l, m,
                                                    PERCENT - i - j - k - l - m, -1);
                        if (best < fitness) {
                            best = fitness;
                            allot_a = i;
                            allot_b = i;
                            allot_c = j;
                            allot_d = k;
                            allot_e = l;
                            allot_f = m;
                            allot_g = PERCENT - i - j - k - l - m;
                        }
                    }
                }
            }
        }
    }
    fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c, stock_d,
                                stock_e, stock_f, stock_g, allot_a, allot_b, allot_c, allot_d, allot_e, allot_f,
                                allot_g, 6);
#elif STOCK == 7
    for (int i = 0; i <= PERCENT; i++) {
        for (int j = 0; j <= PERCENT - i; j++) {
            std::cout << i << " / " << PERCENT << "    " << j << " / " << PERCENT << endl;
            for (int k = 0; k <= PERCENT - i - j; k++) {
                for (int l = 0; l <= PERCENT - i - j - k; l++) {
                    for (int m = 0; m <= PERCENT - i - j - k - l; m++) {
                        for (int n = 0; n <= PERCENT - i - j - k - l - m; n++) {
                            fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c,
                                                        stock_d,
                                                        stock_e, stock_f, stock_g, i, j, k, l, m, n,
                                                        PERCENT - i - j - k - l - m - n, -1);
                            if (best < fitness) {
                                best = fitness;
                                allot_a = i;
                                allot_b = j;
                                allot_c = k;
                                allot_d = l;
                                allot_e = m;
                                allot_f = n;
                                allot_g = PERCENT - i - j - k - l - m - n;
                            }
                        }
                    }
                }
            }
        }
    }
    fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c, stock_d,
                                stock_e, stock_f, stock_g, allot_a, allot_b, allot_c, allot_d, allot_e, allot_f,
                                allot_g, 6);
#endif
}

int main() {
    auto start = std::chrono::steady_clock::now();

//    if (tag == "US/Y2Y") {
//        for (int i = 2; i <= 3; i++) {
//            if (STOCK == 1) {
//                test(i, 1, 1, 1, 1, 1, 1, 1);
//            } else if (STOCK == 2) {
//                test(i, 1, 1, 1, 1, 1, 1, 0);
//            } else if (STOCK == 3) {
//                test(i, 1, 1, 1, 1, 1, 0, 2);
//            } else if (STOCK == 4) {
//                test(i, 1, 1, 1, 1, 0, 2, 3);
//            } else if (STOCK == 5) {
//                test(i, 1, 1, 1, 0, 2, 3, 19);
//            } else if (STOCK == 6) {
//                test(i, 1, 1, 0, 2, 3, 19, 5);
//            }
//        }
//    }

    if (tag == "US/Y2Y") {
        for (int i = 4; i <= 7; i++) {
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7) {
                test(i, 1,  0, 2, 3, 20, 5,6);
            }
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
    std::cout << endl << endl << "Time taken: " << std::chrono::duration<double>(end - start).count() << " s"
              << std::endl;
    return 0;
}
