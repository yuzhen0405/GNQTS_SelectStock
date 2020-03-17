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

    Model *model;

    for (int i = 0; i < 96; i++) {
//        double gbest=-DBL_MAX;
//        int count = 0;
//        for
//        {
        model = new Model(i);
        QTS qts(model);
        qts.run(i);

//        }
    }


    delete model;
    auto end = std::chrono::steady_clock::now();
    cout << endl;
    std::cout << "Time taken: " << std::chrono::duration<double>(end - start).count() << "s" << std::endl;
    return 0;
}
