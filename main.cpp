#include "GNQTS.h"
#include <cfloat>
#include <chrono>

#define STOCK 2

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
    }
    model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c, stock_d,
                      stock_e, stock_f, stock_g, allot_a, allot_b, allot_c, allot_d, allot_e, allot_f,
                      allot_g, 6);

    model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c, stock_d,
                      stock_e, stock_f, stock_g, 50, 50, 50, 50, 50, 50, 50, 6);
#elif STOCK == 3
    for (int i = 0; i <= PERCENT; i++) {
        for (int j = 0; j <= PERCENT - i; j++) {
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
    model->one_to_two(period, particle.binarySolution, stock_a, stock_b, stock_c, stock_d,
                               stock_e, stock_f, stock_g, allot_a, allot_b, allot_c, allot_d, allot_e, allot_f,
                               allot_g, 6);
#endif
}

int main() {
    auto start = std::chrono::steady_clock::now();
    int pe ;
    int a;
    int b;

    if (tag == "US/Y2Y") {
        pe = 2;
        a = 5;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
    } else if (tag == "US/Y2H") {
        pe = 9;
        a = 5;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
    }  else if (tag == "US/Y2Q") {
        pe = 16;
        a = 5;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 17;
        a = 5;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 24;
        a = 1;
        b = 2;
        test(pe, a, a, a, a, a, a, b);
    }else if (tag == "US/Y2M") {
        pe = 38;
        a = 2;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
        pe = 39;
        a = 2;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
        pe = 45;
        a = 5;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 46;
        test(pe, a, a, a, a, a, a, b);
        pe = 48;
        test(pe, a, a, a, a, a, a, b);
        pe = 49;
        test(pe, a, a, a, a, a, a, b);
        pe = 69;
        a = 1;
        b = 2;
        test(pe, a, a, a, a, a, a, b);
        pe = 70;
        test(pe, a, a, a, a, a, a, b);
        pe = 84;
        a = 1;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
    } else if (tag == "US/H2H") {
        pe = 6;
        a = 2;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
        pe = 8;
        a = 5;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 9;
        a = 0;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 11;
        a = 1;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 12;
        a = 1;
        b = 2;
        test(pe, a, a, a, a, a, a, b);
    } else if (tag == "US/H2Q") {
        pe = 15;
        a = 5;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 16;
        a = 2;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 17;
        a = 0;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 21;
        a = 1;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 22;
        a = 1;
        b = 2;
        test(pe, a, a, a, a, a, a, b);
        pe = 23;
        test(pe, a, a, a, a, a, a, b);
    } else if (tag == "US/H2M") {
        pe = 31;
        a = 2;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
        pe = 35;
        test(pe, a, a, a, a, a, a, b);
        pe = 36;
        test(pe, a, a, a, a, a, a, b);
        pe = 39;
        a = 1;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
        pe = 43;
        a = 5;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 45;
        a = 2;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 46;
        test(pe, a, a, a, a, a, a, b);
        pe = 49;
        a = 0;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 61;
        a = 1;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 64;
        a = 1;
        b = 2;
        test(pe, a, a, a, a, a, a, b);
        pe = 66;
        test(pe, a, a, a, a, a, a, b);
        pe = 67;
        test(pe, a, a, a, a, a, a, b);
        pe = 69;
        test(pe, a, a, a, a, a, a, b);
        pe = 71;
        a = 0;
        b = 1;
        test(pe, a, a, a, a, a, a, b);
        pe = 84;
        a = 0;
        b = 3;
        test(pe, a, a, a, a, a, a, b);
    } else if (tag == "US/H#") {
        pe = 7;
        a = 2;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
        pe = 9;
        a = 5;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 10;
        a = 0;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 12;
        a = 1;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 13;
        a = 1;
        b = 2;
        test(pe, a, a, a, a, a, a, b);
    } else if (tag == "US/Q2Q") {
        pe = 11;
        a = 2;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
        pe = 13;
        a = 2;
        b = 3;
        test(pe, a, a, a, a, a, a, b);
        pe = 14;
        a = 5;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 17;
        a = 1;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 18;
        a = 0;
        b = 1;
        test(pe, a, a, a, a, a, a, b);
        pe = 19;
        a = 2;
        b = 6;
        test(pe, a, a, a, a, a, a, b);
        pe = 20;
        a = 6;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 21;
        a = 2;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 28;
        a = 0;
        b = 3;
        test(pe, a, a, a, a, a, a, b);
    } else if (tag == "US/Q2M") {
        pe = 29;
        a = 2;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
        pe = 30;
        test(pe, a, a, a, a, a, a, b);
       pe = 31;
        test(pe, a, a, a, a, a, a, b);
       pe = 33;
        test(pe, a, a, a, a, a, a, b);
        pe = 36;
        a = 1;
        b = 2;
        test(pe, a, a, a, a, a, a, b);
        pe = 37;
        a = 2;
        b = 3;
        test(pe, a, a, a, a, a, a, b);
        pe = 40;
        a = 5;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 49;
        a = 1;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 50;
        a = 0;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 52;
        a = 0;
        b = 1;
        test(pe, a, a, a, a, a, a, b);
        pe = 53;
        a = 0;
        b = 6;
        test(pe, a, a, a, a, a, a, b);
        pe = 54;
        a = 5;
        b = 6;
        test(pe, a, a, a, a, a, a, b);

        pe = 55;
        a = 2;
        b = 6;
        test(pe, a, a, a, a, a, a, b);
        pe = 58;
        a = 6;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 61;
        a = 2;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 63;
        a = 2;
        b = 3;
        test(pe, a, a, a, a, a, a, b);
        pe = 68;
        test(pe, a, a, a, a, a, a, b);
        pe = 77;
        a = 0;
        b = 1;
        test(pe, a, a, a, a, a, a, b);
        pe = 82;
        a = 0;
        b = 3;
        test(pe, a, a, a, a, a, a, b);
    } else if (tag == "US/Q#") {
        pe = 14;
        a = 2;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
        pe = 16;
        a = 2;
        b = 3;
        test(pe, a, a, a, a, a, a, b);
        pe = 17;
        a = 5;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 20;
        a = 1;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 21;
        a = 0;
        b = 1;
        test(pe, a, a, a, a, a, a, b);
        pe = 22;
        a = 2;
        b = 6;
        test(pe, a, a, a, a, a, a, b);
        pe = 23;
        a = 6;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 24;
        a = 2;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
    } else if (tag == "US/M2M") {
        pe = 36;
        a = 2;
        b = 3;
        test(pe, a, a, a, a, a, a, b);
        pe = 40;
        a = 0;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 41;
        a = 2;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 44;
        a = 1;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
        pe = 48;
        a = 1;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 54;
        a = 3;
        b = 6;
        test(pe, a, a, a, a, a, a, b);
        pe = 57;
        a = 0;
        b = 6;
        test(pe, a, a, a, a, a, a, b);
        pe = 59;
        a = 1;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 61;
        a = 3;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 62;
        a = 2;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 66;
        a = 1;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
        pe = 67;
        a = 2;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
        pe = 68;
        a = 1;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 70;
        a = 1;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 72;
        a = 6;
        b = 20;
        test(pe, a, a, a, a, a, a, b);
        pe = 83;
        a = 0;
        b = 5;
        test(pe, a, a, a, a, a, a, b);
    } else if (tag == "US/M#") {

    }

/*
    if (tag == "US/Y2Y") {
        for (int i = 2; i <= 7; i++) {
            std::cout << "period: " << i << " / " << 7 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 3) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 4) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 3) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 4) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 3) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 4) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    } else if (tag == "US/H2H") {
        for (int i = 3; i <= 14; i++) {
            std::cout << "period: " << i << " / " << 14 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 5) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 6) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 5) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 6) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 5) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 6) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    } else if (tag == "US/Q2Q") {
        for (int i = 5; i <= 28; i++) {
            std::cout << "period: " << i << " / " << 28 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 9) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 10) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 9) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 10) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 9) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 10) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    } else if (tag == "US/M2M") {
//        for (int i = 84; i <= 84; i++) {
        for (int i = 13; i <= 84; i++) {
            std::cout << "period: " << i << " / " << 84 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 25) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 26) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 25) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 26) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 25) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 26) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    } else if (tag == "US/Y2H") {
        for (int i = 3; i <= 14; i++) {
            std::cout << "period: " << i << " / " << 14 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 6) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 7) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 6) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 7) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 6) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 7) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    } else if (tag == "US/Y2Q") {
        for (int i = 5; i <= 28; i++) {
            std::cout << "period: " << i << " / " << 28 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 12) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 13) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 12) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 13) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 12) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 13) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    } else if (tag == "US/Y2M") {
        for (int i = 13; i <= 84; i++) {
            std::cout << "period: " << i << " / " << 84 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 36) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 37) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 36) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 37) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 36) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 37) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    } else if (tag == "US/H2Q") {
        for (int i = 5; i <= 28; i++) {
            std::cout << "period: " << i << " / " << 28 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 10) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 11) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 10) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 11) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 10) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 11) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    } else if (tag == "US/H2M") {
        for (int i = 13; i <= 84; i++) {
            std::cout << "period: " << i << " / " << 84 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 30) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 31) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 30) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 31) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 30) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 31) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    } else if (tag == "US/Q2M") {
        for (int i = 13; i <= 84; i++) {
            std::cout << "period: " << i << " / " << 84 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 27) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 28) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 27) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 28) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 27) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 28) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    } else if (tag == "US/H#") {
        for (int i = 3; i <= 14; i++) {
            std::cout << "period: " << i << " / " << 14 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 6) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 7) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 6) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 7) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 6) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 7) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    } else if (tag == "US/Q#") {
        for (int i = 5; i <= 28; i++) {
            std::cout << "period: " << i << " / " << 28 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 12) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 13) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 12) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 13) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 12) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 13) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    } else if (tag == "US/M#") {
        for (int i = 13; i <= 84; i++) {
            std::cout << "period: " << i << " / " << 84 << " " << endl;
            if (STOCK == 1) {
                test(i, 1, 1, 1, 1, 1, 1, 1);
            } else if (STOCK == 2) {
                test(i, 1, 1, 1, 1, 1, 1, 0);
            } else if (STOCK == 3) {
                test(i, 1, 1, 1, 1, 1, 0, 2);
            } else if (STOCK == 4) {
                test(i, 1, 1, 1, 1, 0, 2, 3);
            } else if (STOCK == 5 && i <= 36) {
                test(i, 1, 1, 1, 0, 2, 3, 19);
            } else if (STOCK == 5 && i >= 37) {
                test(i, 1, 1, 1, 0, 2, 3, 20);
            } else if (STOCK == 6 && i <= 36) {
                test(i, 1, 1, 0, 2, 3, 19, 5);
            } else if (STOCK == 6 && i >= 37) {
                test(i, 1, 1, 0, 2, 3, 20, 5);
            } else if (STOCK == 7 && i <= 36) {
                test(i, 1, 0, 2, 3, 19, 5, 6);
            } else if (STOCK == 7 && i >= 37) {
                test(i, 1, 0, 2, 3, 20, 5, 6);
            }
        }
    }
*/

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
        model->align->expect_return = 0;
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
                allAlign->expect_return = model->align->expect_return;
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
//    system("pause");
    return 0;
}
