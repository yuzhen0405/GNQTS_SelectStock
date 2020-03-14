#include "QTS.h"
#include <chrono>

int main() {
    remove("../log/align.csv");
    remove("../log/buy.csv");
    remove("../log/choose.csv");
    remove("../log/expectFS.csv");
    remove("../log/measure.csv");
    remove("../log/realFS.csv");
    remove("../log/update.csv");

    auto start = std::chrono::steady_clock::now();

    srand(114);

//    double random;
//    for (int i = 0; i < 100; i++) {
//        for (int j = 0; j < 49; j++) {
//            random = (double) rand() / RAND_MAX;
//        }
//    }

    Model *model;
    model = new Model();

//    model->readfile(i);
    QTS qts(model);
    qts.run();

    delete model;
    auto end = std::chrono::steady_clock::now();
    cout << endl;
    std::cout << "Time taken: " << std::chrono::duration<double>(end - start).count() << "s" << std::endl;
    return 0;
}
