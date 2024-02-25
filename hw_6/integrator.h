#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "elma/elma.h"

using namespace elma;

class Integrator : public Process {
public:
    Integrator(std::string name) : Process(name), integral(0) {}

    void init() {}
    void start() {}
    void update();
    void stop() {}

    double value() const { return integral; }

private:
    double integral;
};

#endif
