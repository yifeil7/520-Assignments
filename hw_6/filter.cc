#include "filter.h"

Filter::Filter(std::string name) : Process(name), _sum(0), _count(0), _values(10, 0) {}

void Filter::init() {}

void Filter::start() {}

void Filter::update() {
    if (channel("link").nonempty()) {
        double value = channel("link").latest();
        if (_count < 10) {
            _sum += value;
            _count++;
        } else {
            _sum += value - _values[_count % 10];
        }
        _values[_count % 10] = value;
    }
}

void Filter::stop() {}

double Filter::value() const {
    if (_count == 0) {
        return 0; // Return 0 if no values have been received yet
    } else {
        return _sum / std::min(_count, 10);
    }
}
