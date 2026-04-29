# chttp
[English](#english) | [中文](#中文)

---

<a id="english"></a>
## English

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
/**
* GET Example
*/
chttp_response_t *res = chttp_get("https://httpbin.org/get");
if (res) {
    printf("%s\n", res->body);
    chttp_response_free(res);
}
/**
* POST Example
*/
chttp_response_t *res = chttp_post_json(
    "https://httpbin.org/post",
    "{\"name\":\"test\"}"
);
if (res) {
    printf("%s\n", res->body);
    chttp_response_free(res);
}
```

## Debug
1. terminal: ```git clone https://github.com/json031/chttp.git```
2. Replace the url and url param and requestbody param in main.c file
3. terminal: ```brew install cjson```
4. terminal: ```brew install curl```
5. terminal: ```arch -x86_64 gcc src/*.c test/*.c -I/usr/local/opt/cjson/include -L/usr/local/opt/cjson/lib -lcjson -lcurl -o test_chttp```
6. terminal: ```./test_chttp```

## License
This library is licensed under the [MIT License](https://github.com/Json031/chttp/blob/main/LICENSE).

---

<a id="中文"></a>
# 中文
`chttp` 是基于 `libcurl` 和 `cJSON` 构建的开源 C 语言 HTTP 请求库。
支持 GET、POST、文件上传请求，自带 JSON 响应解析能力。

## 安装
### 方式一 — Homebrew 安装（推荐 macOS/Linux）
```bash
brew tap json031/chttp
brew install chttp
```
入库后可直接：
```bash
brew install chttp
```

### 方式二 — 源码编译安装
```bash
git clone https://github.com/json031/chttp.git
cd chttp
make
sudo make install
```

### 方式三 — Git 子模块引入
```bash
git submodule add https://github.com/json031/chttp.git external/chttp
```

Makefile 配置：
```makefile
CFLAGS += -Iexternal/chttp/include
LDFLAGS += -Lexternal/chttp/lib -lchttp
```

CMake 配置：
```cmake
add_subdirectory(external/chttp)
target_link_libraries(your_project PRIVATE chttp)
```

## 编译安装
```bash
make && sudo make install
```

## 使用方式
```c
#include <chttp.h>

/**
* GET Example
*/
chttp_response_t *res = chttp_get("https://httpbin.org/get");
if (res) {
    printf("%s\n", res->body);
    chttp_response_free(res);
}
/**
* POST Example
*/
chttp_response_t *res = chttp_post_json(
    "https://httpbin.org/post",
    "{\"name\":\"test\"}"
);
if (res) {
    printf("%s\n", res->body);
    chttp_response_free(res);
}
```

## 调试步骤
1. 拉取源码
```bash
git clone https://github.com/json031/chttp.git
```
2. 修改 `main.c` 中的接口地址、参数和请求体
3. 安装依赖
```bash
brew install cjson
brew install curl
```
4. 编译测试
```bash
arch -x86_64 gcc src/*.c test/*.c -I/usr/local/opt/cjson/include -L/usr/local/opt/cjson/lib -lcjson -lcurl -o test_chttp
```
5. 运行
```bash
./test_chttp
```

## 开源协议
本项目基于 [MIT License](https://github.com/Json031/chttp/blob/main/LICENSE) 开源协议。
