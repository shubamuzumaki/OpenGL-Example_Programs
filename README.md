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

watch this :point_down: if you feel lost

![tutorial](https://user-images.githubusercontent.com/44112210/76170165-5e6e3380-61a5-11ea-81a4-f9a0dee86c57.gif)

## Line Drawing Algos

In this program we code basic line drawing algorithms used in graphics.

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

![line](https://user-images.githubusercontent.com/44112210/76170414-b73ecb80-61a7-11ea-843c-4f3bf7d91213.gif)

## Circle Drawing Algos

In this program we code various circle drawing algorithms used in graphics.

> <a href="https://www.youtube.com/watch?v=q2LF8hH-dKM">DDA</a>

> <a href="https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/"> Bresenham</a>

> <a href="https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/"> Mid-Point</a>

### Demo

![circle](https://user-images.githubusercontent.com/44112210/76170408-b27a1780-61a7-11ea-970b-0a72c5edfaed.gif)

### Color Pane

In this program basic color selection pane which can be used to color different polygons in different colors.

![colorpane](https://user-images.githubusercontent.com/44112210/76170411-b5750800-61a7-11ea-8a92-2ccd75800a4a.gif)

### Patterns

In this program we code different patterns by using line and circle drawing algorithms used above.

![pattern](https://user-images.githubusercontent.com/44112210/76170415-b7d76200-61a7-11ea-8739-a6cc94d7e59e.gif)
![pattern2](https://user-images.githubusercontent.com/44112210/76170416-b86ff880-61a7-11ea-880e-294005205a93.gif)

### Line Clipping

This is cohen sutherland line clipping algorithm. In this we clip line from cliiping window

![clip](https://user-images.githubusercontent.com/44112210/76170410-b443db00-61a7-11ea-984d-0f6b1769f4e9.gif)

### Koch Curve

Easy to just demonstrate rather than explaining

![koch](https://user-images.githubusercontent.com/44112210/76170413-b6a63500-61a7-11ea-86a7-c8e31a2f84b0.gif)
