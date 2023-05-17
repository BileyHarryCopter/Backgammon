# <div align="center">Backgammon</div>

Our project with Ivan aka [greggregbean](https://github.com/greggregbean). We implemented engine for the traditional game of Backgammon in C++.

For this project we wrote the graphical engine based on SDL2.

## Requirements

CMake with version 3.8 (or higher)

SDL2 library (you can install by this [tutorial](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php):)

## Rules and Agreements

To get acquainted with the rules of the game and its device, We recommend reading this [instruction](impl/assets/Backgammon_Briefing.pdf)

## How to clone and build
```
git clone git@github.com:BileyHarryCopter/course_project.git
```

```bash
cmake -B build -DCMAKE_BUILD_TYPE=[Release/Debug]
cmake --build build/
```

## How to run
```bash
cd build/impl/
./start
