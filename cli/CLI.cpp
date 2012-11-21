/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "CLI.h"

CLI::CLI(World* world, Controller* control) :
    world(world),
    control(control)
{
}

std::string CLI::runCommand(std::string command)
{
    return std::string();
}
