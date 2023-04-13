#pragma once

#include <cstdint>

namespace nada::time {

    /** 
     * Gives you the amount of milliseconds from a fixed point in time. 
     * Does roughly the same as you'd expect from Java's `System.currentTimeMillis()`.
     */
    uint64_t millis();

    /** 
     * Let the executing thread sleep for `millis` milliseconds.
     * @param millis Milliseconds to sleep.
     */ 
    void sleep(unsigned millis);

    /**
     * Use this in your rendering loop to keep fps @ 'target_fps'.
     * Example:
     *      while (true) {
     *          // check events
     *          // do rendering
     *          // other things
     *          nada::time::fps(60); // keeps this loop at 60 fps
     *      }
     * @note target_fps must be > 0.
     */
    void fps(unsigned target_fps);

    /**
     * @brief For timing stuff.
     * Example:
     *     nada::time::Clock c;
     *     // do stuff
     *     c.ms(); // tells you how long *stuff* took in milliseconds.
     */
    class Clock {

        public:

            /// Ctor. Also resets clock to 'now'.
            Clock();

            /// @brief Restarts this clock.
            void reset();

            /// @brief Time in milliseconds from construction (or last reset() call).
            uint64_t ms() const;

            /// @brief Time in seconds from construction (or last reset() call).
            float s() const;

        private:

            uint64_t time_start;

    };

}
