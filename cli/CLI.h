/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#ifndef CLI_H
#define CLI_H

#include "../model/World/World.h"
#include "../control/Controller/Controller.h"

/**
 * @brief Command-Line-Interface class.
 */
class CLI
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     * @param world         pointer to World
     * @param control       pointer to Controller
     */
    CLI(World* world, Controller* control);

    /**
     * @brief Destructor.
     */
    ~CLI(){}

    //**************************************************************************
    // RUNNING COMMANDS.
    //**************************************************************************

    /**
     * @brief  Runs command.
     * @param  command      command
     * @return command output
     */
    std::string runCommand(std::string command);

private:
    //**************************************************************************
    // POINTERS.
    //**************************************************************************

    /// Pointer to World.
    World* world;

    /// Pointer to Controller.
    Controller* control;

    //**************************************************************************
    // COMMAND'S PROCESSORS.
    //**************************************************************************

    /**
     * @brief  `init` command.
     * @param  ss   stream with args
     * @return command output
     */
    std::string init(std::stringstream& ss);

    /**
     * @brief  `random-init` command.
     * @param  ss   stream with args
     * @return command output
     */
    std::string randomInit(std::stringstream& ss);

    /**
     * @brief  `create` command.
     * @param  ss   stream with args
     * @return command output
     */
    std::string create(std::stringstream& ss);

    /**
     * @brief  `list` command.
     * @param  ss   stream with args
     * @return command output
     */
    std::string list(std::stringstream& ss);

    /**
     * @brief  `info` command.
     * @param  ss   stream with args
     * @return command output
     */
    std::string info(std::stringstream& ss);

    /**
     * @brief  `step` command.
     * @param  ss   stream with args
     * @return command output
     */
    std::string step(std::stringstream& ss);

    /**
     * @brief  `trace-step` command.
     * @param  ss   stream with args
     * @return command output
     */
    std::string traceStep(std::stringstream& ss);

    /**
     * @brief  `change` command.
     * @param  ss   stream with args
     * @return command output
     */
    std::string change(std::stringstream& ss);
};

#endif // CLI_H
