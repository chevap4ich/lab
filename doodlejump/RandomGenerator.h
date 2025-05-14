#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <QRandomGenerator>

namespace Random {
    inline int intRand(int low, int high) {
        return QRandomGenerator::global()->bounded(low, high);
    }
    
    inline double doubleRand(double low, double high) {
        return QRandomGenerator::global()->generateDouble() * (high - low) + low;
    }
    
    inline bool chance(double probability) {
        return QRandomGenerator::global()->generateDouble() < probability;
    }
}

#endif //RANDOMGENERATOR_H