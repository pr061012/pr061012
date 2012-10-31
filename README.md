pr061012
========

**pr061012** is a strategy game with indirect control.

Game's name, features and concept are coming soon.

ToDo
====

*Right now!*

1. Add logger (or just use cerr?)
2. Add classes:
   * Action (exception)
   * Controller & PossibilityChecker
   * ObjectHeap::iterator
   * SpellTree
3. Add interfaces:
   * IWorld
   * IGod
4. Decide about:
   * Tool::material_type is needed?
   * Tool::max_quality?
   * Humanoid::owned_objs and viewed_objs are ObjectHeaps or vectors?
   * SpeelTree -- inner struct
   * IWorld -- methods
   * how Controller changes world?
   * ObjectFactory -- map[string] -> void * or int?
   * Indexator -- inner struct

*In future:*

1. Write a common documentation tex-file with:
   * main concept
   * UML diagram with description about how it works
