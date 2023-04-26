#pragma once

#include "misc.hpp"

namespace nada {
/**
 * @brief Class to handle reading values from ini-Files.
 * @note Namespaces inside the ini like this: `[namespace]` are simply ignored.
 * 
 * An ini-file looks like this:
 * ```
 * [data]
 * os=Linux
 * key=value
 * some_number=1.0
 * some_url=http://www.example.com
 * ```
 */
class Ini final {

public:

    /**
     * Start from this constructor by giving it a relative or absolute path to your ini-file.
     * @note Throws no exceptions. Check `Ini::good()` to see, if the file was found and if it's readable.
     * @param ini_path For example relative like this `"subfolder/ini_file.ini"` or absolute like `"/home/user/file.ini"`.
     */
    explicit Ini(const std::string& ini_path) : ini_file(ini_path) {}

    /**
     * Is the file readable?
     */
    bool good() const;

    /**
     * Gives you the raw value that's written in the ini behind given `key`.
     * @param fallback If `key` wasn't found, this is returned.
     */
    std::string get(const std::string& key, const std::string& fallback = "") {
        const std::string val = get_value_from_file(ini_file, key);
        if (val.empty()) return fallback;
        return val;
    }

    /**
     * Gives you a bool behind given key.
     * Bools may be presented as `0` or `1`, `false` or `true`, `False` or `True` and `FALSE` or `TRUE`.
     * @param key The key in the INI from which the values are read.
     * @param fallback If `key` wasn't found, this value is returned. `false` by default.
     */
    bool get_bool(const std::string& key, bool fallback = false);

    /**
     * Use this to retrieve integers, longs, long longs or anything unsigned.
     * @example `long value = ini.get_int<long>("key", 42);`
     * @param fallback If `key` wasn't found, this is returned.
     */
    template<typename T>
    T get_int(const std::string& key, T fallback = T{}) {
        const std::string val = get_value_from_file(ini_file, key);
        if (val.empty()) return fallback;
        return std::atoll(val.c_str());
    }

    /**
     * Use this to retrieve floats.
     * @example `float value = ini.get_float<float>("key", 42.f);`
     * @param fallback If `key` wasn't found, this is returned.
     */
    template<typename T>
    T get_float(const std::string& key, T fallback = T{}) {
        const std::string val = get_value_from_file(ini_file, key);
        if (val.empty()) return fallback;
        return std::atof(val.c_str());
    }

    /**
     * Returns the values separated by `token` from an INI file (with = as separator)
     * for a given key as 'std::vector<std::string>`.
     *
     * @param key The key in the INI from which the values are read.
     * @param token delimiter of the value list.
     * @param append If `append` is given, this value is appended to all strings.
     * @return List of the read values as a string.
     */
    std::vector<std::string> get_vector(const std::string& key, char token = ',', const std::string& append = "");

    /**
    * Returns the value of the given key from an INI file (with = as separator).
    * @note Returns an empty string in case of read errors and non-existent keys.
    * @note Returns the value of the last key for keys that occur multiple times.
    * @note Uses a thread-safe cache.
    * @param file path to the INI file.
    * @param key Readout key.
    * @return value of the key.
    */
    static std::string get_value_from_file(const std::string& datei, const std::string& key);

    /**
    * Returns the values separated by `token` from an INI file (with = as separator)
    * for a given key as 'std::vector<std::string>`.
    *
    * @param file path to the INI file.
    * @param key The key in the INI from which the values are read.
    * @param token delimiter of the value list.
    * @param append If `append` is given, this value is appended to all strings.
    * @return List of the read values as a string.
    */
    static std::vector<std::string> get_vector_from_file(const std::string& datei, const std::string& key, const char token =',', const std::string& append = "");

private:

    /// @brief Path to ini file.
    std::string ini_file;

};}
