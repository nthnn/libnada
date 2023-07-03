#include <nada/fs.hpp>
#include <nada/str.hpp>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <cstdio>
#include <fstream>
#include <filesystem>

void nada::fs::read_lines(const std::string& pfad, std::vector<std::string>& liste, unsigned min_laenge) {
    std::ifstream in(pfad, std::ios::binary);
    if (in.good()) {
        for (std::string zeile; std::getline(in, zeile);) {
            if (zeile.size() >= min_laenge) {
                nada::str::remove(zeile, '\r'); // Windows workaround
                liste.push_back(zeile);
            }
        }

    //if (liste.empty()) nada::Log::err() << "Keine Elemente in " << pfad << '\n'; //TODO
    }
    //else nada::Log::err() << pfad << " konnte nicht gelesen werden.\n"; //TODO
}

bool nada::fs::write_lines(std::string pfad, std::string lines) {
    try {
        std::ofstream file(pfad);

        if (file.is_open()) {
            file << lines;
            file.close();
        }
    } catch(const std::exception& e) {
        return false;
    }

    return true;
}

std::vector<std::string> nada::fs::all_files(const std::string& ordner, std::string endung) {
    std::vector<std::string> dateien;
    endung = "." + endung;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(ordner)) {
            if (entry.is_regular_file()) {
                const auto& dateiname = entry.path().generic_string();
                if (endung == "." || nada::str::ends_with(dateiname, endung)) dateien.push_back(dateiname);
            }
        }
    } catch(const std::exception& e) {}
    return dateien;
}

std::vector<std::string> nada::fs::all_files_recursive(const std::string& folder, std::string extension) {
    std::vector<std::string> dateien;
    extension = "." + extension;
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(folder)) {
            if (entry.is_regular_file()) {
                const auto& dateiname = entry.path().generic_string();
                if (extension == "." || nada::str::ends_with(dateiname, extension)) dateien.push_back(dateiname);
            }
        }
    } catch(const std::exception& e) {}
    return dateien;
}

bool nada::fs::exists_file(const std::string& path) {
    try { 
        std::ifstream in(path);
        return in.good() && std::filesystem::is_regular_file(path);
    } catch (const std::exception& e) { return false; }
}

bool nada::fs::delete_file(std::string filename) {
    return std::remove(filename.c_str()) == 0;
}

bool nada::fs::delete_folder(std::string path) {
    try {
        #ifdef _WIN32
            return (RemoveDirectory(path.c_str()) != 0);
        #else
            return (rmdir(path.c_str()) == 0);
        #endif
    } catch(const std::exception& error) {
        return false;
    }

    return true;
}
