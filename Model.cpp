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
    cout << stock[24].symbol << endl;
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
double Model::one_to_two(int *binarySolution, int stock_a, int stock_b, int allot_a, int allot_b, int HW) {
    for (int i = 0; i < num_of_stock; i++) {
        if (i == stock_a || i == stock_b) {
            binarySolution[i] = 1;
        } else {
            binarySolution[i] = 0;
        }
    }

    stock[stock_a].avg_fund = FUND * allot_a / 10000;
    stock[stock_b].avg_fund = FUND * allot_b / 10000;
    int leftover = FUND - stock[stock_a].avg_fund - stock[stock_b].avg_fund;

    /* calc amount */
    int amount_a = 0;
    int amount_b = 0;
    amount_a = floor(
            stock[stock_a].avg_fund / (stock[stock_a].price[0] * SHARE + stock[stock_a].price[0] * (SHARE * FEE)));
    amount_b = floor(
            stock[stock_b].avg_fund / (stock[stock_b].price[0] * SHARE + stock[stock_b].price[0] * (SHARE * FEE)));
    if (HW == 1) {
        return floor(FUND / (stock[stock_a].price[0] * SHARE + stock[stock_a].price[0] * (SHARE * FEE)));
    }
    if (HW == 2) {
        return floor(FUND / (stock[stock_b].price[0] * SHARE + stock[stock_b].price[0] * (SHARE * FEE)));
    }
    /* calc balance */
    double totalBalance = 0.0;
    double *balance = new double[num_of_stock];
    balance[stock_a] = stock[stock_a].avg_fund - amount_a * stock[stock_a].price[0] * SHARE -
                       amount_a * stock[stock_a].price[0] * SHARE * FEE;
    balance[stock_b] = stock[stock_b].avg_fund - amount_b * stock[stock_b].price[0] * SHARE -
                       amount_b * stock[stock_b].price[0] * SHARE * FEE;
    totalBalance = balance[stock_a] + balance[stock_b];

    /* calc fee */
    double *fee = new double[num_of_stock];
    fee[stock_a] = stock[stock_a].price[0] * amount_a * SHARE * FEE;
    fee[stock_b] = stock[stock_b].price[0] * amount_b * SHARE * FEE;

    /* calc individual real FS */
    stock[stock_a].fs[0] = stock[stock_a].avg_fund - stock[stock_a].price[0] * amount_a * SHARE * FEE;
    stock[stock_b].fs[0] = stock[stock_b].avg_fund - stock[stock_b].price[0] * amount_b * SHARE * FEE;

    for (int j = 0; j < num_of_day; j++) {
        stock[stock_a].fs[j] =
                stock[stock_a].price[j] * amount_a * SHARE - stock[stock_a].price[j] * amount_a * SHARE * FEE -
                stock[stock_a].price[j] * amount_a * SHARE * TAX + balance[stock_a];
        stock[stock_b].fs[j] =
                stock[stock_b].price[j] * amount_b * SHARE - stock[stock_b].price[j] * amount_b * SHARE * FEE -
                stock[stock_b].price[j] * amount_b * SHARE * TAX + balance[stock_b];
    }

/* calc real FS */
    double *realFS = new double[num_of_day];

    for (int i = 0; i < num_of_day; i++) {
        realFS[i] = 0.0;
        realFS[i] = stock[stock_a].fs[i] + stock[stock_b].fs[i];
        realFS[i] += leftover;
    }

/* calc M, (expect_reward), (slope) */
    double tmpMFraction = 0.0;
    int tmpMDenominator = 0;
    for (int i = 0; i < num_of_day; i++) {
        tmpMFraction += (i + 1) * realFS[i] - (i + 1) * FUND;
        tmpMDenominator += (i + 1) * (i + 1);
    }
    double expect_reward = tmpMFraction / tmpMDenominator;
    if (HW == 3) {
        return expect_reward;
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
    if (HW == 4) {
        return risk;
    }
    double trendValue;
/* calc trend value */
    if (expect_reward > 0) {
        trendValue = expect_reward / risk;
    } else {
        trendValue = expect_reward * risk;
    }
    if (HW == 6) {
        std::cout << "|" << stock[stock_a].symbol << "(" << stock_a << ")  |  " << stock[stock_b].symbol << "("
                  << stock_b << ")  |  " << endl
                  << "|:------:|:--------:|:--------:|" <<
                  endl;

        cout << "| fund | 10000000  |" << "10000000 |" <<
             endl;
        cout << "| amount |" << one_to_two(binarySolution, stock_a, stock_b, 10000, 0, 1) << " | "
             << one_to_two(binarySolution, stock_a, stock_b, 0, 10000, 2) << " |" << endl;
        cout << "| expect return | <font color=red> " << setprecision(15)
             << one_to_two(binarySolution, stock_a, stock_b, 10000, 0, 3)
             << "</font> | "
             << one_to_two(binarySolution, stock_a, stock_b, 0, 10000, 3) << "|" << endl;
        cout << "| risk |<font color=red>" << setprecision(15)
             << one_to_two(binarySolution, stock_a, stock_b, 10000, 0, 4) << "</font> | "
             << one_to_two(binarySolution, stock_a, stock_b, 0, 10000, 4) << "|" << endl;
        cout << "| fitness |<font color=red>" << setprecision(15)
             << one_to_two(binarySolution, stock_a, stock_b, 10000, 0, 0) << "</font> | "
             << one_to_two(binarySolution, stock_a, stock_b, 0, 10000, 0) << " |" << endl;
        if (one_to_two(binarySolution, stock_a, stock_b, 10000, 0, 0) >= 0 &&
            one_to_two(binarySolution, stock_a, stock_b, 0, 10000, 0) >= 0) {

            cout << "| fitness ratio |" << setprecision(15)
                 << one_to_two(binarySolution, stock_a, stock_b, 10000, 0, 0) /
                    (one_to_two(binarySolution, stock_a, stock_b, 10000, 0, 0) +
                     one_to_two(binarySolution, stock_a, stock_b, 0, 10000, 0))
                 << "| "
                 << setprecision(15) << one_to_two(binarySolution, stock_a, stock_b, 0, 10000, 0) /
                                        (one_to_two(binarySolution, stock_a, stock_b, 10000, 0, 0) +
                                         one_to_two(binarySolution, stock_a, stock_b, 0, 10000, 0)) << "|" << endl
                 << endl;
        } else {
            cout << "| fitness ratio | ==X== | ==X== |" << endl << endl;
        }
    }

    if (HW == 7) {
        std::cout << "|" << stock[stock_a].symbol << "(" << stock_a << ")  |  " << stock[stock_b].symbol << "("
                  << stock_b << ")  |  " << endl
                  << "|:------:|:--------:|:--------:|" <<
                  endl;

        cout << "|ratio|" << setprecision(4) << (float) allot_a / 100 << " % |" << (float) allot_b / 100 << " %|"
             <<
             endl;
        cout << "|fund|" << stock[stock_a].avg_fund << " |" << stock[stock_b].avg_fund << "|" <<
             endl;
        cout << "|amount|" << amount_a << "| " << amount_b << "|" << endl <<
             endl;
        string tmp = "+";
        double tmpExpect_return = one_to_two(binarySolution, stock_a, stock_b, 10000, 0, 3);

        if (expect_reward - tmpExpect_return < 0) {
            tmp = "-";
        }
        cout << "> <font color=red> expect return: " << setprecision(15) << expect_reward << " ( ==" << tmp << "== "
             << abs(expect_reward - tmpExpect_return) << ") " << endl;
        double tmpRisk = one_to_two(binarySolution, stock_a, stock_b, 10000, 0, 4);
        tmp = "+";
        if (risk - tmpRisk < 0) {
            tmp = "-";
        }
        cout << "> risk: " << setprecision(20) << risk << " ( ==" << tmp << "== " << abs(risk - tmpRisk) << ") "
             << endl;
        double tmpTrendValue = one_to_two(binarySolution, stock_a, stock_b, 10000, 0, 5);
        tmp = "+";
        if (trendValue - tmpTrendValue < 0) {
            tmp = "-";
        }
        if (tmpTrendValue >= 0 && trendValue >= 0) {
            cout << "> trend value: " << setprecision(15) << trendValue << " ( ==" << tmp << "== "
                 <<
                 abs(trendValue
                     - tmpTrendValue) << ") " << "</font>" << endl << ">" << endl
                 << "... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..."
                 <<
                 endl;
        } else {
            cout << "> trend value: " << setprecision(15) << trendValue << "</font>" << endl << ">" << endl
                 << "... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..."
                 <<
                 endl;
        }
    }

    delete[] balance;
    delete[] fee;
    delete[] realFS;
    delete[] Yi;
    return trendValue;
}