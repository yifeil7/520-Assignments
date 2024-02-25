#include "integrator.h"

void Integrator::update() {
    if (channel("link").nonempty()) {
        double value = channel("link").latest().get<double>();
        integral += delta() * value;
    }
}
