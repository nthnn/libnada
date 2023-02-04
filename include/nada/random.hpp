#pragma once

#include "log.hpp"

#include <random>
#include <chrono>
#include <unordered_map>

/// Methods for supplying random numbers.
namespace nada::random {

    /// Returns a random number (integer) in the range a <= N <= b (template version).
    template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
    T get(T a, T b);

    /// Returns a random number (float) in the range a <= N <= b (template version).
    template<typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
    T get(T a, T b);

    /// Returns a random number in the range a <= N <= b (unsigned int).
    int i(int a, int b);

    /// Returns a random number in the range a <= N <= b (long long int).
    long long ll(long long a, long long b);

    /// Returns a random number in the range a <= N <= b (unsigned int).
    unsigned int ui(unsigned int a, unsigned int b);

    /// Returns a random number in the range a <= N <= b (unsigned long).
    unsigned long ul(unsigned long a, unsigned long b);

    /// Returns a random number in the range a <= N <= b (float).
    float f(float a, float b);

    /// Returns a random number in the range a <= N <= b (double).
    double d(double a, double b);

    /// Returns `true` with a probability of `chance`%. 0 returns always `false`; 100 or more returns always `true`.
    bool b(unsigned int chance);

    /**
    * Returns a random number in the largest possible number range. For example, for random hashing.
    * @tparam T Data type of the random hash, e.g. uint_32t.
     */
    template<typename T>
    T random_hash() {
        thread_local std::random_device rd;
        thread_local std::mt19937 mt(rd());
        std::uniform_int_distribution<T> uid(0);
        return uid(mt);
    }

    /**
     * @brief Returns a random element of a given list. Const version.
     * @tparam T data type of the items in the list.
     * @param list Non-empty list of items to randomly select one from.
     * @warning list must not be empty!
     */
    template<typename T>
    const typename T::value_type& choice(const T& list) {
        std::size_t n = nada::random::get<std::size_t>(0, list.size() - 1);
        auto iter = std::cbegin(list);
        std::advance(iter, n);
        return *iter;
    }

    /**
     * @brief Returns a random element of a given list. Non-const version.
     * @tparam T data type of the items in the list.
     * @param list Non-empty list of items to randomly select one from.
     * @warning list must not be empty!
     */
    template<typename T>
    typename T::value_type& choice(T& list) {
        std::size_t n = nada::random::get<std::size_t>(0, list.size() - 1);
        auto iter = std::begin(list);
        std::advance(iter, n);
        return *iter;
    }

    /**
     * @brief Returns a random element of a given list and removes it.
     * @note list must not be empty.
     * @note object is copied and returned via assignment.
     */
    template<typename T>
    typename T::value_type choice_erase(T& list) {
        std::size_t n = nada::random::get<std::size_t>(0, list.size() - 1);
        auto iter = std::begin(list);
        std::advance(iter, n);
        typename T::value_type objekt{std::move(*iter)}; // Kopie
        list.erase(iter);
        return objekt;
    }

    /**
     * Returns a vector of objects.
     * Each object appears `pair<A,B>.second` times.
     * This is used for example to create lot lists.
     * @tparam A key_type of the map and at the same time value_type of the returned vector.
     * @tparam B Integer data type that determines the number of objects B that will be written to the return vector.
     * @param weights A map of weights to be processed.
     * @return Generated list of A.
     */
    template<typename A, typename B>
    constexpr std::vector<A> get_weights(const std::unordered_map<A, B>& gewichtungen) {
        std::vector<A> v;
        v.reserve(gewichtungen.size() * 2);
        for (const auto& paar: gewichtungen) for (unsigned int i = 0; i < paar.second; ++i) v.push_back(paar.first);
        return v;
    }

}
