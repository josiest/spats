# spatula

This is a simple header-only spatial searching library for modern C++ (>= 17).
The only datastructure currently offered is a kd-tree.

## Motivation

The goal is to have a simple nearest neighbors search interface. Other C++
libraries exist that do this, but it seems to be either the case that they're
overly complex, or not well documented or supported.
So the goal is to be simple, well-documented and well-tested. For this reason
the library currently only implements a simple kd-tree, since this is good
enough for small amounts of data in low dimensions.

### What `spatula` is not

The library does not attempt to be the most optimized library out there. If
this is what you're looking for, consider nanoflann.
