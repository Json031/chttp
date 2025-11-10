# chttp
`chttp` is an open-source C library for making HTTP requests, built on top of `libcurl` and `cJSON`.  
It supports GET, POST, and file upload requests with JSON response parsing.

## Installation
### Option 1 — Install via Homebrew (recommended for macOS/Linux)
If you are using macOS or Linux with [Homebrew](https://brew.sh):

```bash
brew tap json031/chttp
brew install chttp
```
Or, after it’s accepted into Homebrew Core:

```bash
brew install chttp
```
### Option 2 — Build from source
If you prefer to build manually:
```bash
git clone https://github.com/json031/chttp.git
cd chttp
make
sudo make install
```
### Option 3 — Add as a Git submodule (for developers)

If you’re developing another C project that depends on chttp:
```bash
git submodule add https://github.com/json031/chttp.git external/chttp
```
Then include headers and link against it in your Makefile or CMakeLists.txt:
Using Makefile
```makefile
CFLAGS += -Iexternal/chttp/include
LDFLAGS += -Lexternal/chttp/lib -lchttp
```
Using CMake
```cmake
add_subdirectory(external/chttp)
target_link_libraries(your_project PRIVATE chttp)
```

## Build
```bash
make && sudo make install
```
## Usage
```c
#include <chttp.h>
```

```yaml
---

```bash
git add .
git commit -m "Initial release"
git remote add origin https://github.com/json031/chttp.git
git push -u origin main
git tag v1.0.0
git push origin v1.0.0
```
## Debug
1. terminal: ```git clone https://github.com/json031/chttp.git```
2. Replace the url and url param and requestbody param in main.c file
3. terminal: ```brew install cjson```
4. terminal: ```brew install curl```
5. terminal: ```arch -x86_64 gcc src/*.c test/*.c -I/usr/local/opt/cjson/include -L/usr/local/opt/cjson/lib -lcjson -lcurl -o test_chttp```
6. terminal: ```./test_chttp```

## License
Copyright MIT License
