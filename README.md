pr061012
========

**pr061012** is a strategy game with indirect control.

Features
--------

* World with creatures, environment and resource.
* Two basic types of creatures: humanoid and non-humanoid (non-humanoid has
  subtypes: cow and dragon). Creature lives by itself, independetly from player:
  it makes own decisions about what to do and how to do it. Humanoids are clever
  creatures and the can make compilicated decisions, non-humanoids are silly and 
  have only few goals in its life (food and sleep).
* Several types of food: grass, berries and meat.
* One type of resource: tree (it is necessary for house building).
* Several types of weather: meteor shower (destroys everything), rain (heals
  trees, grass and berries), hurricane (moves moveable objects), clouds (without
  any effects).

Compilation
===========

**Note**: compilation will be succeeded with libraries/compilers versions given
below, but maybe you will succeed with lower versions.

To compile pr061012 you need following libraries:
* armadillo (⩾ 3.2.3)
* GL
* GLFW (⩾ 2.7.2 or ⩾ 3.0.0)
* GLC (⩾ 0.7.2)
* SOIL (⩾ 1.07)
* JsonCpp (⩾ 0.6.0)

In GNU/Linux distros (Ubuntu/Debian at least) there are packages for these
libraries, so you can install them by your package manager.

Compilation succeed with following compilers:
* g++ (⩾ 4.7.2)
* clang++ (⩾ 3.1-8) (note: maybe you will need to apply [this patch]
(http://clang.llvm.org/libstdc++4.7-clang11.patch))

GNU/Linux
---------

To compile pr061012 (in debug mode, sprites are not used):

    make

To compile project (with sprites):

    make view=pretty

How to play
===========

Command line
------------

Game starts with empty world. You need to "initialise" it manually by command
line (dark box in the bottom of the screen). Common commands:

* `random-init size` -- creates random world by size (with random generated
  objects)
* `init size` -- creates empty world by size
* `create` -- creates objects

For full description of commands look for [our documentation]
(http://pr061012.github.com/pr061012/classCLI.html#details).

Hot keys
--------

* arrows (← → ↑ ↓) -- move camera
* P -- pause
* mouse wheel -- zoom
* click on any object -- prints object's info to console (detailed) and window
  (shortened)

ToDo
====

* Switch to CMake.
* Try to compile under OS different from Linux.
* Fix bugs!
