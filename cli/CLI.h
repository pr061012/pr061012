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
 *
 *        **TODO**: Write full `create` and `list` description.
 *
 *        **init**
 *
 *          *init <size>* -- initialises clear world with specified size.
 *
 *        **random-init**
 *
 *          *random-init <size>* -- initialises world with specified size and
 *        randomly generated units.
 *
 *        **create**
 *
 *          *create <x> <y> <type> [additional args]* -- creates new object.
 *
 *        **list**
 *
 *          *list [type]* -- list objects by type, if specified, otherwise list
 *          all objects.
 *
 *        **info**
 *
 *          *info <id>* -- prints object's information by id.
 *
 *        **change**
 *
 *          *change <id> <field> <new_value>* -- changes object's field.
 *
 *        **step**
 *
 *          *step [amount]* -- does Controller's steps (suppose amount = 1, if
 *          isn't specified).
 *
 *        **trace-step**
 *          *trace-step [list of ids]* -- does on Controller's step and prints
 *          out changes for specified objects.
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
    // ARRAYS WITH NAMES.
    //**************************************************************************

    /// Array with object types names.
    std::vector <std::string> obj_types;

    /// Array with creature types names.
    std::vector <std::string> creat_types;

    /// Array with shape types names.
    std::vector <std::string> shape_types;

    /// Array with creature actions names.
    std::vector <std::string> creat_acts;

    /// Array with detailed humanoid actions names.
    std::vector <std::string> hum_acts;

    //**************************************************************************
    // COMMAND'S PROCESSORS.
    //**************************************************************************

    /**
     * @brief  `init` and `random-init` commands.
     * @param  ss   stream with args
     * @return command output
     */
    std::string init(std::stringstream& ss, bool random);

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
