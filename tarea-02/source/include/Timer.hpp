#pragma once

#include <chrono>
#include <iostream>
#include <string>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
    bool isRunning;

public:
    Timer();
    void start();
    void stop();
    void reportDuration() const;
    double getDurationSeconds() const;
};
