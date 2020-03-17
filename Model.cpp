//
// Created by Irene Chen on 2020/2/3.
//

#include "Model.h"
#include "Logger.h"
#include <cmath>
#include <sstream>

using namespace std;


Model::Model(int period) {
    readfile(period);
    getStock(period);
}

Model::~Model() {
    delete[] stock;
}

void Model::readfile(int period) {
//    ifstream inFile("../data/M2M/train_2009_12(2009 Q1).csv", ios::in);
    string M2M_train[] = {"../data/M2M/train_2009_12(2009 Q1).csv", "../data/M2M/train_2010_01(2010 Q1).csv",
                          "../data/M2M/train_2010_02(2010 Q1).csv", "../data/M2M/train_2010_03(2010 Q1).csv",
                          "../data/M2M/train_2010_04(2010 Q1).csv", "../data/M2M/train_2010_05(2010 Q1).csv",
                          "../data/M2M/train_2010_06(2010 Q1).csv", "../data/M2M/train_2010_07(2010 Q1).csv",
                          "../data/M2M/train_2010_08(2010 Q1).csv", "../data/M2M/train_2010_09(2010 Q1).csv",
                          "../data/M2M/train_2010_10(2010 Q1).csv", "../data/M2M/train_2010_11(2010 Q1).csv",
                          "../data/M2M/train_2010_12(2010 Q1).csv", "../data/M2M/train_2011_01(2011 Q1).csv",
                          "../data/M2M/train_2011_02(2011 Q1).csv", "../data/M2M/train_2011_03(2011 Q1).csv",
                          "../data/M2M/train_2011_04(2011 Q1).csv", "../data/M2M/train_2011_05(2011 Q1).csv",
                          "../data/M2M/train_2011_06(2011 Q1).csv", "../data/M2M/train_2011_07(2011 Q1).csv",
                          "../data/M2M/train_2011_08(2011 Q1).csv", "../data/M2M/train_2011_09(2011 Q1).csv",
                          "../data/M2M/train_2011_10(2011 Q1).csv", "../data/M2M/train_2011_11(2011 Q1).csv",
                          "../data/M2M/train_2011_12(2011 Q1).csv", "../data/M2M/train_2012_01(2012 Q1).csv",
                          "../data/M2M/train_2012_02(2012 Q1).csv", "../data/M2M/train_2012_03(2012 Q1).csv",
                          "../data/M2M/train_2012_04(2012 Q1).csv", "../data/M2M/train_2012_05(2012 Q1).csv",
                          "../data/M2M/train_2012_06(2012 Q1).csv", "../data/M2M/train_2012_07(2012 Q1).csv",
                          "../data/M2M/train_2012_08(2012 Q1).csv", "../data/M2M/train_2012_09(2012 Q1).csv",
                          "../data/M2M/train_2012_10(2012 Q1).csv", "../data/M2M/train_2012_11(2012 Q1).csv",
                          "../data/M2M/train_2012_12(2012 Q1).csv", "../data/M2M/train_2013_01(2013 Q1).csv",
                          "../data/M2M/train_2013_02(2013 Q1).csv", "../data/M2M/train_2013_03(2013 Q1).csv",
                          "../data/M2M/train_2013_04(2013 Q1).csv", "../data/M2M/train_2013_05(2013 Q1).csv",
                          "../data/M2M/train_2013_06(2013 Q1).csv", "../data/M2M/train_2013_07(2013 Q1).csv",
                          "../data/M2M/train_2013_08(2013 Q1).csv", "../data/M2M/train_2013_09(2013 Q1).csv",
                          "../data/M2M/train_2013_10(2013 Q1).csv", "../data/M2M/train_2013_11(2013 Q1).csv",
                          "../data/M2M/train_2013_12(2013 Q1).csv", "../data/M2M/train_2014_01(2014 Q1).csv",
                          "../data/M2M/train_2014_02(2014 Q1).csv", "../data/M2M/train_2014_03(2014 Q1).csv",
                          "../data/M2M/train_2014_04(2014 Q1).csv", "../data/M2M/train_2014_05(2014 Q1).csv",
                          "../data/M2M/train_2014_06(2014 Q1).csv", "../data/M2M/train_2014_07(2014 Q1).csv",
                          "../data/M2M/train_2014_08(2014 Q1).csv", "../data/M2M/train_2014_09(2014 Q1).csv",
                          "../data/M2M/train_2014_10(2014 Q1).csv", "../data/M2M/train_2014_11(2014 Q1).csv",
                          "../data/M2M/train_2014_12(2014 Q1).csv", "../data/M2M/train_2015_01(2015 Q1).csv",
                          "../data/M2M/train_2015_02(2015 Q1).csv", "../data/M2M/train_2015_03(2015 Q1).csv",
                          "../data/M2M/train_2015_04(2015 Q1).csv", "../data/M2M/train_2015_05(2015 Q1).csv",
                          "../data/M2M/train_2015_06(2015 Q1).csv", "../data/M2M/train_2015_07(2015 Q1).csv",
                          "../data/M2M/train_2015_08(2015 Q1).csv", "../data/M2M/train_2015_09(2015 Q1).csv",
                          "../data/M2M/train_2015_10(2015 Q1).csv", "../data/M2M/train_2015_11(2015 Q1).csv",
                          "../data/M2M/train_2015_12(2015 Q1).csv", "../data/M2M/train_2016_01(2016 Q1).csv",
                          "../data/M2M/train_2016_02(2016 Q1).csv", "../data/M2M/train_2016_03(2016 Q1).csv",
                          "../data/M2M/train_2016_04(2016 Q1).csv", "../data/M2M/train_2016_05(2016 Q1).csv",
                          "../data/M2M/train_2016_06(2016 Q1).csv", "../data/M2M/train_2016_07(2016 Q1).csv",
                          "../data/M2M/train_2016_08(2016 Q1).csv", "../data/M2M/train_2016_09(2016 Q1).csv",
                          "../data/M2M/train_2016_10(2016 Q1).csv", "../data/M2M/train_2016_11(2016 Q1).csv",
                          "../data/M2M/train_2016_12(2016 Q1).csv", "../data/M2M/train_2017_01(2017 Q1).csv",
                          "../data/M2M/train_2017_02(2017 Q1).csv", "../data/M2M/train_2017_03(2017 Q1).csv",
                          "../data/M2M/train_2017_04(2017 Q1).csv", "../data/M2M/train_2017_05(2017 Q1).csv",
                          "../data/M2M/train_2017_06(2017 Q1).csv", "../data/M2M/train_2017_07(2017 Q1).csv",
                          "../data/M2M/train_2017_08(2017 Q1).csv", "../data/M2M/train_2017_09(2017 Q1).csv",
                          "../data/M2M/train_2017_10(2017 Q1).csv", "../data/M2M/train_2017_11(2017 Q1).csv",
                          "../data/M2M/train_2017_12(2017 Q1).csv"};

    ifstream inFile(M2M_train[period], ios::in);

    string line;
    int countStock = 0;
    int countDay = 0;

    getline(inFile, line);
    stringstream ss(line);
    char comma;
    int stockSymbol;
    while (ss >> stockSymbol >> comma) {
        countStock++;
    }

    while (getline(inFile, line)) {
        countDay++;
    }

    this->NUM_OF_STOCK = countStock;
    this->NUM_OF_DAY = countDay;

    this->stock = new Stock[this->NUM_OF_STOCK];
    for (int i = 0; i < this->NUM_OF_STOCK; i++) {
        this->stock[i].setSize(this->NUM_OF_DAY);
    }
    inFile.close();
}

