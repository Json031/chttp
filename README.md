# chttp
A tiny C networking helper library.

## Build
```bash
make && sudo make install
```
# Usage
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
# Debug
1. terminal: ```git clone https://github.com/json031/chttp.git```
2. Replace the url and url param and requestbody param in main.c file
3. terminal: ```brew install cjson```
4. terminal: ```brew install curl```
5. terminal: ```arch -x86_64 gcc src/*.c test/*.c -I/usr/local/opt/cjson/include -L/usr/local/opt/cjson/lib -lcjson -lcurl -o test_chttp```
6. terminal: ```./test_chttp```

## License
Copyright MIT License
