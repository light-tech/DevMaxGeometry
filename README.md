Figure Generation for 2D Geometry
=================================

This example concerns implementation of a library of routines to make figures and illustrations. It is inspired by [Asymptote](http://asymptote.sourceforge.net/), a software to make technical illustration for LaTeX and [Geogebra](https://www.geogebra.org/).

When we look at [this presentation on Asymptote](http://asymptote.sourceforge.net/intro.pdf), we couldn't help but think: _The graphic language of Asymptote is pretty much C/C++ so why do we even need another language and compiler?_

Our first milestone is to build figures for 2D Euclidean geometry (i.e. points, lines, line segment, triangles, circles on Cartesian plane). For example, interpreting the following program using DevMax

```C++
// GenFigure1.cpp
typedef Figure<double> Fig;

Fig fig;

// Triangle ABC
Fig::Point A(0, 1, "A"), B(-1, -1, "B"), C(3, -1.25, "C");
fig.Add(A, B, C);

Fig::Triangle TABC(A, B, C);
fig.Add(TABC);

// Write out the figure to SVG file
char output_file_name[1024];
sprintf(output_file_name, "%s.svg", __FILE__);
fig.RenderAsSVG(600, 400, -2, 4, -2, 2, output_file_name);
PrintString("Done\n");
```

generate the following SVG file `GenFigure1.cpp.svg` in the project folder:

![Figure1](Figure1.svg)

which one can include in a LaTeX-written textbook. See [`GenFigure2.cpp`](GenFigure2.cpp) for a more complicated example.

As you can see, this is a pretty sweet exploit of DevMax's interpreter.

The API
-------

The main header for figure manipulation and SVG export is [`Figure.h`](include/Figure.h) which provide a templated class `Figure<R>` where `R` should be a real number type such as `float` or `double`. It contains various inner classes for various geometric objects such as `Point`, `Line`, `LineSegment`, etc. (mainly extending their purely geometric counterpart in the `G2D` namespace to provide appearance styling and naming) which one can construct and `Add` to the figure.

The geometric computations (projection from a point to a line, intersection of lines, parallel lines, etc.) are handled in [`Geometry2D.h`](include/Geometry2D.h).