void Model::getStock(int period) {
//    ifstream inFile("../data/M2M/train_2009_12(2009 Q1).csv", ios::in);
    string M2M_train[] = {"../data/M2M/train_2009_12(2009 Q1).csv", "../data/M2M/train_2010_01(2010 Q1).csv",
                          "../data/M2M/train_2010_02(2010 Q1).csv", "../data/M2M/train_2010_03(2010 Q1).csv",
                          "../data/M2M/train_2010_04(2010 Q1).csv", "../data/M2M/train_2010_05(2010 Q1).csv",
                          "../data/M2M/train_2010_06(2010 Q1).csv", "../data/M2M/train_2010_07(2010 Q1).csv",
                          "../data/M2M/train_2010_08(2010 Q1).csv", "../data/M2M/train_2010_09(2010 Q1).csv",
                          "../data/M2M/train_2010_10(2010 Q1).csv", "../data/M2M/train_2010_11(2010 Q1).csv",
                          "../data/M2M/train_2010_12(2010 Q1).csv", "../data/M2M/train_2011_01(2011 Q1).csv",
                          "../data/M2M/train_2011_02(2011 Q1).csv", "../data/M2M/train_2011_03(2011 Q1).csv",
                          "../data/M2M/train_2011_04(2011 Q1).csv", "../data/M2M/train_2011_05(2011 Q1).csv",
                          "../data/M2M/train_2011_06(2011 Q1).csv", "../data/M2M/train_2011_07(2011 Q1).csv",
                          "../data/M2M/train_2011_08(2011 Q1).csv", "../data/M2M/train_2011_09(2011 Q1).csv",
                          "../data/M2M/train_2011_10(2011 Q1).csv", "../data/M2M/train_2011_11(2011 Q1).csv",
                          "../data/M2M/train_2011_12(2011 Q1).csv", "../data/M2M/train_2012_01(2012 Q1).csv",
                          "../data/M2M/train_2012_02(2012 Q1).csv", "../data/M2M/train_2012_03(2012 Q1).csv",
                          "../data/M2M/train_2012_04(2012 Q1).csv", "../data/M2M/train_2012_05(2012 Q1).csv",
                          "../data/M2M/train_2012_06(2012 Q1).csv", "../data/M2M/train_2012_07(2012 Q1).csv",
                          "../data/M2M/train_2012_08(2012 Q1).csv", "../data/M2M/train_2012_09(2012 Q1).csv",
                          "../data/M2M/train_2012_10(2012 Q1).csv", "../data/M2M/train_2012_11(2012 Q1).csv",
                          "../data/M2M/train_2012_12(2012 Q1).csv", "../data/M2M/train_2013_01(2013 Q1).csv",
                          "../data/M2M/train_2013_02(2013 Q1).csv", "../data/M2M/train_2013_03(2013 Q1).csv",
                          "../data/M2M/train_2013_04(2013 Q1).csv", "../data/M2M/train_2013_05(2013 Q1).csv",
                          "../data/M2M/train_2013_06(2013 Q1).csv", "../data/M2M/train_2013_07(2013 Q1).csv",
                          "../data/M2M/train_2013_08(2013 Q1).csv", "../data/M2M/train_2013_09(2013 Q1).csv",
                          "../data/M2M/train_2013_10(2013 Q1).csv", "../data/M2M/train_2013_11(2013 Q1).csv",
                          "../data/M2M/train_2013_12(2013 Q1).csv", "../data/M2M/train_2014_01(2014 Q1).csv",
                          "../data/M2M/train_2014_02(2014 Q1).csv", "../data/M2M/train_2014_03(2014 Q1).csv",
                          "../data/M2M/train_2014_04(2014 Q1).csv", "../data/M2M/train_2014_05(2014 Q1).csv",
                          "../data/M2M/train_2014_06(2014 Q1).csv", "../data/M2M/train_2014_07(2014 Q1).csv",
                          "../data/M2M/train_2014_08(2014 Q1).csv", "../data/M2M/train_2014_09(2014 Q1).csv",
                          "../data/M2M/train_2014_10(2014 Q1).csv", "../data/M2M/train_2014_11(2014 Q1).csv",
                          "../data/M2M/train_2014_12(2014 Q1).csv", "../data/M2M/train_2015_01(2015 Q1).csv",
                          "../data/M2M/train_2015_02(2015 Q1).csv", "../data/M2M/train_2015_03(2015 Q1).csv",
                          "../data/M2M/train_2015_04(2015 Q1).csv", "../data/M2M/train_2015_05(2015 Q1).csv",
                          "../data/M2M/train_2015_06(2015 Q1).csv", "../data/M2M/train_2015_07(2015 Q1).csv",
                          "../data/M2M/train_2015_08(2015 Q1).csv", "../data/M2M/train_2015_09(2015 Q1).csv",
                          "../data/M2M/train_2015_10(2015 Q1).csv", "../data/M2M/train_2015_11(2015 Q1).csv",
                          "../data/M2M/train_2015_12(2015 Q1).csv", "../data/M2M/train_2016_01(2016 Q1).csv",
                          "../data/M2M/train_2016_02(2016 Q1).csv", "../data/M2M/train_2016_03(2016 Q1).csv",
                          "../data/M2M/train_2016_04(2016 Q1).csv", "../data/M2M/train_2016_05(2016 Q1).csv",
                          "../data/M2M/train_2016_06(2016 Q1).csv", "../data/M2M/train_2016_07(2016 Q1).csv",
                          "../data/M2M/train_2016_08(2016 Q1).csv", "../data/M2M/train_2016_09(2016 Q1).csv",
                          "../data/M2M/train_2016_10(2016 Q1).csv", "../data/M2M/train_2016_11(2016 Q1).csv",
                          "../data/M2M/train_2016_12(2016 Q1).csv", "../data/M2M/train_2017_01(2017 Q1).csv",
                          "../data/M2M/train_2017_02(2017 Q1).csv", "../data/M2M/train_2017_03(2017 Q1).csv",
                          "../data/M2M/train_2017_04(2017 Q1).csv", "../data/M2M/train_2017_05(2017 Q1).csv",
                          "../data/M2M/train_2017_06(2017 Q1).csv", "../data/M2M/train_2017_07(2017 Q1).csv",
                          "../data/M2M/train_2017_08(2017 Q1).csv", "../data/M2M/train_2017_09(2017 Q1).csv",
                          "../data/M2M/train_2017_10(2017 Q1).csv", "../data/M2M/train_2017_11(2017 Q1).csv",
                          "../data/M2M/train_2017_12(2017 Q1).csv"};
    ifstream inFile(M2M_train[period], ios::in);

    string line;

    getline(inFile, line);
    stringstream ss(line);
    char comma;
    int stockSymbol;
    for (int i = 0; i < this->NUM_OF_STOCK; i++) {
        ss >> stockSymbol >> comma;
        this->stock[i].symbol = stockSymbol;
    }
    int countStock = 0;
    int countDay = 0;

    while (getline(inFile, line)) {
        countStock = 0;
        stringstream ss(line);
        string str;
        char comma;
        double price;
        while (ss >> price >> comma) {
            this->stock[countStock].price[countDay] = price;
            countStock++;
        }
        countDay++;
    }
    inFile.close();

    string align_M2M_train[] = {"../log/train_2009_12(2009 Q1).csv", "../log/train_2010_01(2010 Q1).csv",
                                "../log/train_2010_02(2010 Q1).csv", "../log/train_2010_03(2010 Q1).csv",
                                "../log/train_2010_04(2010 Q1).csv", "../log/train_2010_05(2010 Q1).csv",
                                "../log/train_2010_06(2010 Q1).csv", "../log/train_2010_07(2010 Q1).csv",
                                "../log/train_2010_08(2010 Q1).csv", "../log/train_2010_09(2010 Q1).csv",
                                "../log/train_2010_10(2010 Q1).csv", "../log/train_2010_11(2010 Q1).csv",
                                "../log/train_2010_12(2010 Q1).csv", "../log/train_2011_01(2011 Q1).csv",
                                "../log/train_2011_02(2011 Q1).csv", "../log/train_2011_03(2011 Q1).csv",
                                "../log/train_2011_04(2011 Q1).csv", "../log/train_2011_05(2011 Q1).csv",
                                "../log/train_2011_06(2011 Q1).csv", "../log/train_2011_07(2011 Q1).csv",
                                "../log/train_2011_08(2011 Q1).csv", "../log/train_2011_09(2011 Q1).csv",
                                "../log/train_2011_10(2011 Q1).csv", "../log/train_2011_11(2011 Q1).csv",
                                "../log/train_2011_12(2011 Q1).csv", "../log/train_2012_01(2012 Q1).csv",
                                "../log/train_2012_02(2012 Q1).csv", "../log/train_2012_03(2012 Q1).csv",
                                "../log/train_2012_04(2012 Q1).csv", "../log/train_2012_05(2012 Q1).csv",
                                "../log/train_2012_06(2012 Q1).csv", "../log/train_2012_07(2012 Q1).csv",
                                "../log/train_2012_08(2012 Q1).csv", "../log/train_2012_09(2012 Q1).csv",
                                "../log/train_2012_10(2012 Q1).csv", "../log/train_2012_11(2012 Q1).csv",
                                "../log/train_2012_12(2012 Q1).csv", "../log/train_2013_01(2013 Q1).csv",
                                "../log/train_2013_02(2013 Q1).csv", "../log/train_2013_03(2013 Q1).csv",
                                "../log/train_2013_04(2013 Q1).csv", "../log/train_2013_05(2013 Q1).csv",
                                "../log/train_2013_06(2013 Q1).csv", "../log/train_2013_07(2013 Q1).csv",
                                "../log/train_2013_08(2013 Q1).csv", "../log/train_2013_09(2013 Q1).csv",
                                "../log/train_2013_10(2013 Q1).csv", "../log/train_2013_11(2013 Q1).csv",
                                "../log/train_2013_12(2013 Q1).csv", "../log/train_2014_01(2014 Q1).csv",
                                "../log/train_2014_02(2014 Q1).csv", "../log/train_2014_03(2014 Q1).csv",
                                "../log/train_2014_04(2014 Q1).csv", "../log/train_2014_05(2014 Q1).csv",
                                "../log/train_2014_06(2014 Q1).csv", "../log/train_2014_07(2014 Q1).csv",
                                "../log/train_2014_08(2014 Q1).csv", "../log/train_2014_09(2014 Q1).csv",
                                "../log/train_2014_10(2014 Q1).csv", "../log/train_2014_11(2014 Q1).csv",
                                "../log/train_2014_12(2014 Q1).csv", "../log/train_2015_01(2015 Q1).csv",
                                "../log/train_2015_02(2015 Q1).csv", "../log/train_2015_03(2015 Q1).csv",
                                "../log/train_2015_04(2015 Q1).csv", "../log/train_2015_05(2015 Q1).csv",
                                "../log/train_2015_06(2015 Q1).csv", "../log/train_2015_07(2015 Q1).csv",
                                "../log/train_2015_08(2015 Q1).csv", "../log/train_2015_09(2015 Q1).csv",
                                "../log/train_2015_10(2015 Q1).csv", "../log/train_2015_11(2015 Q1).csv",
                                "../log/train_2015_12(2015 Q1).csv", "../log/train_2016_01(2016 Q1).csv",
                                "../log/train_2016_02(2016 Q1).csv", "../log/train_2016_03(2016 Q1).csv",
                                "../log/train_2016_04(2016 Q1).csv", "../log/train_2016_05(2016 Q1).csv",
                                "../log/train_2016_06(2016 Q1).csv", "../log/train_2016_07(2016 Q1).csv",
                                "../log/train_2016_08(2016 Q1).csv", "../log/train_2016_09(2016 Q1).csv",
                                "../log/train_2016_10(2016 Q1).csv", "../log/train_2016_11(2016 Q1).csv",
                                "../log/train_2016_12(2016 Q1).csv", "../log/train_2017_01(2017 Q1).csv",
                                "../log/train_2017_02(2017 Q1).csv", "../log/train_2017_03(2017 Q1).csv",
                                "../log/train_2017_04(2017 Q1).csv", "../log/train_2017_05(2017 Q1).csv",
                                "../log/train_2017_06(2017 Q1).csv", "../log/train_2017_07(2017 Q1).csv",
                                "../log/train_2017_08(2017 Q1).csv", "../log/train_2017_09(2017 Q1).csv",
                                "../log/train_2017_10(2017 Q1).csv", "../log/train_2017_11(2017 Q1).csv",
                                "../log/train_2017_12(2017 Q1).csv"};

    Logger logger_align(align_M2M_train[period], 20);

}

