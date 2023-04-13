# nadalib

## User friendly C++ library for everyday basic needs
+ **C++17 or later required**
+ **no external dependencies**
+ string manipulation
+ random number generation
+ ini (config) file reading/writing
+ simplistic logging
+ file system

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

### For generating random numbers 
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
                                      // i.e. 551.07, 0.1987 or 851.29 or so
```


### For String manipulation
### `#include <nada/str.hpp>`
```cpp
std::string s1 = "hello world";
// Remove whitespace
nada::str::remove_whitespace(s1); // "helloworld"

// Remove all chars
nada::str::remove(s1, 'o'); // "hellwrld"

// Get text between tags or other delimiters
std::string tagged1 = "oh that is so <tacky> isn't it?";
std::string tag1 = nada::str::get_between(tagged1, '<', '>'); // "tacky"

std::string tagged2 = "oh that is so 'tacky' isn't it?";
std::string tag2 = nada::str::get_between(tagged2, '\'', '\''); // "tacky"

// Tokenize Strings
std::string s2 = "hello world, how are you?";
std::vector<std::string> v2 = nada::str::tokenize(s2, ' '); // ["hello", "world,", "how", "are", "you?"]

std::string s3 = "0.1,0.2,0.3,0.4";
std::vector<std::string> v3 = nada::str::tokenize(s3, ','); // ["0.1", "0.2", "0.3", "0.4"]

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
    "mollit anim id est laborum."); // note: \n have been inserted
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
```
```cpp
// Read values like this
nada::Ini ini("subfolder/some_ini_file.ini");
if (ini.good()) {
    int i = ini.get_int<int>("first"); // 1
    double d = ini.get_float<double>("second"); // 2.5
    std::string s = ini.get("fourth"); // "some value"
}
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
// Sum elements using multi-threading if available
std::vector<unsigned> v = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
unsigned sum = NADA_SUM(v, std::plus()); // sum == 10

// Comparator for objects behind raw pointers or smart-pointers:
std::vector<std::string*> v; // note: std::string* not regular std::string
//std::vector<std::shared_ptr<std::string>> v // also possible
//std::vector<std::unique_ptr<std::string>> v // also possible
// ... fill v
std::sort(v.begin(), v.end(), nada::misc::ptr_compare); // sorts strings in v lexically
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

```
