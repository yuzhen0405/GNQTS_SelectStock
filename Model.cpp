//
// Created by Irene Chen on 2020/2/3.
//

#include "Model.h"
#include <cmath>
#include <sstream>

using namespace std;


Model::Model() {
    this->align = nullptr;
}

Model::~Model() {
    delete[] stock;
}

void Model::readfile(const string &path) {
    ifstream inFile(path, ios::in);
    string line;

    getline(inFile, line);
    stringstream ss(line);

    string stockSymbol;
    int countStock = 0;
    int countDay = 0;

    while (getline(ss, stockSymbol, ',')) {
        countStock++;
    }

    while (getline(inFile, line)) {
        countDay++;
    }

    this->num_of_stock = countStock;
    this->num_of_day = countDay;

    inFile.close();
}

void Model::getStock(const string &path) {
    ifstream inFile(path, ios::in);

    string line;

    getline(inFile, line);
    stringstream ss(line);

    char comma;
    string stockSymbol;
    int count = 0;
    for (int i = 0; i < this->num_of_stock; i++) {
        getline(ss, stockSymbol, ',');

        stringstream symbol;
        symbol << stockSymbol;
        symbol >> this->stock[i].symbol;
    }

    int countStock = 0;
    int countDay = 0;

    while (getline(inFile, line)) {
        countStock = 0;
        stringstream ss(line);

        char comma;
        double price;

        while (ss >> price >> comma) {
            this->stock[countStock].price[countDay] = price;
            countStock++;
        }
        countDay++;
    }
    inFile.close();
}

void Model::nextPeriod(int period) {
    string path = "../data/" + tag + "/" + trainPeriod[period];
    readfile(path);
    this->stock = new Stock[this->num_of_stock];

    for (int i = 0; i < this->num_of_stock; i++) {
        this->stock[i].setSize(this->num_of_day);
    }

    getStock(path);

    delete this->align;
    this->align = new Align();

    this->align->setStock(this->num_of_stock, this->num_of_day);

    for (int i = 0; i < this->num_of_stock; i++) {
        this->align->stock[i].symbol = this->stock[i].symbol;
        for (int j = 0; j < this->num_of_day; j++) {
            this->stock[i].fs[j] = 0.0;
        }
    }
}