double Model::getFitness(int *binarySolution, int gen, int individual, int HW, int period) {
    string align_M2M_train[] = {"../log/train_2009_12(2009 Q1).csv", "../log/train_2010_01(2010 Q1).csv",
                                "../log/train_2010_02(2010 Q1).csv", "../log/train_2010_03(2010 Q1).csv",
                                "../log/train_2010_04(2010 Q1).csv", "../log/train_2010_05(2010 Q1).csv",
                                "../log/train_2010_06(2010 Q1).csv", "../log/train_2010_07(2010 Q1).csv",
                                "../log/train_2010_08(2010 Q1).csv", "../log/train_2010_09(2010 Q1).csv",
                                "../log/train_2010_10(2010 Q1).csv", "../log/train_2010_11(2010 Q1).csv",
                                "../log/train_2010_12(2010 Q1).csv", "../log/train_2011_01(2011 Q1).csv",
                                "../log/train_2011_02(2011 Q1).csv", "../log/train_2011_03(2011 Q1).csv",
                                "../log/train_2011_04(2011 Q1).csv", "../log/train_2011_05(2011 Q1).csv",
                                "../log/train_2011_06(2011 Q1).csv", "../log/train_2011_07(2011 Q1).csv",
                                "../log/train_2011_08(2011 Q1).csv", "../log/train_2011_09(2011 Q1).csv",
                                "../log/train_2011_10(2011 Q1).csv", "../log/train_2011_11(2011 Q1).csv",
                                "../log/train_2011_12(2011 Q1).csv", "../log/train_2012_01(2012 Q1).csv",
                                "../log/train_2012_02(2012 Q1).csv", "../log/train_2012_03(2012 Q1).csv",
                                "../log/train_2012_04(2012 Q1).csv", "../log/train_2012_05(2012 Q1).csv",
                                "../log/train_2012_06(2012 Q1).csv", "../log/train_2012_07(2012 Q1).csv",
                                "../log/train_2012_08(2012 Q1).csv", "../log/train_2012_09(2012 Q1).csv",
                                "../log/train_2012_10(2012 Q1).csv", "../log/train_2012_11(2012 Q1).csv",
                                "../log/train_2012_12(2012 Q1).csv", "../log/train_2013_01(2013 Q1).csv",
                                "../log/train_2013_02(2013 Q1).csv", "../log/train_2013_03(2013 Q1).csv",
                                "../log/train_2013_04(2013 Q1).csv", "../log/train_2013_05(2013 Q1).csv",
                                "../log/train_2013_06(2013 Q1).csv", "../log/train_2013_07(2013 Q1).csv",
                                "../log/train_2013_08(2013 Q1).csv", "../log/train_2013_09(2013 Q1).csv",
                                "../log/train_2013_10(2013 Q1).csv", "../log/train_2013_11(2013 Q1).csv",
                                "../log/train_2013_12(2013 Q1).csv", "../log/train_2014_01(2014 Q1).csv",
                                "../log/train_2014_02(2014 Q1).csv", "../log/train_2014_03(2014 Q1).csv",
                                "../log/train_2014_04(2014 Q1).csv", "../log/train_2014_05(2014 Q1).csv",
                                "../log/train_2014_06(2014 Q1).csv", "../log/train_2014_07(2014 Q1).csv",
                                "../log/train_2014_08(2014 Q1).csv", "../log/train_2014_09(2014 Q1).csv",
                                "../log/train_2014_10(2014 Q1).csv", "../log/train_2014_11(2014 Q1).csv",
                                "../log/train_2014_12(2014 Q1).csv", "../log/train_2015_01(2015 Q1).csv",
                                "../log/train_2015_02(2015 Q1).csv", "../log/train_2015_03(2015 Q1).csv",
                                "../log/train_2015_04(2015 Q1).csv", "../log/train_2015_05(2015 Q1).csv",
                                "../log/train_2015_06(2015 Q1).csv", "../log/train_2015_07(2015 Q1).csv",
                                "../log/train_2015_08(2015 Q1).csv", "../log/train_2015_09(2015 Q1).csv",
                                "../log/train_2015_10(2015 Q1).csv", "../log/train_2015_11(2015 Q1).csv",
                                "../log/train_2015_12(2015 Q1).csv", "../log/train_2016_01(2016 Q1).csv",
                                "../log/train_2016_02(2016 Q1).csv", "../log/train_2016_03(2016 Q1).csv",
                                "../log/train_2016_04(2016 Q1).csv", "../log/train_2016_05(2016 Q1).csv",
                                "../log/train_2016_06(2016 Q1).csv", "../log/train_2016_07(2016 Q1).csv",
                                "../log/train_2016_08(2016 Q1).csv", "../log/train_2016_09(2016 Q1).csv",
                                "../log/train_2016_10(2016 Q1).csv", "../log/train_2016_11(2016 Q1).csv",
                                "../log/train_2016_12(2016 Q1).csv", "../log/train_2017_01(2017 Q1).csv",
                                "../log/train_2017_02(2017 Q1).csv", "../log/train_2017_03(2017 Q1).csv",
                                "../log/train_2017_04(2017 Q1).csv", "../log/train_2017_05(2017 Q1).csv",
                                "../log/train_2017_06(2017 Q1).csv", "../log/train_2017_07(2017 Q1).csv",
                                "../log/train_2017_08(2017 Q1).csv", "../log/train_2017_09(2017 Q1).csv",
                                "../log/train_2017_10(2017 Q1).csv", "../log/train_2017_11(2017 Q1).csv",
                                "../log/train_2017_12(2017 Q1).csv"};

    Logger logger_align(align_M2M_train[period], 20);
    Logger logger_allAlign("../log/allAlign.csv", 20);

    double totalBalance = 0; // ?R¡±?¡±F?¡ì?`?l¡ÔB

    /* allot fund */
    int num = 0;
    for (int i = 0; i < this->NUM_OF_STOCK; i++) {
        if (binarySolution[i] == 1) {
            num++;
        }
    }
    int avgFund = FUND / num;
    int leftover = FUND - avgFund * num;

    /* calc amount */
    int *amount = new int[NUM_OF_STOCK];
    for (int i = 0; i < NUM_OF_STOCK; i++) {
        if (binarySolution[i] == 0) {
            amount[i] = 0;
        }
        if (binarySolution[i] == 1) {
            amount[i] = avgFund / (stock[i].price[0] * SHARE + stock[i].price[0] * (SHARE * FEE));
        }
    }

    /* calc balance */
    double *balance = new double[NUM_OF_STOCK];
    for (int i = 0; i < NUM_OF_STOCK; i++) {
        if (binarySolution[i] == 0) {
            balance[i] = 0.0;
        } else {
            balance[i] = avgFund - amount[i] * stock[i].price[0] * SHARE - amount[i] * stock[i].price[0] * SHARE * FEE;
            totalBalance += balance[i];
        }
    }

    /* calc fee */
    double *fee = new double[NUM_OF_STOCK];
    for (int i = 0; i < NUM_OF_STOCK; i++) {
        if (binarySolution[i] == 1) {
            fee[i] = stock[i].price[0] * amount[i] * SHARE * FEE;
        } else {
            fee[i] = 0.0;
        }
    }

    /* calc individual real FS */
    for (int i = 0; i < NUM_OF_STOCK; i++) {
        for (int j = 0; j < NUM_OF_DAY; j++) {
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
        }
    }

    /* calc real FS */
    double *realFS = new double[NUM_OF_DAY];

    for (int i = 0; i < NUM_OF_DAY; i++) {
        realFS[i] = 0;
        for (int j = 0; j < NUM_OF_STOCK; j++) {
            realFS[i] += stock[j].fs[i];
        }
        realFS[i] += leftover;
    }

    /* calc M */
    double tmpMFraction = 0.0;
    int tmpMDenominator = 0;
    for (int i = 0; i < NUM_OF_DAY; i++) {
        tmpMFraction += (i + 1) * realFS[i] - (i + 1) * FUND;
        tmpMDenominator += (i + 1) * (i + 1);
    }
    double m = tmpMFraction / tmpMDenominator;

    /* calc Yi */
    /* calc risk */
    double risk = 0.0;
    double *Yi = new double[NUM_OF_DAY];
    for (int i = 0; i < NUM_OF_DAY; i++) {
        Yi[i] = 0.0;
        Yi[i] += m * (i + 1) + FUND;
        risk += (realFS[i] - Yi[i]) * (realFS[i] - Yi[i]);
    }
    risk = sqrt(risk / NUM_OF_DAY);
    double trendValue;
    /* calc trend value */
    if (m > 0) {
        trendValue = m / risk;
    } else {
        trendValue = m * risk;
    }

    if (HW == 1) {
        string M2M_train[] = {"../data/M2M/train_2009_12(2009 Q1).csv", "../data/M2M/train_2010_01(2010 Q1).csv",
                              "../data/M2M/train_2010_02(2010 Q1).csv", "../data/M2M/train_2010_03(2010 Q1).csv",
                              "../data/M2M/train_2010_04(2010 Q1).csv", "../data/M2M/train_2010_05(2010 Q1).csv",
                              "../data/M2M/train_2010_06(2010 Q1).csv", "../data/M2M/train_2010_07(2010 Q1).csv",
                              "../data/M2M/train_2010_08(2010 Q1).csv", "../data/M2M/train_2010_09(2010 Q1).csv",
                              "../data/M2M/train_2010_10(2010 Q1).csv", "../data/M2M/train_2010_11(2010 Q1).csv",
                              "../data/M2M/train_2010_12(2010 Q1).csv", "../data/M2M/train_2011_01(2011 Q1).csv",
                              "../data/M2M/train_2011_02(2011 Q1).csv", "../data/M2M/train_2011_03(2011 Q1).csv",
                              "../data/M2M/train_2011_04(2011 Q1).csv", "../data/M2M/train_2011_05(2011 Q1).csv",
                              "../data/M2M/train_2011_06(2011 Q1).csv", "../data/M2M/train_2011_07(2011 Q1).csv",
                              "../data/M2M/train_2011_08(2011 Q1).csv", "../data/M2M/train_2011_09(2011 Q1).csv",
                              "../data/M2M/train_2011_10(2011 Q1).csv", "../data/M2M/train_2011_11(2011 Q1).csv",
                              "../data/M2M/train_2011_12(2011 Q1).csv", "../data/M2M/train_2012_01(2012 Q1).csv",
                              "../data/M2M/train_2012_02(2012 Q1).csv", "../data/M2M/train_2012_03(2012 Q1).csv",
                              "../data/M2M/train_2012_04(2012 Q1).csv", "../data/M2M/train_2012_05(2012 Q1).csv",
                              "../data/M2M/train_2012_06(2012 Q1).csv", "../data/M2M/train_2012_07(2012 Q1).csv",
                              "../data/M2M/train_2012_08(2012 Q1).csv", "../data/M2M/train_2012_09(2012 Q1).csv",
                              "../data/M2M/train_2012_10(2012 Q1).csv", "../data/M2M/train_2012_11(2012 Q1).csv",
                              "../data/M2M/train_2012_12(2012 Q1).csv", "../data/M2M/train_2013_01(2013 Q1).csv",
                              "../data/M2M/train_2013_02(2013 Q1).csv", "../data/M2M/train_2013_03(2013 Q1).csv",
                              "../data/M2M/train_2013_04(2013 Q1).csv", "../data/M2M/train_2013_05(2013 Q1).csv",
                              "../data/M2M/train_2013_06(2013 Q1).csv", "../data/M2M/train_2013_07(2013 Q1).csv",
                              "../data/M2M/train_2013_08(2013 Q1).csv", "../data/M2M/train_2013_09(2013 Q1).csv",
                              "../data/M2M/train_2013_10(2013 Q1).csv", "../data/M2M/train_2013_11(2013 Q1).csv",
                              "../data/M2M/train_2013_12(2013 Q1).csv", "../data/M2M/train_2014_01(2014 Q1).csv",
                              "../data/M2M/train_2014_02(2014 Q1).csv", "../data/M2M/train_2014_03(2014 Q1).csv",
                              "../data/M2M/train_2014_04(2014 Q1).csv", "../data/M2M/train_2014_05(2014 Q1).csv",
                              "../data/M2M/train_2014_06(2014 Q1).csv", "../data/M2M/train_2014_07(2014 Q1).csv",
                              "../data/M2M/train_2014_08(2014 Q1).csv", "../data/M2M/train_2014_09(2014 Q1).csv",
                              "../data/M2M/train_2014_10(2014 Q1).csv", "../data/M2M/train_2014_11(2014 Q1).csv",
                              "../data/M2M/train_2014_12(2014 Q1).csv", "../data/M2M/train_2015_01(2015 Q1).csv",
                              "../data/M2M/train_2015_02(2015 Q1).csv", "../data/M2M/train_2015_03(2015 Q1).csv",
                              "../data/M2M/train_2015_04(2015 Q1).csv", "../data/M2M/train_2015_05(2015 Q1).csv",
                              "../data/M2M/train_2015_06(2015 Q1).csv", "../data/M2M/train_2015_07(2015 Q1).csv",
                              "../data/M2M/train_2015_08(2015 Q1).csv", "../data/M2M/train_2015_09(2015 Q1).csv",
                              "../data/M2M/train_2015_10(2015 Q1).csv", "../data/M2M/train_2015_11(2015 Q1).csv",
                              "../data/M2M/train_2015_12(2015 Q1).csv", "../data/M2M/train_2016_01(2016 Q1).csv",
                              "../data/M2M/train_2016_02(2016 Q1).csv", "../data/M2M/train_2016_03(2016 Q1).csv",
                              "../data/M2M/train_2016_04(2016 Q1).csv", "../data/M2M/train_2016_05(2016 Q1).csv",
                              "../data/M2M/train_2016_06(2016 Q1).csv", "../data/M2M/train_2016_07(2016 Q1).csv",
                              "../data/M2M/train_2016_08(2016 Q1).csv", "../data/M2M/train_2016_09(2016 Q1).csv",
                              "../data/M2M/train_2016_10(2016 Q1).csv", "../data/M2M/train_2016_11(2016 Q1).csv",
                              "../data/M2M/train_2016_12(2016 Q1).csv", "../data/M2M/train_2017_01(2017 Q1).csv",
                              "../data/M2M/train_2017_02(2017 Q1).csv", "../data/M2M/train_2017_03(2017 Q1).csv",
                              "../data/M2M/train_2017_04(2017 Q1).csv", "../data/M2M/train_2017_05(2017 Q1).csv",
                              "../data/M2M/train_2017_06(2017 Q1).csv", "../data/M2M/train_2017_07(2017 Q1).csv",
                              "../data/M2M/train_2017_08(2017 Q1).csv", "../data/M2M/train_2017_09(2017 Q1).csv",
                              "../data/M2M/train_2017_10(2017 Q1).csv", "../data/M2M/train_2017_11(2017 Q1).csv",
                              "../data/M2M/train_2017_12(2017 Q1).csv"};
        logger_align.writeComma("initial_fund");
        logger_align.writeLine(FUND);
        logger_align.writeComma("final_fund");
        logger_align.writeLine(realFS[NUM_OF_DAY - 1]);
        logger_align.writeComma("real_rewards");
        logger_align.writeLine(realFS[NUM_OF_DAY - 1] - FUND);
        logger_align.writeLine("");
        logger_align.writeComma("expect_rewards");
        logger_align.writeLine(m);
        logger_align.writeComma("risk");
        logger_align.writeLine(risk);
        logger_align.writeComma("Gbest");
        logger_align.writeLine(trendValue);
        logger_align.writeComma("find_gBest_gen");
        logger_align.writeLine(gen + 1);
        logger_align.writeComma("find_gBest_round#");
        logger_align.writeLine("1");
        logger_align.writeComma("find_gBest_times#");
        logger_align.writeLine("1");
        logger_align.writeLine("");
        logger_align.writeComma("portfolio_stocks");
        logger_align.writeLine(num);
        logger_align.writeComma("Stock#");

        for (int i = 0; i < NUM_OF_STOCK; i++) {
            if (binarySolution[i] == 1) {
                logger_align.write(stock[i].symbol);
                logger_align.write("(");
                logger_align.write(i);
                logger_align.writeComma(")");
            }
        }
        logger_align.writeLine("");
        logger_align.writeComma("amount");
        for (int i = 0; i < NUM_OF_STOCK; i++) {
            if (binarySolution[i] == 1) {
                logger_align.writeComma(amount[i]);
            }
        }
        logger_align.writeLine("");
        logger_align.writeComma("avg_fund");

        for (int i = 0; i < NUM_OF_STOCK; i++) {
            if (binarySolution[i] == 1) {
                logger_align.writeComma(avgFund);
            }
        }
        logger_align.writeLine("");
        logger_align.writeComma("leftover_fund");
        for (int i = 0; i < NUM_OF_STOCK; i++) {
            if (binarySolution[i] == 1) {
                logger_align.writeComma(balance[i]);
            }
        }
        logger_align.writeLine("");
        for (int i = 0; i < NUM_OF_DAY; i++) {
            logger_align.write("FS");
            logger_align.write("(");
            logger_align.write(i + 1);
            logger_align.writeComma(")");
            for (int j = 0; j < NUM_OF_STOCK; j++) {
                if (binarySolution[j] == 1) {
                    logger_align.writeComma(stock[j].fs[i]);
                }
            }
            logger_align.writeLine(realFS[i]);
        }

        logger_allAlign.writeComma(period + 1);
        logger_allAlign.writeComma(num);
        for (int i = 0; i < NUM_OF_STOCK; i++) {
            if (binarySolution[i] == 1) {
                logger_allAlign.write(stock[i].symbol);
                logger_allAlign.write("(");
                logger_allAlign.write(i);
                logger_allAlign.writeSpace(")");
            }
        }
        logger_allAlign.writeComma("");
        logger_allAlign.writeComma("Gbest");
        if (m < 0) {
            logger_allAlign.writeComma("0");
        } else {
            logger_allAlign.writeComma(trendValue);
        }
        logger_allAlign.writeComma("expect_rewards");
        logger_allAlign.writeComma(m);
        logger_allAlign.writeComma("risk");
        logger_allAlign.writeComma(risk);
        logger_allAlign.writeComma("find_gBest_round#");
        logger_allAlign.writeComma("1");
        logger_allAlign.writeComma("find_gBest_gen");
        logger_allAlign.writeComma(gen + 1);
        logger_allAlign.writeComma("find_gBest_times#");
        logger_allAlign.writeLine("1");
    }

//    if (HW == 1) {
//        cout << "initial_fund " << FUND << endl;
//        cout << "final_fund " << setprecision(20) << realFS[NUM_OF_DAY - 1] << endl;
//        cout << "real_rewards " << setprecision(20) << realFS[NUM_OF_DAY - 1] - FUND << endl;
//        cout << endl;
//        cout << "expect_rewards " << setprecision(20) << m << endl;
//        cout << "risk " << setprecision(20) << risk << endl;
//        cout << "Gbest " << setprecision(20) << trendValue << endl;
//        cout << "find_gBest_gen " << gen << endl;
//        cout << "find_gBest_round#  1" << endl;
//        cout << "find_gBest_times#  1" << endl;
//        cout << endl;
//
//        cout << "portfolio_stocks " << num << endl;
//        cout << "Stock# ";
//        for (int i = 0; i < NUM_OF_STOCK; i++) {
//            if (binarySolution[i] == 1) {
//                cout << stock[i].symbol << "(" << i << ") ";
//            }
//        }
//        cout << endl << "amount ";
//        for (int i = 0; i < NUM_OF_STOCK; i++) {
//            if (binarySolution[i] == 1) {
//                cout << amount[i] << " ";
//            }
//        }
//        cout << endl << "avg_fund ";
//
//        for (int i = 0; i < NUM_OF_STOCK; i++) {
//            if (binarySolution[i] == 1) {
//                cout << avgFund << " ";
//            }
//        }
//        cout << endl << "leftover_fund ";
//        for (int i = 0; i < NUM_OF_STOCK; i++) {
//            if (binarySolution[i] == 1) {
//                cout << balance[i] << " ";
//            }
//        }
//        cout << endl;
//        for (int i = 0; i < NUM_OF_DAY; i++) {
//            cout << "FS" << "(" << i + 1 << ") ";
//            for (int j = 0; j < NUM_OF_STOCK; j++) {
//                if (binarySolution[j] == 1) {
//                    cout << stock[j].fs[i] << " ";
//                }
//            }
//            cout << realFS[i] << endl;
//        }
//    }
    delete[] amount;
    delete[] balance;
    delete[] fee;
    delete[] realFS;
    delete[] Yi;
    return trendValue;
}
