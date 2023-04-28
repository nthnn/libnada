# nadalib

[![Build and Test](https://github.com/chris-nada/libnada/actions/workflows/build-and-test.yml/badge.svg)](https://github.com/chris-nada/libnada/actions/workflows/build-and-test.yml)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

## User friendly C++ library for everyday basic needs
+ **C++17 or later required**
+ **no external dependencies**
+ string manipulation
+ random number generation
+ ini (config) file reading/writing
+ easy logging
+ file system helpers
+ basic benchmarking function calls
+ timing / constant FPS

**Documented**
+ Usage examples see below
+ All functions are documented in their headers

**Unit Tested**
+ in `./test/` using the awesome [doctest header-only library](https://github.com/doctest/doctest/)
+ tests also provide more usage examples

## How to include in your project
1. Git clone or copy folder `libnada` to the same directory your `CMakeLists.txt` is in.
2. Add these 3 lines to your `CMakeLists.txt`
```cmake
    ...
    add_subdirectory(libnada)
    ...
    include_directories(libnada/include)
    ...
    target_link_libraries(PROJECT_NAME PRIVATE nada)
    ...
```
## Usage examples

Given examples below could of course be shortened by `using namespace nada;`

### For generating randomness
### `#include <nada/random.hpp>`
```cpp
bool b1 = nada::random::b(100); // always true
bool b2 = nada::random::b(50); // is true 50% of the time
bool b3 = nada::random::b(25); // is true 25% of the time
bool b4 = nada::random::b(0); // always false

int i1 = nada::random::i(1,6); // like a dice: gives 1, 2, 3, 4, 5 or 6

float f1 = nada::random::f(0,1); // gives a random float between 0 and 1, 
                                 // i.e. 0.6621, 0.1551 or 0.99101 or something

double d1 = nada::random::d(1, 1000); // gives a random double between 1 and 1000
                                      // i.e. 551.07, 1.1987 or 851.29 or so

// random picker
std::vector<std::string> v = {"first", "second", "third", "forth", "..."};
std::string s = nada::random::choice(v); // s == "second" for example
```


### For String manipulation
### `#include <nada/str.hpp>`
```cpp
std::string s = "hello world";
// Remove whitespace
nada::str::remove_whitespace(s); // "helloworld"

// Trim left
std::string s = "\t    space. the final frontier.\t    ";
nada::str::trim_left(s); // "space. the final frontier.\t    ";

// Trim right
std::string s = "\t    space. the final frontier.\t    ";
nada::str::trim_right(s); // "\t    space. the final frontier.";

// Trim (left + right)
std::string s = "\t    space. the final frontier.\t    ";
nada::str::trim(s); // "space. the final frontier.";

// Remove all chars 'o'
nada::str::remove(s1, 'o'); // "hellwrld"

// Get text between tags or other delimiters
std::string tagged1 = "oh that is so <tacky> isn't it?";
std::string tag1 = nada::str::get_between(tagged1, '<', '>'); // "tacky"

std::string tagged2 = "oh that is so 'tacky' isn't it?";
std::string tag2 = nada::str::get_between(tagged2, '\'', '\''); // "tacky"

// Tokenize Strings
std::string s = "hello world, how are you?";
std::vector<std::string> v = nada::str::tokenize(s, ' '); // ["hello", "world,", "how", "are", "you?"]

std::string s = "0.1,0.2,0.3,0.4";
std::vector<std::string> v = nada::str::tokenize(s, ','); // ["0.1", "0.2", "0.3", "0.4"]

// Wrapping single line strings
std::string s1("Lorem ipsum dolor sit amet, consectetur adipiscing"
    " elit, sed do eiusmod tempor incididunt ut labore et dolore magna"
    " aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco"
    " laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure"
    " dolor in reprehenderit in voluptate velit esse cillum dolore eu"
    " fugiat nulla pariatur. Excepteur sint occaecat cupidatat non"
    " proident, sunt in culpa qui officia deserunt mollit anim id est"
    " laborum."); // single line text
nada::str::wrap(s1, 42); // breaks line next whitespace after 42 chars 
// s1 ==
    "Lorem ipsum dolor sit amet, consectetur adipiscing\n"
    "elit, sed do eiusmod tempor incididunt ut\n"
    "labore et dolore magna aliqua. Ut enim ad\n"
    "minim veniam, quis nostrud exercitation ullamco\n"
    "laboris nisi ut aliquip ex ea commodo consequat.\n"
    "Duis aute irure dolor in reprehenderit in\n"
    "voluptate velit esse cillum dolore eu fugiat\n"
    "nulla pariatur. Excepteur sint occaecat cupidatat\n"
    "non proident, sunt in culpa qui officia deserunt\n"
    "mollit anim id est laborum." // note: \n have been inserted

// Testing string for intness or floatness
std::string an_int = "42";
std::string a_float = "42.0";
nada::str::is_integer(an_int); // true
nada::str::is_integer(a_float); // false
nada::str::is_float(a_float); // true
nada::str::is_float(an_int); // true
```

### For Reading and Writing INI 
### `#include <nada/ini.hpp>`

Given `subfolder/some_ini_file.ini`
```ini
# contents of example ini file
first=1
second=2.5
third=4
fourth=some value
fifth=ich,bin,many,values
sixth=True
```
```cpp
// Path to your ini
nada::Ini ini("subfolder/some_ini_file.ini");
if (ini.good()) {
    // Read different types like this

    int i = ini.get_int<int>("first"); // 1 <- use this for int, long, short and so on
    
    double d = ini.get_float<double>("second"); // 2.5 <- use this for float and double
    
    std::string s = ini.get("fourth"); // "some value"
    
    std::vector<std::string> = ini.get_vector("fifth"); // "ich", "bin", "many", "values"
    
    bool b = ini.get_bool("sixth"); // true (accepts "1", "True" and "true" as true)
}

// Or: static methods for simple access
std::string s = nada::Ini::get_value_from_file("subfolder/some_ini_file.ini", "fourth"); // "some value"
std::vector<std::string> = nada::Ini::get_vector_from_file("subfolder/some_ini_file.ini", "fifth"); // "ich", "bin", "many", "values"
```

### For timing stuff 
### `#include <nada/time.hpp>`
```cpp
// sleep + a simple millis() clock
unsigned long long m1 = nada::time::millis(); // 1669025747307
nada::time::sleep(100); // sleeps 100 ms
unsigned long long m1 = nada::time::millis(); // 1669025747407

/// Timing stuff
nada::time::Clock c;
// do stuff
c.ms(); // tells you how long *stuff* took in milliseconds (uint).
c.s(); // tells you how long *stuff* took in seconds (float).
c.reset(); // restarts c

/// constant FPS
while (true) { // your rendering loop
    // check events,,,
    // do rendering,,,
    // other things,,,
    nada::time::fps(60); // keeps this loop @ 60 fps
}
```

### For miscellaneous things 
### `#include <nada/misc.hpp>`

```cpp
// Sum elements using multi-threading if available*
// *might need linking with 'pthread' and possibly 'tbb'
std::vector<unsigned> v = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
unsigned sum = NADA_SUM(v, std::plus()); // sum == 10

// Comparator for objects behind raw pointers or smart-pointers:
std::vector<std::string*> v; // note: std::string* not regular std::string
//or: std::vector<int*> v
//or: std::vector<std::shared_ptr<std::string>> v;
//or: std::vector<std::unique_ptr<std::string>> v;
//or: std::list, std::array, std::deque... also supported
// ... fill v
nada::misc::sort_ptrs(v); // sorts ints in v or strings in v lexically
```


### For filesystem stuff
### `#include <nada/fs.hpp>`

```cpp
// if you got a folder structure like this for example
// .
// └── subfolder
//     ├── file1.xml
//     ├── file2.jpg
//     ├── file3.png
//     ├── file4.jpg
//     └── subsubfolder
//         ├── file5.txt
//         └── file6.xml

std::vector<std::string> files = nada::fs::all_files("subfolder"); 
// => subfolder/file1.xml, subfolder/file2.jpg, subfolder/file3.png subfolder/file4.jpg

std::vector<std::string> files = nada::fs::all_files("subfolder", "jpg"); 
// => subfolder/file2.jpg, subfolder/file4.jpg

std::vector<std::string> files = nada::fs::all_files_recursive("subfolder", "xml"); 
// => subfolder/file1.xml, subfolder/subsubfolder/file6.xml

bool file_exists = nada::fs::exists_file("subfolder/file1.xml"); // true
```

### For logging stuff
### `#include <nada/log.hpp>`
```cpp
nada::Log::out() << "Hello world!" << nada::Log::endl; // prints "Hello world!" to std::cout

std::ostringstream oss;
nada::Log::set_output(&oss);
nada::Log::out() << "Hello world!" << nada::Log::endl; // writes "Hello world!" to stringstream 'oss'

std::ofstream out("log.txt");
nada::Log::set_output(&out);
nada::Log::out() << "Hello world!" << nada::Log::endl; // writes "Hello world!" to file "log.txt"

nada::Log::to_cout();
nada::Log::out() << "Hello world!" << nada::Log::endl; // prints "Hello world!" to std::cout again

nada::Log::out() << nada::Log::endl; // newline + flush

nada::Log::out() << nada::Log::flush; // flush 

nada::Log::debug() << "Hello world!"; // prints "Hello world!" only if building in debug mode; does nothing in release build
```

### Benchmarking function calls
### `#include <nada/log.hpp>`
```cpp
auto function_to_benchmark = []() {
    // do
    // expensive
    // calculation
};

nada::Log::benchmark(function_to_benchmark, "Expensive calculation");
// prints something like:
// "Expensive calculation Duration: 0.41s"
```

