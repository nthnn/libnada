#include <vector>
#include <string>
#include <algorithm>
#include <future>

namespace nada::str {

    /**
     * @brief Splits a string 'text' into parts. Chopping is done where 'char token_sep' occurs.
     *
     * @param text Text to split.
     * @param token_sep If this `char` occurs, a new token is started at this point.
     * @return std::vector<std::string> The splitting parts.
     * @note After splitting, none of the parts contains the `char token_sep` anymore.
     */
    std::vector<std::string> tokenize(const std::string& text, char token_sep);

    /**
     * @brief A simple 'replace_all' method to replace 'char'.
     * Replaces all occurrences of `old` in a string `s` with `new'.
     * @param s The string to manipulate.
     * @param old `char` to replace.
     * @param new `char` to replace with.
     * @note Uses 2 threads for strings larger than 1 million chars.
     */
    void replace(std::string& s, char c_old, char c_new);

    /**
     * @brief A `replace_all` method optimized for large strings.
     * Replaces all occurrences of `old` in a string `s` with `new'.
     * For large strings, and replace with 'alt.size() != new.size()` faster than
     * the regular replace method: @see replace.
     * @param s The string to manipulate.
     * @param old `char` to replace.
     * @param new `char` to replace with.
     */
    void replace(std::string& s, const std::string& s_old, const std::string& s_new);

    /**
     * @brief A 'replace_all' method with a "cancel" function.
     * Replaces all occurrences of `old` in a string `s` with `new' until it has been replaced `max` times.
     * @param s The string to manipulate.
     * @param old `char` to replace.
     * @param new `char` to replace with.
     * @param max Maximum number of times to replace (-1 means no limit).
     */
    void replace(std::string& s, const std::string& s_old, const std::string& s_new, int max);

    /**
     * @brief Returns the text between two tokens.
     *
     * @param text Text to search.
     * @param l_sep 'l_set' Left separator of the text snippet to be extracted. Can be `char` or `std::string`.
     * @param r_sep 'r_set' Right separator of the text snippet to be extracted. Can be `char` or `std::string`.
     * @return std::string The extracted text snippet. Empty if the separators are not found.
     * @note The text snippet is rendered without `l_sep` and `r_sep`.
     */
    template <typename T, typename U>
    static std::string get_between(std::string text, const T& l_sep, const U& r_sep) {
        auto links = text.find(l_sep);
        if (links != std::string::npos) {
            ++links;
            const auto rechts = text.find(r_sep, links);
            if (rechts != std::string::npos && links < rechts) return {text.begin() + links, text.begin() + rechts};
            else                                               return {text.begin() + links, text.end()};
        }
        return {};
    }

    /**
     * @brief Converts an ANSI string to lowercase only.
     * @params The string to manipulate.
     * @note umlauts and special characters could cause problems. (Only ANSI/ASCII is converted correctly.)
     */
    void to_lower(std::string& s);

    /**
     * Finds index of the nth occurence of `f` in `s` (indexing starts with 0). 
     * Returns `std::string::npos` if not found.
     * @see `test_string.hpp` for examples.
     * 
     * @param s String to search.
     * @param f Token to find.
     * @param n Return the index of nth Token.
     * @param start_pos Position to start the search, 0 by default.
     * @return size_t 0-indexed position of s. Same as `std::string::find` does.
     */
    size_t find(const std::string& s, const std::string& f, unsigned n, size_t start_pos = 0);

    /**
     * @brief Finds the position of String f in String s, but only after the occurrence of String a (in s of course).
     * For example, the parameters ("hello world and hello computer", "hello", "and") are passed,
     * the position of the second "hello", which occurs after the "and", is returned.
     * Position indices returned work the same as `std::string::find`.
     * 
     * @param s String to search.
     * @param f Token to find (after first occurence of a).
     * @param a Searches s only after finding this `a`.
     * @return size_t Position of f in s after a. `std::string::npos` if not found.
     */
    size_t find_after(const std::string& s, const std::string& f, const std::string& a);

    /**
     * @brief Check if a string starts with a given string.
     * @param s String to check.
     * @param beginning Check if `s` begins with this.
     * @return Does `s` begin with `beginning`?
     */
    bool begins_with(const std::string& s, const std::string& beginning);

    /**
     * @brief Check if a string ends with a given string.
     * @param s String to check.
     * @param ending Check if `s` ends with this.
     * @return Does `s` end with `ending`?
     */
    bool ends_with(const std::string& s, const std::string& ending);

    /**
     * @brief Removes all characters `c` from str.
     * @param str String to manipulate.
     * @param c Charater to remove.
     */
    void remove(std::string& str, char c);

    /// Removes all whitespace from `s`.
    void remove_whitespace(std::string& s);

    /**
     * Wraps given string at the next whitespace after
     * given `line_length` has been reached.
     */
    void wrap(std::string& s, unsigned line_length);

}