double Model::getFitness(int *binarySolution, int HW) {
    if (HW == 1) {
        for (int i = 0; i < this->num_of_stock; i++) {
            align->binarySolution[i] = binarySolution[i];
        }
    }

    /* allot fund */
    int num = 0;
    for (int i = 0; i < this->num_of_stock; i++) {
        if (binarySolution[i] == 1) {
            num++;
        }
    }
    int avgFund = FUND / num;
    for (int i = 0; i < this->num_of_stock; i++) {
        stock[i].avg_fund = avgFund;
    }
    int leftover = FUND - avgFund * num;
    if (HW == 1) {
        align->num = num;
        for (int i = 0; i < this->num_of_stock; i++) {
            align->stock[i].avg_fund = stock[i].avg_fund;
        }
    }

    /* calc amount */
    int *amount = new int[num_of_stock];
    for (int i = 0; i < num_of_stock; i++) {
        if (binarySolution[i] == 0) {
            amount[i] = 0;
        } else if (binarySolution[i] == 1) {
            amount[i] = floor(avgFund / (stock[i].price[0] * SHARE + stock[i].price[0] * (SHARE * FEE)));
        }
        if (HW == 1) {
            align->amount[i] = amount[i];
        }
    }

    /* calc balance */
    double totalBalance = 0.0;
    double *balance = new double[num_of_stock];
    for (int i = 0; i < num_of_stock; i++) {
        if (binarySolution[i] == 0) {
            balance[i] = 0.0;
        } else {
            balance[i] = avgFund - amount[i] * stock[i].price[0] * SHARE - amount[i] * stock[i].price[0] * SHARE * FEE;
            totalBalance += balance[i];
        }
        if (HW == 1) {
            align->balance[i] = balance[i];
        }
    }

    /* calc fee */
    double *fee = new double[num_of_stock];
    for (int i = 0; i < num_of_stock; i++) {
        if (binarySolution[i] == 1) {
            fee[i] = stock[i].price[0] * amount[i] * SHARE * FEE;
        } else {
            fee[i] = 0.0;
        }
    }

    /* calc individual real FS */
    for (int i = 0; i < num_of_stock; i++) {
        for (int j = 0; j < num_of_day; j++) {
            if (binarySolution[i] == 1) {
                if (j == 0) {
                    stock[i].fs[j] = avgFund - stock[i].price[0] * amount[i] * SHARE * FEE;
                } else {
                    stock[i].fs[j] =
                            stock[i].price[j] * amount[i] * SHARE - stock[i].price[j] * amount[i] * SHARE * FEE -
                            stock[i].price[j] * amount[i] * SHARE * TAX + balance[i];
                }
            } else {
                stock[i].fs[j] = 0.0;
            }
            if (HW == 1) {
                align->stock[i].fs[j] = stock[i].fs[j];
            }
        }
    }

    /* calc real FS */
    double *realFS = new double[num_of_day];

    for (int i = 0; i < num_of_day; i++) {
        realFS[i] = 0.0;
        for (int j = 0; j < num_of_stock; j++) {
            realFS[i] += stock[j].fs[i];
        }
        realFS[i] += leftover;
        if (HW == 1) {
            align->FS[i] = realFS[i];
            align->final_fund = realFS[i];
        }
    }

    /* calc M, (expect_reward), (slope) */
    double tmpMFraction = 0.0;
    int tmpMDenominator = 0;
    for (int i = 0; i < num_of_day; i++) {
        tmpMFraction += (i + 1) * realFS[i] - (i + 1) * FUND;
        tmpMDenominator += (i + 1) * (i + 1);
    }
    double expect_reward = tmpMFraction / tmpMDenominator;
    if (HW == 1) {
        align->expect_reward = expect_reward;
    }

    /* calc Yi */
    /* calc risk */
    double risk = 0.0;
    double *Yi = new double[num_of_day];
    for (int i = 0; i < num_of_day; i++) {
        Yi[i] = 0.0;
        Yi[i] += expect_reward * (i + 1) + FUND;
        risk += (realFS[i] - Yi[i]) * (realFS[i] - Yi[i]);
    }
    risk = sqrt(risk / num_of_day);
    if (HW == 1) {
        align->risk = risk;
    }

    double trendValue;
    /* calc trend value */
    if (expect_reward > 0) {
        trendValue = expect_reward / risk;
    } else {
        trendValue = expect_reward * risk;
    }
    if (HW == 1) {
        if (trendValue < 0) {
            align->gBest = 0;
        } else {
            align->gBest = trendValue;
        }
    }

    delete[] amount;
    delete[] balance;
    delete[] fee;
    delete[] realFS;
    delete[] Yi;
    return trendValue;
}

