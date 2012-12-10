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
 *        **init**
 *
 *          *init size* -- initialises clear world with specified size.
 *
 *        **random-init**
 *
 *          *random-init size* -- initialises world with specified size and
 *          randomly generated units.
 *
 *        **generate**
 *          *generate x y density cluster_type* -- generates a bundle of objects
 *          around (x, y) point.
 *
 *        **create**
 *
 *          *create x y type [additional args]* -- creates new object.
 *
 *          List of additional args for different types:
 *              * *c* (Creature): CreatureType (h/nh), NonHumanoidType (cow/
 *                dragon) -- nh only.
 *              * *b* (Building): max health (uint), max space (uint).
 *              * *r* (Resource): ResourceType (water/grass/berries/meat/tree),
 *                resource amount (uint).
 *              * *w* (Weather): WeatherType (clouds/hurricane/meteor-shower/
 *                rain), weather living steps (uint).
 *
 *        **list**
 *
 *          *list [type]* -- list objects by type, if specified, otherwise list
 *          all objects.
 *
 *        **info**
 *
 *          *info id* -- prints object's information by id.
 *
 *        **change**
 *
 *          *change id field new_value* -- changes object's field.
 *
 *          List of fields names:
 *              * center -- two doubles
 *              * shape -- circle/square
 *              * size -- double
 *              * danger -- uint
 *              * immortality -- toggles immortality
 *              * solidity -- toggles solidity
 *              * destroyed -- toggles destroyed flag
 *              * age/mage (Creature only) -- uint
 *              * endurance/mendurance (Creature only) -- uint
 *              * hunger/mhunger (Creature only) -- uint
 *              * health/mhealth (Creature only) -- uint
 *              * sleepiness/msleepiness (Creature only) -- uint
 *              * force (Creature only) -- uint
 *              * a -- CreatureAction (none/sleep/eat/build/gather/communicate/
 *                work/realize-dream/escape/do-nothing)
 *              * da -- HumanoidDetailedAct (hunt/inv-food/find-food/home-relax/
 *                home-sleep/ground-sleep/mine-res/build-house/choose-hplace/
 *                fight/run-from-danger)
 *
 *        **step**
 *
 *          *step [amount]* -- does Controller's steps (suppose amount = 1, if
 *          isn't specified).
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
     * @brief  `init` and `random-init` commands.
     * @param  ss       stream with args
     * @param  random   use random object generation or not
     * @return command output
     */
    std::string init(std::stringstream& ss, bool random);

    /**
     * @brief  `generate` command.
     * @param  ss   stream with args
     * @return command output
     */
    std::string generate(std::stringstream& ss);

    /**
     * @brief  `create` command.
     * @param  ss   stream with args
     * @return command output
     */
    std::string create(std::stringstream& ss);

    /**
     * @brief  `list` command.
     * @param  ss       stream with args
     * @param  columns  amount of output columns
     * @return command output
     */
    std::string list(std::stringstream& ss, uint columns = 2);

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
     * @brief  `change` command.
     * @param  ss   stream with args
     * @return command output
     */
    std::string change(std::stringstream& ss);
};

#endif // CLI_H
