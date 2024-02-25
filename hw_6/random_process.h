#ifndef RANDOMPROCESS_H
#define RANDOMPROCESS_H

#include "elma/elma.h"

class RandomProcess : public elma::Process {
public:
    RandomProcess(std::string name);

    void init();
    void start();
    void update();
    void stop();
};

#endif
