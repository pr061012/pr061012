pr061012
========

**pr061012** is a strategy game with indirect control.

Game's name, features and concept are coming soon.

Compilation
===========

**Note**: compilation will be succeeded with libraries/compilers versions given
below. But maybe you will succeed with lower versions (we don't know these
details).

To compile pr061012 you need following libraries:
* armadillo (⩾ 3.2.3)
* GL
* GLFW (⩾ 2.7.2 or ⩾ 3.0.0)
* GLC (⩾ 0.7.2)
* SOIL (⩾ 1.07)

Compilation succeed with following compilers:
* g++ (⩾ 4.7.2)
* clang++ (⩾ 3.1-8) (note: maybe you will need to apply [this patch](http://clang.llvm.org/libstdc++4.7-clang11.patch))

GNU/Linux
---------

In GNU/Linux distros there are packages for these libraries, so you can install
them by your package manager.

To compile pr061012 run:

    make

Current state
=============

We don't have enought time. Sad but true. In this case we're developing with
following conditions:

* There is one type of NonHumanoid (''cow''), two types of Resource (food
  and building material), one type of Building.
* No Tool and Weather at all.
* No communication between humanoids.
* No God.