/******************************************************************************************************/
double
Model::one_to_two(int period, int *binarySolution, int stock_a, int stock_b, int stock_c, int stock_d, int stock_e, int stock_f, int stock_g,
                  int allot_a, int allot_b, int allot_c, int allot_d, int allot_e, int allot_f, int allot_g, int HW) {
    if (HW == 6) {
        align->initial_fund = 10000000;
        for (int i = 0; i < this->num_of_stock; i++) {
            align->binarySolution[i] = binarySolution[i];
        }
    }

    /* allot fund */
    for (int i = 0; i < this->num_of_stock; i++) {
        stock[i].avg_fund = 0.0;
        if (i == stock_a) {
            stock[i].avg_fund = FUND * allot_a / PERCENT;
        }
        if (i == stock_b) {
            stock[i].avg_fund = FUND * allot_b / PERCENT;
        }
        if (i == stock_c) {
            stock[i].avg_fund = FUND * allot_c / PERCENT;
        }
        if (i == stock_d) {
            stock[i].avg_fund = FUND * allot_d / PERCENT;
        }
        if (i == stock_e) {
            stock[i].avg_fund = FUND * allot_e / PERCENT;
        }
        if (i == stock_f) {
            stock[i].avg_fund = FUND * allot_f / PERCENT;
        }
        if (i == stock_g) {
            stock[i].avg_fund = FUND * allot_g / PERCENT;
        }
        if (HW == 6) {
            align->stock[i].avg_fund = stock[i].avg_fund;
        }
    }
    int leftover = FUND;
    for (int i = 0; i < this->num_of_stock; i++) {
        leftover -= stock[i].avg_fund;
    }

    /* calc amount */
    int *amount = new int[num_of_stock];
    for (int i = 0; i < num_of_stock; i++) {
        if (binarySolution[i] == 0) {
            amount[i] = 0;
        } else if (binarySolution[i] == 1) {
            amount[i] = floor(stock[i].avg_fund / (stock[i].price[0] * SHARE + stock[i].price[0] * (SHARE * FEE)));
        }
        if (HW == 6) {
            align->amount[i] = amount[i];
        }
    }

    /* calc balance */
    double totalBalance = 0.0;
    double *balance = new double[num_of_stock];
    for (int i = 0; i < num_of_stock; i++) {
        if (binarySolution[i] == 0) {
            balance[i] = 0.0;
        } else {
            balance[i] = stock[i].avg_fund - amount[i] * stock[i].price[0] * SHARE -
                         amount[i] * stock[i].price[0] * SHARE * FEE;
            totalBalance += balance[i];
        }
        if (HW == 6) {
            align->balance[i] = 0.0;
            align->balance[i] = balance[i];
        }
    }

    /* calc fee */
    double *fee = new double[num_of_stock];
    for (int i = 0; i < num_of_stock; i++) {
        if (binarySolution[i] == 1) {
            fee[i] = stock[i].price[0] * amount[i] * SHARE * FEE;
        } else {
            fee[i] = 0.0;
        }
    }

    /* calc individual real FS */
    for (int i = 0; i < num_of_stock; i++) {
        for (int j = 0; j < num_of_day; j++) {
            if (binarySolution[i] == 1) {
                if (j == 0) {
                    stock[i].fs[j] = stock[i].avg_fund - stock[i].price[0] * amount[i] * SHARE * FEE;
                } else {
                    stock[i].fs[j] =
                            stock[i].price[j] * amount[i] * SHARE - stock[i].price[j] * amount[i] * SHARE * FEE -
                            stock[i].price[j] * amount[i] * SHARE * TAX + balance[i];
                }
            } else {
                stock[i].fs[j] = 0.0;
            }
            if (HW == 6) {
                align->stock[i].fs[j] = 0.0;
                align->stock[i].fs[j] = stock[i].fs[j];
            }
        }
    }

    /* calc real FS */
    double *realFS = new double[num_of_day];

    for (int i = 0; i < num_of_day; i++) {
        realFS[i] = 0.0;
        for (int j = 0; j < num_of_stock; j++) {
            realFS[i] += stock[j].fs[i];
        }
        realFS[i] += leftover;
        if (HW == 6) {
            align->FS[i] = 0.0;
            align->final_fund = 0.0;
            align->FS[i] = realFS[i];
            align->final_fund = realFS[i];
        }
    }

    /* calc M, (expect_reward), (slope) */
    double tmpMFraction = 0.0;
    int tmpMDenominator = 0;
    for (int i = 0; i < num_of_day; i++) {
        tmpMFraction += (i + 1) * realFS[i] - (i + 1) * FUND;
        tmpMDenominator += (i + 1) * (i + 1);
    }
    double expect_reward = tmpMFraction / tmpMDenominator;
    if (HW == 6) {
        align->expect_reward = 0.0;
        align->expect_reward = expect_reward;
    }

    /* calc Yi */
    /* calc risk */
    double risk = 0.0;
    double *Yi = new double[num_of_day];
    for (int i = 0; i < num_of_day; i++) {
        Yi[i] = 0.0;
        Yi[i] += expect_reward * (i + 1) + FUND;
        risk += (realFS[i] - Yi[i]) * (realFS[i] - Yi[i]);
    }
    risk = sqrt(risk / num_of_day);
    if (HW == 6) {
        align->risk = 0.0;
        align->risk = risk;
    }

    double trendValue;
    /* calc trend value */
    if (expect_reward > 0) {
        trendValue = expect_reward / risk;
    } else {
        trendValue = expect_reward * risk;
    }
    if (HW == 6) {
        align->gBest = 0.0;
        align->gBest = trendValue;
        align->align(period);
    }

    delete[] balance;
    delete[] fee;
    delete[] realFS;
    delete[] Yi;
    return trendValue;
}