//
// Created by Irene Chen on 2020/2/3.
//

#include "Model.h"
#include <cmath>
#include <sstream>

using namespace std;


Model::Model() {

}

Model::~Model() {
    delete[] stock;
}

void Model::readfile(const string &path) {
    ifstream inFile(path, ios::in);

    string line;

    getline(inFile, line);
    stringstream ss(line);

    char comma;
    int stockSymbol;
    int countStock = 0;
    int countDay = 0;

    while (ss >> stockSymbol >> comma) {
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
    int stockSymbol;

    for (int i = 0; i < this->num_of_stock; i++) {
        ss >> stockSymbol >> comma;
        this->stock[i].symbol = stockSymbol;
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

    for (int i = 0; i < this->num_of_stock; i++) {
        for (int j = 0; j < this->num_of_day; j++) {
            this->stock[i].fs[j] = 0.0;
        }
    }
}

double Model::getFitness(int *binarySolution, int gen, int HW) {
    if (HW == 1) {
        align->find_gBest_gen = gen;
        for (int i = 0; i < this->num_of_stock; i++) {
            align->binarySolution[i] = binarySolution[i];
        }
    }

    for (int j = 0; j < this->num_of_stock; j++) {
        align->stock[j].avg_fund = 0;
        align->balance[j] = 0;
        for (int k = 0; k < this->num_of_day; k++) {
            align->stock[j].fs[k] = 0.0;
            align->FS[k] = 0.0;
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
            amount[i] = avgFund / (stock[i].price[0] * SHARE + stock[i].price[0] * (SHARE * FEE));
        }
        if (HW == 1) {
            align->amount[i] = amount[i];
        }
    }

    /* calc balance */
    double totalBalance = 0;
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

    delete[] amount;
    delete[] balance;
    delete[] fee;
    delete[] realFS;
    delete[] Yi;
    return trendValue;
}

