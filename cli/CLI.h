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
    Controller * control;

    //**************************************************************************
    // COMMAND'S PROCESSORS.
    //**************************************************************************

    /**
     * @brief  `init` command.
     * @param  vsize    World's vertical size
     * @param  hsize    World's horizontal size
     * @return command output
     */
    std::string init(uint vsize, uint hsize);

    /**
     * @brief  `random-init` command.
     * @param  seed     World's seed
     * @param  vsize    World's vertical size
     * @param  hsize    World's horizontal size
     * @return command output
     */
    std::string randomInit(uint seed, uint vsize, uint hsize);

    /**
     * @brief  `create` command.
     * @param  type     object's type
     * @param  x        x coordinate
     * @param  y        y coordinate
     * @param  args     ParamArray with additional args
     * @return command output
     */
    std::string create(ObjectType type, double x, double y, ParamArray args);

    /**
     * @brief  `list` command.
     * @param  type     ParamArray with specified object types
     * @return command output
     */
    std::string list(ParamArray type);

    /**
     * @brief  `info` command.
     * @param  id       object's id
     * @return command output
     */
    std::string info(uint id);

    /**
     * @brief  `step` command.
     * @return command output
     */
    std::string step();

    /**
     * @brief  `trace-step` command.
     * @param  ids      array with ids of traced objects
     * @return command output
     */
    std::string traceStep(std::vector<uint> ids);

    // TODO: Add `change`. What about interface?
};

#endif // CLI_H
