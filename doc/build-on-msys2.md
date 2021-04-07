# Build on Msys2

This document illustrates the steps to build this project in the MSYS2 MinGW-w64-x86_64 environment. 

## Revision History

Last Update Date: 2021.04.07

- 2021.04.07: Initial Document, add steps for building this project on MSYS2.


## Environment

- MSYS2: [msys2-x86_64-20210228.exe](https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20210228.exe)
    - SHA256 checksum: `ef1dbd40d03eda274f6d101792e5d197f0709fd306967c42be025f8746fcd9af`
    - GPG signature: `0xf7a49b0ec`

## Steps

Prepare the source code and its submodule dependencies.

```
pacman -S git
git clone https://github.com/cy20lin/gl
cd gl
git submodule update --init --recursive
```

Install dependant packages.

```bash
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-glfw
pacman -S mingw-w64-x86_64-glew
pacman -S mingw-w64-x86_64-glbinding
pacman -S mingw-w64-x86_64-boost
pacman -S mingw-w64-x86_64-opencv
pacman -S mingw-w64-x86_64-fmt
```

Configure and build the apps.

```bash
cd gl
mkdir build
cd build
cmake .. -GUnix\ Makefiles
```

## Run the programs

Followings are runnable apps.

```bash
./1.1.hello_window.exe
./1.2.hello_polygon.exe
./1.2.hello_rectangle.exe
./1.2.hello_triangle.exe
./1.3.breath_triangle.exe
./1.3.mix_color_triangle.exe
./1.3.our_own_shader_class.exe
./1.3.red_triangle.exe
./1.4.texture.exe
./1.4.texture2.exe
./1.5.transformation.exe
./1.6.coordinate_system.exe
./1.6.coordinate_system2.exe
./1.6.coordinate_system3.exe
./a.exe
./b.exe
./imgui.exe
./sensor_emitter_server.exe
./tut1.exe
./tut2.exe
```

## References

- [MSYS2 Official Website](https://www.msys2.org/)