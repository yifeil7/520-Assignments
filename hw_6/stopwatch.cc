#include "stopwatch.h"

// Constructor
Stopwatch::Stopwatch() : _running(false), _elapsed(0) {}

void Stopwatch::start() {
    if (!_running) {
        _start = std::chrono::high_resolution_clock::now();
        _running = true;
    }
}

void Stopwatch::stop() {
    if (_running) {
        _end = std::chrono::high_resolution_clock::now();
        _elapsed += _end - _start;
        _running = false;
    }
}

void Stopwatch::reset() {
    _running = false;
    _elapsed = std::chrono::duration<double, std::nano>::zero();
}

double Stopwatch::get_minutes() {
    return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<60>>>(_elapsed).count();
}

double Stopwatch::get_seconds() {
    return std::chrono::duration_cast<std::chrono::seconds>(_elapsed).count();
}

double Stopwatch::get_milliseconds() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(_elapsed).count();
}

double Stopwatch::get_nanoseconds() {
    return _elapsed.count();
}
