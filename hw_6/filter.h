#ifndef FILTER_H
#define FILTER_H

#include "elma/elma.h"
#include <vector>

class Filter : public elma::Process {
public:
    Filter(std::string name);

    void init();
    void start();
    void update();
    void stop();
    double value() const;

private:
    double _sum;
    int _count;
    std::vector<double> _values;
};

#endif
