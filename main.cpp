#include "GNQTS.h"
#include <cfloat>
#include <chrono>

#define STOCK 4


void test(int p, int a, int b, int c, int d) {
    int period = p - 1;
    int stock_a = a;
    int stock_b = b;
    int stock_c = c;
    int stock_d = d;
    double best = -DBL_MAX;
    int allot_a = 0;
    int allot_b = 0;
    int allot_c = 0;
    Model *model = new Model();
    model->nextPeriod(period);

    Particle particle;
    particle.setSize(model->num_of_stock);
    Align align;
    align.setStock(model->num_of_stock, model->num_of_day);

    for (int i = 0; i < model->num_of_stock; i++) {
        if (i == stock_a || i == stock_b || i == stock_c || i == stock_d)
            particle.binarySolution[i] = 1;
        else
            particle.binarySolution[i] = 0;
    }
    double fitness = 0.0;
    for (int i = 0; i <= PERCENT; i++) {
        for (int j = 0; j <= PERCENT - i; j++) {
            for (int k = 0; k <= PERCENT - i - j; k++) {
                fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c,
                                            stock_d, i, j, k, 100 - i - j - k, -1);
                if (best < fitness) {
                    best = fitness;
                    allot_a = i;
                    allot_b = j;
                    allot_c = k;
                }
            }
        }
    }

    int flag = 0;
    Logger logger("../log/" + tag + "/result_period" + std::to_string(period + 1) + ".csv", 20);
    for (int i = 0; i <= PERCENT; i++) {
        for (int j = 0; j <= PERCENT - i; j++) {
            for (int k = 0; k <= PERCENT - i - j; k++) {
                fitness = model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c,
                                            stock_d, i, j, k, 100 - i - j - k, -1);
                if (best == fitness && flag == 0) {
                    logger.writeSpace("period:");
                    logger.write(period + 1);
                    logger.writeSpace(", fitness:");
                    logger.write(best);
                    logger.write(", ");
                    logger.writeSpace(i);
                    logger.writeSpace(j);
                    logger.write(PERCENT - i - j);
                    flag++;
                } else if (best == fitness) {
                    logger.write(", ");
                    logger.writeSpace(i);
                    logger.writeSpace(j);
                    logger.write(PERCENT - i - j);
                }
            }
        }
    }
    logger.writeLine("");
    model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c,
                      stock_d, allot_a, allot_b, allot_c, 100 - allot_a - allot_b - allot_c, 6);
}

