//
// Created by Irene Chen on 2020/2/4.
//

#ifndef GNQTS_SELECTSTOCK_PARTICLE_H
#define GNQTS_SELECTSTOCK_PARTICLE_H


class Particle {
public:
    int *binarySolution;
    double fitness;

    void setSize(int size) {
        this->binarySolution = new int[size];
    }

    ~Particle() {
        delete[] binarySolution;
    }

};

#endif //GNQTS_SELECTSTOCK_PARTICLE_H