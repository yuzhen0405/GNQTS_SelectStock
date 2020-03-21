//
// Created by Irene Chen on 2020/2/4.
//

#ifndef GNQTS_SELECTSTOCK_STOCK_H
#define GNQTS_SELECTSTOCK_STOCK_H

class Stock {
public:
    int symbol;
    double avg_fund;
    double *price;
    double *fs;

    void setSize(int size) {
        this->price = new double[size];
        this->fs = new double[size];
    }

    ~Stock(){
        delete[] price;
        delete[] fs;
    }
};

#endif //GNQTS_SELECTSTOCK_STOCK_H
