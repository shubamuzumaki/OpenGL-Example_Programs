# OpenGL-Examples_Programs

This repo contains various small graphics program made in `c++` using `OpenGL` to get you started in OpenGL.

## List of programs

:one: Line Drawing Algos(DDA and Bresenham)

:two: Circle Drawing Algos(DDA and Bresenham)

:three: 2D Transformation

:four: Color Pane

:five: Patterns

:six: Line Clipping

:seven: Koch Curve

:eight: Sedd Filling

## How to Run :runner:

### Linux

Make Sure that your Device has OpenGL installed. If not, install it using this command :

``` sh
$ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

Now open the terminal in the current directory and select the program u want to run. Compile that program using the following command : 

``` sh
g++ program_to_run.cpp -lglut -lGL -lGLU
```

And now you can execute the program using the command :  

``` sh
./a.out
```

### Windows/Mac (Visual Studio)

Make Sure that Visual-Studio is set up for Open-GL projects. if not watch <a href="https://www.youtube.com/watch?v=8p76pJsUP44&t=555s">this</a> tutorial.

:one: Clone this repo.

:two: Open the `.sln` file in Visual Studio.

:three: <kbd>Command/ctrl + F5</kbd> - Run default program.

:four: To run different program go to `solution explorer(ctrl+alt+L)` window and <kbd>right click</kbd>  on `source files` and exclude the `---.cpp` file from the project.

:five: <kbd>shift + alt + a </kbd> to add existing file in the project. open the current project directory and select the `---.cpp` file you want to run.

## Line Drawing Algos
  
> DDA(Digital Differential Analyzer)
>
> Bresenham

### DDA

In computer graphics, a digital differential analyzer (DDA) is hardware or software used for interpolation of variables over an interval between start and end point. DDAs are used for rasterization of lines, triangles and polygons.

:point_right: to learn more click <a href="https://www.geeksforgeeks.org/dda-line-generation-algorithm-computer-graphics/">here</a>

### Bresenham

Bresenham's line algorithm is a line drawing algorithm that determines the points of an n-dimensional raster that should be selected in order to form a close approximation to a straight line between two points.

:point_right: to learn more click <a href="https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/">here</a>

### Demo

## Circle Drawing Algos

> <a href="https://www.youtube.com/watch?v=q2LF8hH-dKM">DDA</a>

> <a href="https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/"> Bresenham</a>

> <a href="https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/"> Mid-Point</a>

### Demo



