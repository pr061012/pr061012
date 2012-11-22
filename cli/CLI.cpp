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
    if (cmd == "init")
    {
        return this -> init(ss);
    }

    if (cmd == "random-init")
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
        return this -> step(ss);
    }
    else if (cmd == "trace-step")
    {
    }

    return "Unknown command `" + cmd + "`.\n";
}

//******************************************************************************
// COMMAND'S PROCESSORS.
//******************************************************************************

std::string CLI::init(std::stringstream &ss)
{
    // FIXME: Interpreting only one size.
    int size = -1;
    ss >> size;

    if (ss.fail())
    {
        return std::string("Error: Integer argument expected.\n") +
               std::string("`init` syntax: init <size>\n");
    }

    if (size <= 0)
    {
        return "Error: Size must be greater than 0.\n";
    }

    this -> world -> reset(false);
    return "Successfully created clear world.\n";
}

std::string CLI::step(std::stringstream& ss)
{
    this -> control -> step();
    return "Successfully updated world.\n";
}
