#pragma once

#include <string>
#include <vector>

/** 
 * @brief Filesystem helpers. 
 * All given paths can be relative or absolute.
 */ 
namespace nada::fs {

    /// Reads a file with a given path and adds each line to a container via 'push_back'.
    void read_lines(const std::string& pfad, std::vector<std::string>& list, unsigned min_laenge = 2);

    // Writes a string to a specified file named.
    void write_lines(std::string pfad, std::string lines);
    
    /**
    * Returns all file paths (relative) from this executable's working directory (relative)
    * with a given file extension (case sensitive).
    *
    * @param folder Path to folder. Relative or absolute.
    * @param extension e.g. "png", "jpg", "dat", "json" etc. (without '.' before that). Case sensitive. Leave blank for all files.
    * @note File extension is Case-sensitive.
    * @note Path is given including `folder`. For example: `folder/file.extension`
    * @note '/' characters are used as path separators.
    * @note Only given folder is searched, not subfolders.
    */
    std::vector<std::string> all_files(const std::string& folder, std::string extension = "");

    /**
     * Same as `nada::fs::all_files`, but also searches subfolders and their subfolders of given folder.
     */
    std::vector<std::string> all_files_recursive(const std::string& folder, std::string extension = "");

    /// @brief Gives true, if file at given path exists and is readable.
    bool exists_file(const std::string& path);

}
