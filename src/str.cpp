#include <nada/str.hpp>

std::vector<std::string> nada::str::tokenize(const std::string& text, const char token_sep) {
    std::vector<std::string> teile;
    teile.reserve(4);
    size_t anfang = 0, ende;
    while ((ende = text.find(token_sep, anfang)) != std::string::npos) {
        teile.push_back(text.substr(anfang, ende - anfang));
        anfang = ende;
        anfang++;
    }
    teile.push_back(text.substr(anfang));
    return teile;
}

void nada::str::replace(std::string& s, char alt, char neu) {
    if (s.size() < 1000000) std::replace(s.begin(), s.end(), alt, neu);
    else {
        const auto laenge = s.end() - s.begin();
        const auto it_mitte = s.begin() + laenge / 2;
        auto t1 = std::async(std::launch::async, [&]() { std::replace(s.begin(), it_mitte, alt, neu); } );
        auto t2 = std::async(std::launch::async, [&]() { std::replace(it_mitte,   s.end(), alt, neu); } );
        t1.get();
        t2.get();
    }
}

void nada::str::replace(std::string& s, const std::string& alt, const std::string& neu) {
    std::string buffer;
    if (neu.size() > alt.size()) buffer.reserve((size_t)(s.size() * 1.1 + 1));
    else buffer.reserve(s.size());
    size_t last = 0;
    for (size_t find = s.find(alt); find != std::string::npos; find = s.find(alt, last)) {
        buffer.append(s, last, find - last);
        buffer.append(neu);
        last = find + alt.size();
    }
    buffer.append(s.substr(last));
    s.swap(buffer);
}

[[gnu::hot]]
void nada::str::replace(std::string& s, const std::string& alt, const std::string& neu, int max) {
    if (max < 0 && alt.size() != neu.size()) { // optimierte Version nutzen (für ungleich große Ersetzungen)
        nada::str::replace(s, alt, neu); 
        return; 
    } 
    size_t it = 0;
    while (max && (it = s.find(alt, it)) != std::string::npos) {
        s.replace(it, alt.size(), neu);
        it += neu.size();
        if (max > 0) --max;
    }
}

void nada::str::to_lower(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower );
}

size_t nada::str::find(const std::string& s, const std::string& f, unsigned n, size_t start_pos) {
    for (unsigned i = 0; i < n + 1 && start_pos != std::string::npos; ++i) start_pos = s.find(f, start_pos + 1);
    return start_pos;
}

size_t nada::str::find_after(const std::string& s, const std::string& f, const std::string& a) {
        const size_t start_pos = s.find(a);
        if (start_pos != std::string::npos) return s.find(f, start_pos);
        return start_pos;
    }

void nada::str::remove(std::string& str, const char c) {
    str.erase(std::remove(std::begin(str), std::end(str), c), std::end(str));
}

void nada::str::remove_whitespace(std::string& s) {
    s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char c) { return std::isspace(c); }), s.end());
}

void nada::str::wrap(std::string& s, unsigned line_length) {
    auto search_pos = line_length;
    while (true) {
        const auto pos = s.find(' ', search_pos);
        if (pos == std::string::npos) return;
        s[pos] = '\n';
        search_pos = pos + line_length;
    }
}

bool nada::str::begins_with(const std::string& s, const std::string& beginning) {
    if (beginning.size() > s.size()) return false;
    return s.compare(0, beginning.size(), beginning) == 0;
}

bool nada::str::ends_with(const std::string& s, const std::string& ending) {
    if (ending.size() > s.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), s.rbegin());
}
