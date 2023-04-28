#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
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
     * Provides a color (RGBA 32 bit) with a green tint at a positive ratio > 1, red tint at < 1.
     * 0 = maximum red; 1 = maximum green.
     * @note This is currently not endian-portable.
     */
    uint32_t get_color_from_ratio(float ratio);

    /// @brief Sorts given list of pointers.
    template<typename T>
    void sort_ptrs(std::list<T*>& v) {
        v.sort([](const auto* lhs, const auto* rhs) { return *lhs < *rhs; }); 
    }

    /** 
     * Sorts given vector/deque/array... of pointers.
     * For example std::vector<int*> or std::deque<std::string*> and so on.
     * Does not support nullptrs.
     */ 
    template<typename T>
    void sort_ptrs(T& v) { 
        std::sort(v.begin(), v.end(), [](const auto* lhs, const auto* rhs) { return *lhs < *rhs; }); 
    }

}
