/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "CLI.h"

#include <sstream>

//******************************************************************************
// CONSTRUCTOR.
//******************************************************************************

CLI::CLI(World* world, Controller* control) :
    world(world),
    control(control)
{
}

//******************************************************************************
// RUNNING COMMANDS.
//******************************************************************************

std::string CLI::runCommand(std::string command)
{
    // Creating string stream.
    std::stringstream ss(command);

    // Reading command.
    std::string cmd;
    ss >> cmd;

    // Reading command args and running processors.
    std::string output;
    if (cmd == "init")
    {
    }
    else if (cmd == "random-init")
    {
    }
    else if (cmd == "create")
    {
    }
    else if (cmd == "list")
    {
    }
    else if (cmd == "info")
    {
    }
    else if (cmd == "change")
    {
    }
    else if (cmd == "step")
    {
        output = this -> step();
    }
    else if (cmd == "trace-step")
    {
    }
    else
    {
        output = "Unknown command `" + cmd + "`.\n";
    }

    return output;
}

//******************************************************************************
// COMMAND'S PROCESSORS.
//******************************************************************************

std::string CLI::step()
{
    this -> control -> step();
    return std::string();
}
