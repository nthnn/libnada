#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#if __has_include(<execution>)
    /**
     * Sums Elements in `c` beginning with 0.
     * Automatically chooses single-threaded execution where `<execution>` is
     * unavailable.
     * @param c Range to sum. Could be std::vector for example.
     * @param f A binary function object as in `std::accumulate` or `std::reduce`.
     */
    #include <execution>
    #define NADA_SUM(c, f) std::reduce(std::execution::par, c.begin(), c.end(), 0, f);
#else
    /**
     * Sums Elements in `c` beginning with 0.
     * Automatically chooses single-threaded execution where `<execution>` is
     * unavailable.
     * @param c Range to sum. Could be std::vector for example.
     * @param f A binary function object as in `std::accumulate` or `std::reduce`.
     */
    #include <algorithm>
    #define NADA_SUM(c, f) std::accumulate(c.begin(), c.end(), 0, f);
#endif

/// Use this like: `if (static Do_Once _; _)` and the following code is only executed once or use the `NADA_DO_ONCE` macro.
struct Do_Once {
    explicit operator bool() { return std::exchange(b, false); }
    private: bool b = true;
};
/// Use this macro to do: `NADA_DO_ONCE { ... your code ... }` and your code is only executed once.
#define NADA_DO_ONCE if (static Do_Once once_var; once_var)

/// Helpers, that don't fit anywhere else.
namespace nada::misc {

    /**
     * Provides a color (rgb 32 bit) with a green tint at a positive ratio > 1, red tint at < 1.
     * 0 = maximum red; 1 = maximum green.
     * For example get_color_from_ratio(5, 5); gives maximum green (0x00FF00).
     * For example get_color_from_ratio(0, 5); gives maximum red   (0xFF0000).
     * For example get_color_from_ratio(2, 4); gives something roughly in the middle - 0x888800 or so.
     */
    uint32_t get_color_from_ratio(unsigned numerator, unsigned denominator);

    /** 
     * Compares via < the objects that are hidden behind their pointers.
     * For example:
     * std::vector<std::string*> v;
     * // ... fill v
     * std::sort(v.begin(), v.end(), nada::misc::ptr_compare); // sorts strings in v lexically
     */ 
    template <typename T>
    bool ptr_compare(const T* o1, const T* o2) { return *o1 < *o2; }

}
