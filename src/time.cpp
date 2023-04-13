#include <nada/time.hpp>

#include <thread>
#include <chrono>

uint64_t nada::time::millis() {
    const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    return millis.count();
}

void nada::time::sleep(unsigned millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void nada::time::fps(unsigned target_fps) {
    thread_local nada::time::Clock c;
    const int wait_time = (1000 / (int)target_fps) - c.ms();
    if (wait_time > 0) nada::time::sleep(wait_time);
    c.reset();
}

nada::time::Clock::Clock() : time_start(nada::time::millis()) {
    //
}

void nada::time::Clock::reset() {
    time_start = nada::time::millis();
}

uint64_t nada::time::Clock::ms() const {
    return nada::time::millis() - time_start;
}

float nada::time::Clock::s() const {
    return static_cast<float>(ms()) * 0.001f;
}
