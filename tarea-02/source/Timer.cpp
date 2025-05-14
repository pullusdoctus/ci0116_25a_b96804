#include <Timer.hpp>

Timer::Timer() : isRunning(false) {}

void Timer::start() {
  startTime = std::chrono::high_resolution_clock::now();
  isRunning = true;
}

void Timer::stop() {
  if (isRunning) {
    endTime = std::chrono::high_resolution_clock::now();
    isRunning = false;
  }
}

void Timer::reportDuration() const {
  std::cout << "Duration: " << getDurationSeconds() <<
    " seconds\n" << std::endl;
}

double Timer::getDurationSeconds() const {
  if (isRunning) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(currentTime - startTime).count();
  } else {
    return std::chrono::duration<double>(endTime - startTime).count();
  }
}
