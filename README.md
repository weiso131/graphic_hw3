## Install
### glfw
1. 編譯 glfw

```
git clone https://github.com/glfw/glfw.git
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

2. 把 glfw/build/src/Release/glfw3.lib 跟 glfw/include 拿出來丟到 libs ，確保結構長成這樣:
```
├── libs/
│   └── glfw/
│       ├── include/GLFW/...
│       └── lib/glfw3.lib
```

## Compile and Run
```
mkdir build
cd build
cmake ..
cmake --build .
cd Debug
./opengl_test.exe
```