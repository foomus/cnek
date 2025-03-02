# Cnek
Classic snake game written in C

# Controls
* Arrows -> Move

## Fun fact
This project was made in August 2024 in around 6 hours of coding, debugging, and researching. It was my first project using SDL2.

## Building from source
It was developed and tested only on Windows 10. Linux and macOS are unsupported, forks that add compatibility to those OSes are welcomed.

The `MinGW-w64` toolchain was used to compile and test the application. Use `mingw32-make` while in the src folder to build. No additional dependencies are required.

Why is SDL embedded directly into the repo? Well, it was just easier for me to set up the makefile this way.

## Libraries used
* [SDL2](https://github.com/libsdl-org/) [SDL2 LICENSE](./src/SDL2/LICENSE)

## License
[MIT License](LICENSE.md)