int main() {
    auto start = std::chrono::steady_clock::now();
    if (STOCK == 4) {
        if (tag == "Y2Y") {
            test(3, 4, 24, 41, 45);
            test(7, 2, 24, 33, 47);
        } else if (tag == "H2H") {
            test(5, 2, 24, 26, 45);
            test(10, 18, 19, 22, 26);
        } else if (tag == "Q2Q") {
            test(7, 9, 15, 24, 41);
            test(12, 8, 15, 24, 40);
            test(17, 27, 28, 33, 41);
            test(21, 21, 40, 42, 45);
            test(22, 11, 24, 26, 48);
            test(23, 10, 18, 38, 41);
            test(26, 20, 25, 40, 47);
        } else if (tag == "M2M") {
            test(5, 8, 20, 27, 39);
            test(12, 20, 22, 24, 27);
            test(23, 4, 11, 45, 46);
            test(31, 21, 27, 42, 47);
            test(32, 8, 10, 15, 43);
            test(34, 2, 13, 15, 27);
            test(59, 19, 40, 42, 45);
            test(60, 8, 19, 45, 46);
            test(65, 4, 5, 41, 47);
            test(79, 0, 1, 25, 42);
            test(82, 4, 23, 27, 41);
            test(91, 7, 16, 21, 27);
            test(94, 3, 9, 23, 38);
            test(96, 14, 20, 39, 41);
        } else if (tag == "Y2H") {
            test(2, 5, 40, 41, 44);
            test(4, 5, 24, 37, 40);
            test(5, 4, 24, 41, 45);
            test(13, 2, 24, 33, 47);
        } else if (tag == "Y2Q") {
            test(2, 4, 19, 41, 44);
            test(3, 5, 40, 41, 44);
            test(7, 5, 24, 37, 40);
            test(9, 4, 24, 41, 45);
            test(12, 10, 12, 22, 45);
            test(16, 0, 2, 13, 42);
            test(25, 2, 24, 33, 47);
        } else if (tag == "Y2M") {
            test(4, 4, 19, 41, 44);
            test(7, 5, 40, 41, 44);
            test(9, 5, 40, 41, 47);
            test(11, 5, 40, 41, 47);
            test(12, 12, 28, 40, 47);
            test(19, 5, 24, 37, 40);
            test(23, 8, 17, 24, 39);
            test(25, 4, 24, 41, 45);
            test(31, 2, 24, 45, 46);
            test(34, 10, 12, 22, 45);
            test(36, 2, 10, 21, 45);
            test(39, 2, 15, 20, 46);
            test(46, 0, 2, 13, 42);
            test(59, 8, 16, 23, 42);
            test(72, 2, 24, 33, 42);
            test(73, 2, 24, 33, 47);
            test(81, 16, 24, 42, 47);
            test(83, 16, 41, 42, 47);
        } else if (tag == "H2Q") {
            test(4, 24, 39, 40, 47);
            test(6, 5, 27, 37, 40);
            test(9, 2, 24, 26, 45);
            test(19, 18, 19, 22, 26);
            test(22, 30, 42, 45, 46);
        } else if (tag == "H2M") {
            test(2, 5, 20, 41, 47);
            test(3, 5, 20, 41, 47);
            test(5, 4, 5, 12, 44);
            test(10, 24, 39, 40, 47);
            test(16, 5, 27, 37, 40);
            test(25, 2, 24, 26, 45);
            test(35, 2, 13, 27, 42);
            test(54, 19, 21, 24, 28);
            test(55, 18, 19, 22, 26);
            test(58, 16, 26, 31, 36);
            test(59, 7, 30, 38, 42);
            test(64, 30, 42, 45, 46);
        } else if (tag == "Q2M") {
            test(5, 5, 9, 13, 39);
            test(11, 2, 3, 7, 24);
            test(14, 17, 24, 27, 31);
            test(19, 9, 15, 24, 41);
            test(20, 9, 15, 24, 41);
            test(34, 8, 15, 24, 40);
            test(35, 0, 13, 20, 28);
            test(38, 9, 33, 41, 43);
            test(48, 27, 28, 30, 33);
            test(49, 27, 28, 33, 41);
            test(61, 21, 40, 42, 45);
            test(64, 11, 24, 26, 48);
            test(65, 24, 26, 30, 41);
            test(67, 10, 18, 38, 41);
            test(72, 16, 17, 27, 41);
            test(76, 20, 25, 40, 47);
            test(77, 5, 9, 12, 25);
            test(80, 12, 18, 41, 42);
        } else if (tag == "H#") {
            test(6, 2, 24, 26, 45);
            test(11, 18, 19, 22, 26);
        } else if (tag == "Q#") {
            test(2, 8, 25, 41, 42);
            test(10, 9, 15, 24, 41);
            test(15, 8, 15, 24, 40);
            test(20, 27, 28, 33, 41);
            test(24, 21, 40, 42, 45);
            test(25, 11, 24, 26, 48);
            test(26, 10, 18, 38, 41);
            test(29, 20, 25, 40, 47);
        } else if (tag == "M#") {
            test(4, 5, 9, 14, 22);
            test(9, 18, 19, 37, 41);
            test(16, 8, 20, 27, 39);
            test(23, 20, 22, 24, 27);
            test(34, 4, 11, 45, 46);
            test(42, 21, 27, 42, 47);
            test(43, 8, 10, 15, 43);
            test(45, 2, 13, 15, 27);
            test(70, 19, 40, 42, 45);
            test(71, 8, 19, 45, 46);
            test(76, 4, 5, 41, 47);
            test(90, 0, 1, 25, 42);
            test(93, 4, 23, 27, 41);
        }

    } else if (STOCK == 1) {
        if (tag == "H2H") {
            test(13, 24, 24, 24, 24);
        } else if (tag == "M2M") {
            test(9, 4, 4, 4, 4);
            test(15, 44, 44, 44, 44);
            test(21, 26, 26, 26, 26);
            test(25, 42, 42, 42, 42);
            test(58, 7, 7, 7, 7);
            test(67, 38, 38, 38, 38);
            test(68, 24, 24, 24, 24);
            test(69, 2, 2, 2, 2);
            test(72, 45, 45, 45, 45);
            test(73, 16, 16, 16, 16);
        } else if (tag == "Y2H") {
            test(14, 24, 24, 24, 24);
        } else if (tag == "Y2Q") {
            test(27, 24, 24, 24, 24);
        } else if (tag == "Y2M") {
            test(74, 24, 24, 24, 24);
            test(78, 24, 24, 24, 24);
            test(79, 24, 24, 24, 24);
        } else if (tag == "H2Q") {
            test(25, 24, 24, 24, 24);
        } else if (tag == "H2M") {
            test(71, 2, 2, 2, 2);
            test(72, 24, 24, 24, 24);
            test(73, 24, 24, 24, 24);
        } else if (tag == "Q2M") {
            test(6, 27, 27, 27, 27);
            test(8, 40, 40, 40, 40);
            test(23, 26, 26, 26, 26);
            test(59, 20, 20, 20, 20);
            test(60, 42, 42, 42, 42);
            test(69, 24, 24, 24, 24);
            test(74, 16, 16, 16, 16);
        } else if (tag == "H#") {
            test(14, 24, 24, 24, 24);
        } else if (tag == "M#") {
            test(6, 25, 25, 25, 25);
            test(20, 4, 4, 4, 4);
            test(26, 44, 44, 44, 44);
            test(32, 26, 26, 26, 26);
            test(36, 42, 42, 42, 42);
            test(69, 7, 7, 7, 7);
            test(78, 38, 38, 38, 38);
            test(79, 24, 24, 24, 24);
            test(80, 2, 2, 2, 2);
            test(83, 45, 45, 45, 45);
            test(84, 16, 16, 16, 16);
        }

    } else if (STOCK == 2) {
        if (tag == "H2H") {
            test(2, 5, 5, 5, 39);
        } else if (tag == "Q2Q") {
            test(2, 4, 4, 4, 5);
            test(8, 21, 21, 21, 24);
            test(20, 2, 2, 2, 7);
        } else if (tag == "M2M") {
            test(3, 4, 4, 4, 13);
            test(14, 4, 4, 4, 17);
            test(24, 10, 10, 10, 45);
            test(29, 0, 0, 0, 37);
            test(35, 0, 0, 0, 42);
            test(43, 33, 33, 33, 46);
            test(64, 10, 10, 10, 35);
            test(66, 10, 10, 10, 18);
            test(70, 27, 27, 27, 47);
            test(84, 3, 3, 3, 35);
        } else if (tag == "Y2H") {
            test(6, 18, 18, 18, 45);
        } else if (tag == "Y2Q") {
            test(11, 18, 18, 18, 45);
        } else if (tag == "Y2M") {
            test(30, 18, 18, 18, 45);
            test(33, 22, 22, 22, 45);
            test(77, 2, 2, 2, 24);
        } else if (tag == "H2Q") {
            test(3, 5, 5, 5, 39);
            test(24, 2, 2, 2, 33);
        } else if (tag == "H2M") {
            test(7, 5, 5, 5, 39);
            test(8, 5, 5, 5, 39);
            test(11, 24, 24, 24, 40);
            test(21, 40, 40, 40, 41);
            test(23, 24, 24, 24, 45);
            test(24, 24, 24, 24, 45);
            test(27, 45, 45, 45, 46);
            test(60, 7, 7, 7, 20);
            test(70, 2, 2, 2, 33);
            test(74, 16, 16, 16, 24);
        } else if (tag == "Q2M") {
            test(3, 20, 20, 20, 28);
            test(4, 4, 4, 4, 5);
            test(17, 0, 0, 0, 44);
            test(22, 21, 21, 21, 24);
            test(24, 16, 16, 16, 45);
            test(27, 42, 42, 42, 48);
            test(30, 15, 15, 15, 46);
            test(58, 2, 2, 2, 7);
        } else if (tag == "H#") {
            test(3, 5, 5, 5, 39);
        } else if (tag == "Q#") {
            test(5, 4, 4, 4, 5);
            test(11, 21, 21, 21, 24);
            test(23, 2, 2, 2, 7);
        } else if (tag == "M#") {
            test(14, 4, 4, 4, 13);
            test(25, 4, 4, 4, 17);
            test(35, 10, 10, 10, 45);
            test(40, 0, 0, 0, 37);
            test(46, 0, 0, 0, 42);
            test(54, 33, 33, 33, 46);
            test(75, 10, 10, 10, 35);
            test(77, 10, 10, 10, 18);
            test(81, 27, 27, 27, 47);
            test(95, 3, 3, 3, 35);
        }
    } else if (STOCK == 3) {
//        if (tag == "Y2Y") {
//            test(2, 5, 5, 39, 47);
//        } else if (tag == "H2H") {
//            test(14, 25, 25, 42, 44);
//        } else if (tag == "Q2Q") {
//            test(1, 20, 20, 24, 48);
//            test(3, 27, 27, 39, 40);
//            test(6, 4, 4, 9, 44);
//            test(9, 10, 10, 45, 48);
//            test(24, 2, 2, 24, 41);
//            test(25, 16, 16, 17, 33);
//        } else if (tag == "M2M") {
//            test(2, 4, 4, 20, 44);
//            test(6, 39, 39, 40, 47);
//            test(16, 0, 0, 8, 9);
//            test(19, 24, 24, 31, 41);
//            test(22, 13, 13, 19, 26);
//            test(28, 15, 15, 17, 28);
//            test(30, 11, 11, 43, 46);
//            test(33, 16, 16, 27, 28);
//            test(37, 4, 4, 9, 47);
//            test(44, 17, 17, 26, 36);
//            test(45, 15, 15, 20, 22);
//            test(62, 25, 25, 44, 45);
//            test(74, 20, 20, 25, 40);
//            test(75, 8, 8, 13, 18);
//            test(77, 2, 2, 12, 36);
//            test(78, 12, 12, 40, 41);
//            test(80, 0, 0, 24, 34);
//            test(83, 4, 4, 41, 44);
//            test(85, 9, 9, 23, 43);
//            test(89, 7, 7, 13, 44);
//        } else if (tag == "Y2H") {
//            test(3, 5, 5, 39, 47);
//        } else if (tag == "Y2Q") {
//            test(5, 5, 5, 39, 47);
//            test(26, 2, 2, 24, 47);
//            test(28, 5, 5, 11, 16);
//        } else if (tag == "Y2M") {
//            test(5, 4, 4, 8, 14);
//            test(13, 5, 5, 39, 47);
//            test(26, 40, 40, 41, 45);
//            test(32, 2, 2, 26, 45);
//            test(75, 2, 2, 24, 47);
//            test(76, 2, 2, 24, 47);
//            test(82, 5, 5, 11, 16);
//        } else if (tag == "H2Q") {
//            test(12, 2, 2, 27, 46);
//            test(26, 16, 16, 17, 24);
//            test(27, 25, 25, 42, 44);
//            test(28, 36, 36, 39, 42);
//        } else if (tag == "H2M") {
//            test(6, 12, 12, 28, 40);
//            test(9, 12, 12, 39, 47);
//            test(26, 2, 2, 26, 45);
//            test(33, 15, 15, 25, 46);
//            test(34, 2, 2, 27, 46);
//            test(38, 13, 13, 20, 24);
//            test(39, 0, 0, 13, 20);
//            test(51, 16, 16, 28, 33);
//            test(62, 7, 7, 20, 42);
//            test(63, 20, 20, 42, 45);
//            test(75, 16, 16, 17, 24);
//            test(76, 16, 16, 17, 24);
//            test(77, 16, 16, 17, 24);
//            test(79, 25, 25, 42, 44);
//            test(82, 36, 36, 39, 42);
//            test(83, 16, 16, 19, 41);
//        } else if (tag == "Q2M") {
//            test(1, 20, 24, 48);
//            test(7, 27, 39, 40);
//            test(16, 4, 9, 44);
//            test(18, 9, 24, 41);
//            test(21, 24, 40, 41);
//            test(25, 10, 45, 48);
//            test(26, 10, 45, 48);
//            test(44, 40, 41, 46);
//            test(50, 16, 28, 33);
//            test(70, 2, 24, 41);
//            test(71, 2, 3, 16);
//            test(73, 16, 17, 33);
//            test(75, 16, 24, 47);
//            test(84, 4, 5, 35);
//        } else if (tag == "H#") {
//            test(15, 25, 42, 44);
//        } else if (tag == "Q#") {
//            test(1, 3, 18, 26);
//            test(4, 20, 24, 48);
//            test(6, 27, 39, 40);
//            test(9, 4, 9, 44);
//            test(12, 10, 45, 48);
//            test(27, 2, 24, 41);
//            test(28, 16, 17, 33);
//        } else if (tag == "M#") {
//            test(1, 3, 18, 25);
//            test(2, 14, 21, 25);
//            test(10, 15, 20, 23);
//            test(13, 4, 20, 44);
//            test(17, 39, 40, 47);
//            test(27, 0, 8, 9);
//            test(30, 24, 31, 41);
//            test(33, 13, 19, 26);
//            test(39, 15, 17, 28);
//            test(41, 11, 43, 46);
//            test(44, 16, 27, 28);
//            test(48, 4, 9, 47);
//            test(55, 17, 26, 36);
//            test(56, 15, 20, 22);
//            test(73, 25, 44, 45);
//            test(85, 20, 25, 40);
//            test(86, 8, 13, 18);
//            test(88, 2, 12, 36);
//            test(89, 12, 40, 41);
//            test(91, 0, 24, 34);
//            test(94, 4, 41, 44);
//            test(96, 9, 23, 43);
//        }
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
