#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch {
public:
    Stopwatch();              // Constructor initializes the stopwatch
    void start();             // Starts the timer
    void stop();              // Stops the timer
    void reset();             // Resets the timer to zero
    double get_minutes();     // Returns the counted minutes as a double
    double get_seconds();     // Returns the counted seconds as a double
    double get_milliseconds();// Returns the counted milliseconds as a double
    double get_nanoseconds(); // Returns the counted nanoseconds as a double

private:
    std::chrono::high_resolution_clock::time_point _start;
    std::chrono::high_resolution_clock::time_point _end;
    bool _running;
    std::chrono::duration<double, std::nano> _elapsed;
};

#endif // STOPWATCH_H
