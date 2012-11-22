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

    // Running processors.
    if (cmd == "init")
    {
        return this -> init(ss, false);
    }

    if (cmd == "random-init")
    {
        return this -> init(ss, true);
    }

    if (cmd == "create")
    {
        return this -> create(ss);
    }

    if (cmd == "list")
    {
        return this -> list(ss);
    }

    if (cmd == "info")
    {
        return this -> info(ss);
    }

    if (cmd == "change")
    {
        return this -> change(ss);
    }

    if (cmd == "step")
    {
        return this -> step(ss);
    }

    if (cmd == "trace-step")
    {
        return this -> traceStep(ss);
    }

    return "Unknown command `" + cmd + "`.\n";
}

//******************************************************************************
// COMMAND'S PROCESSORS.
//******************************************************************************

std::string CLI::init(std::stringstream &ss, bool random)
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

    this -> world -> reset(size, random);
    return "Successfully created world.\n";
}

std::string CLI::create(std::stringstream& ss)
{
}

std::string CLI::list(std::stringstream& ss)
{
}

std::string CLI::info(std::stringstream& ss)
{
}

std::string CLI::step(std::stringstream& ss)
{
    this -> control -> step();
    return "Successfully updated world.\n";
}

std::string CLI::traceStep(std::stringstream& ss)
{
}

std::string CLI::change(std::stringstream& ss)
{
}
