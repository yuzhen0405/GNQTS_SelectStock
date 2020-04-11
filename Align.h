//
// Created by Irene Chen on 2020/3/18.
//

#ifndef GNQTS_SELECTSTOCK_ALIGN_H
#define GNQTS_SELECTSTOCK_ALIGN_H

#include "Stock.h"
#include "Logger.h"
#include "Period.h"

class Align {
public:
    string ROUND = "50";
    string GENERATION = "10000";
    string PARTICLE = "10";
    int *binarySolution;
    double theta_upper;
    double theta_lower;
    double theta;
    int round;

    double initial_fund;
    double final_fund;
    double expect_return;
    double risk;
    double gBest;
    int find_gBest_gen;
    int find_gBest_round;
    int find_gBest_time;

    int num;
    Stock *stock;
    int *amount;
    double *balance;
    double *FS; //funds standardization
    double fitness;
    int num_of_stock;
    int num_of_day;

    void setStock(int numOfStock, int numOfDay) {
        this->binarySolution = new int[numOfStock];
        this->amount = new int[numOfStock];
        this->balance = new double[numOfStock];
        this->FS = new double[numOfDay];
        this->num_of_stock = numOfStock;
        this->num_of_day = numOfDay;
        this->stock = new Stock[numOfStock];
        for (int i = 0; i < numOfStock; i++) {
            this->stock[i].setSize(numOfDay);
        }
    }

    ~Align() {
        delete[] this->binarySolution;
        delete[] this->amount;
        delete[] this->balance;
        delete[] this->FS;
        delete[] this->stock;
    };

    void align(int period) const {
        Logger logger("../log/" + tag + "/Irene_result_" + trainPeriod[period], 20);

        logger.writeComma("Period");
        logger.writeLine(period + 1);
        logger.writeComma("Stock#");
        for (int i = 0; i < this->num_of_stock; i++) {
            if (this->binarySolution[i] == 1) {
                logger.write(this->stock[i].symbol);
                logger.write("(");
                logger.write(i);
                logger.writeComma(")");
            }
        }
        logger.writeLine("");
        logger.writeComma("Allocated fund");
        for (int i = 0; i < this->num_of_stock; i++) {
            if (binarySolution[i] == 1) {
                logger.write(this->stock[i].avg_fund);
                logger.write("(");
                logger.write(this->amount[i]);
                logger.write(")");
                logger.writeComma("");
            }
        }
        logger.writeLine("");
        logger.writeComma("Balance");
        for (int i = 0; i < this->num_of_stock; i++) {
            if (binarySolution[i] == 1)
                logger.writeComma(this->balance[i]);
        }

        logger.writeLine("");

        logger.writeComma("Expected return");
        logger.writeLine(this->expect_return);
        logger.writeComma("Risk");
        logger.writeLine(this->risk);
        logger.writeComma("gBest");
        logger.writeLine(this->gBest);


        for (int i = 0; i < this->num_of_day; i++) {
            logger.write("FS(");
            logger.write(i + 1);
            logger.writeComma(")");
            for (int j = 0; j < num_of_stock; j++) {
                if (this->binarySolution[j] == 1) {
                    logger.writeComma(this->stock[j].fs[i]);
                }
            }
            logger.writeComma(this->FS[i]);
            logger.writeLine("");
        }
        logger.writeLine("");
    };

    void allAlign(int period) const {
        Logger logger(
                "../log/" + tag + "/" + "(srand114)" + ROUND + "round_" + GENERATION + "gen_" + tag + "_train.csv", 20);
        if (period == 0) {
            logger.writeComma(tag);
            logger.writeComma("Number of chosen");
            logger.writeLine("Portfolio");
        }
        logger.writeComma(period + 1);
        logger.writeComma(this->num);
        for (int i = 0; i < this->num_of_stock; i++) {
            if (this->binarySolution[i] == 1) {
                logger.write(this->stock[i].symbol);
                logger.write("(");
                logger.write(i);
                logger.writeSpace(")");
            }
        }
        logger.writeComma("");
        logger.writeComma("gBest");
        logger.writeComma(this->gBest);
        logger.writeComma("Expect reward");
        logger.writeComma(this->expect_return);
        logger.writeComma("Risk");
        logger.writeComma(this->risk);
        logger.writeComma("Find gBest round");
        logger.writeComma(this->find_gBest_round + 1);
        logger.writeComma("Find gBest gen");
        logger.writeComma(find_gBest_gen + 1);
        logger.writeComma("Found gBest time");
        logger.writeLine(this->find_gBest_time);
    }
};

#endif //GNQTS_SELECTSTOCK_ALIGN_H
