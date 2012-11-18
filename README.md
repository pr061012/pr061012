pr061012
========

**pr061012** is a strategy game with indirect control.

Game's name, features and concept are coming soon.

Compilation
===========

To compile pr061012 you need following libraries:
* armadillo (>= 3.2.3)
* GL
* GLFW (>= 2.7.2 or >= 3.0.0)
* GLC (>= 0.7.2)
* SOIL (>= 1.07)

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

Current bugs
============
* aim == 0 in Humanoid
