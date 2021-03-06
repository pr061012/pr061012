/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef HUMANOID_H
#define HUMANOID_H

#include <string>

#include "../Creature.h"
#include "../../Building/Building.h"

/**
 * @class Humanoid
 * @brief Humanoid is clever creature, has own ideals, thoughts and preferences.
 *        Humanoids are base element in game, they makes their own decisions
 *        and influence and change world around them.
 */
class Humanoid : public Creature
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Random constructor (creates Humanoid with really random
     *        attributes).
     * @param dmaker    humanoid's decision maker
     */
    Humanoid(const DecisionMaker& dmaker);

    /**
     * @brief Destructor
     */
    virtual ~Humanoid();

    //**************************************************************************
    // TYPE NAME.
    //**************************************************************************

    std::string getTypeName() const;

    //**************************************************************************
    // INHERETED THINGS.
    //**************************************************************************

    std::vector <Action>* getActions();

    void receiveMessage(Message message);

    std::string printObjectInfo(bool full) const;

    //**************************************************************************
    // ID.
    //**************************************************************************

    /**
     * @brief  Returns humanoid's id.
     * @return humanoid's id
     */
    uint getHumanoidID() const;

    //**********************************************************
    // GETTERS
    //**********************************************************

    /// Gets current desicion of humanoid
    uint getCurrentDetailedAct() const;

    ///  Gets humanoid's home
    Building* getHome() const;

    /// Gets visual memory of humanoid
    ObjectHeap* getVisMem() const;

    /// Gets need in house
    uint getNeedInHouse() const;

    /// Gets bravery
    uint getBravery() const;

    /// Gets free space
    uint getFreeSpace();

    /// Gets capacity
    uint getCapacity();

    //**************************************************************************
    // SETTERS
    //**************************************************************************

    /**
     * @brief  Sets home pointer
     */
    void setHome(Building* home);

     /**
     * @brief Sets detailed action
     * @param detailed_act  new detailed humanoid action.
     */
    void setDetailedAction(DetailedHumAction detailed_act);

    //**********************************************************
    // INVENTORY
    //**********************************************************
    
    /**
     * @brief  Add object to inventory.
     * @param  obj object to add.
     * @return true if object was put in the inventory.
     */
    bool addToInventory(Object * obj);
    
    /**
     * @brief  Removes object from inventory.
     * @param  obj object to remove.
     */
    void removeFromInventory(Object * obj);

    /**
     * @brief Removes destroyed objects from inventory.
     */
    void cleanInventory();

    /**
     * @brief  Get inventory
     * @return inventory
     */
    ObjectHeap* getInventory();

private:
    //**************************************************************************
    // IDS.
    //**************************************************************************

    static uint CURRENT_HUM_ID;

    const uint hum_id;

    //**************************************************************************
    // COMMON INFORMATION.
    //**************************************************************************

    /// Humanoid's name.
    std::string name;

    //**************************************************************************
    // HUMANOID'S OBJECTS
    //**************************************************************************

    Building* home;

    //**************************************************************************
    // RELATIVE COEFFICIENTS.
    // May have any value. In decision maker we use only quotient of them (in
    // percents).
    // Some coefficients are declared in Object class -- health and max_health,
	// sleepiness and max_sleepiness, hunger and max_hunger.
    //**************************************************************************

    // Quotient = 100 => humanoid wants to talk with somebody.
    /// Current sociability.
    unsigned int sociability;
    /// Maximum possible value of sociability.
    unsigned int max_sociability;

    //**************************************************************************
    // ABSOLUTE COEFFICIENTS.
    // May take only value in range [0, 100].
    //**************************************************************************

    // If = 100, humanoid is very lazy.
    /// Laziness (const during time).
    unsigned int laziness;  //const?

    // If = 100, humanoid needs new house.
    /// Need in house.
    unsigned int need_in_house;

    // If = 100, humanoid needs resources.
    /// Need in points.
    unsigned int need_in_points;

    /// Bravery
    uint bravery;

    /// Creature's inventory.
    ObjectHeap * inventory;

    /// Capacity of the inventory.
    uint capacity;
    /// Space left in the inventory.
    uint free_space;

    //**************************************************************************
    // MEMORY
    //**************************************************************************

    ObjectHeap* visual_memory;

    /**
     * @brief Memorize seen object
     */
    void visualMemorize();

    //**************************************************************************
    // UPDATES
    //**************************************************************************

    void updateNeedInDesc();

    //**************************************************************************
    // HUMANOID'S LOGICS.
    //**************************************************************************

    /// Detailed action of humanoid
    DetailedHumAction detailed_act;

    /**
     * @brief Humanoid chooses the next action
     * @return CratureAction action
     */
    DetailedHumAction chooseAction(CreatureAction action); // is it good name?

    /**
     * @brief Humanoid chooses the way to decrease his hunger
     * @return DetailedHumAction detailed_act
     */
    DetailedHumAction chooseWayToEat();

    /**
     * @brief Humanoid chooses the way to decrease his sleepiness
     * @return DetailedHumAction detailed_act
     */
    DetailedHumAction chooseWayToSleep();

    /**
     * @brief Humanoid chooses the way to build his house
     * @return DetailedHumAction detailed_act
     */
    DetailedHumAction chooseWayToBuild();

    /**
     * @brief Humanoid chooses the way to escape danger
     * @return DetailedHumAction detailed_act
     */
    DetailedHumAction chooseWayToEscape();

    /**
     * @brief Humanoid chooses the way to relax
     * @return DetailedHumAction detailed_act
     */
    DetailedHumAction chooseWayToRelax();

    /**
     * @brief Make hum eat aim
     */
    void eat();

    /**
     * @brief Humanoid choose his food.
     */
    void chooseFood();

    //**************************************************************************
    // UPDATE STEP
    //**************************************************************************

    /// Amount of steps before decreasion of sleepiness. When HUM is sleeping
    uint decr_sleep_step;

    /// Amount of steps before decreasion of endurance. When HUM is escaping
    uint decr_endur_step;

    //**************************************************************************
    // ACTION ERROR
    //**************************************************************************

    /**
     * @brief  Processing os actions errors.
     * @return Array with action errors.
     */
    std::vector<ActionError> errorProcess();

    /// Array with current errors.
    std::vector<ActionError> current_errors;

    //**************************************************************************
    // MESSAGES
    //**************************************************************************

    void messageProcess();

    //**************************************************************************
    // HOME CREATION.
    //**************************************************************************

    /// How often he change direction when he try to choose place for home
    uint steps_to_choose_place;

    /**
     * @brief Runs HumanoidValueMap and choose the best place for home. (Or
     *        forces humanoid to roam around, if there is no best place at all.)
     */
    void chooseBestPlace();

    //**************************************************************************
    // SEARCHING FUNCTION
    //**************************************************************************

    /**
     * @brief Searching for resource
     * @param  type type of res.
     */
    void findNearestRes(ResourceType type);
    /**
     * @brief Searching for Victim
     */
    void findVictim();

    /**
     * @brief  Searching for res in inventory
     * @param  type Resource type
     * @return Object Founded obj
     */
    Object* isResInInventory(ResourceType type);

    //**************************************************************************
    // INVENTORY FUNC
    //**************************************************************************

    /**
     * @brief  Calculate, how many res amount should humanoid mine
     * @return uint res amount
     */
    uint calculateNecessResAmount();

    /**
     * @brief Move inventory to build inventory
     */
    void putInvInHome();

    /**
     * @brief  Drop on ground or put in home
     * @return bool drop - false; home - true
     */
    bool putHomeAux(ResourceType type);
};

#endif // HUMANOID_H
