/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef CREATURE_H
#define CREATURE_H

#include <stack>

#include "../Object.h"
#include "../../DecisionMaker/DecisionMaker.h"
#include "../../ObjectHeap/ObjectHeap.h"
#include "../../../../common/BasicTypes.h"

/**
 * @class Creature
 * @brief Abstract Creature class.
 */
class Creature : public Object
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Random constructor (creates Creature with really random
     *        attributes).
     * @param type      creature's type
     * @param dmaker    creature's decision maker
     */
    Creature(CreatureType type, const DecisionMaker& dmaker);

    /**
     * @brief Destructor.
     */
    ~Creature();

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Get subtype
     * @return creature subtype
     */
    CreatureType getSubtype() const;

    /**
     * @brief Set the value of creature's window.
     * @param window    the new value of window
     */
    void setObjectsAround(ObjectHeap objects_around);

    /**
     * @brief  Get the value of creature's window.
     * @return the window
     */
    ObjectHeap* getObjectsAround();

    /**
     * @brief Set the value of view_area.
     * @param view_area the new value of view_area
     */
    void setViewArea(Shape view_area);

    /**
     * @brief  Get the value of view_area.
     * @return the value of view_area
     */
    Shape getViewArea();

    /**
     * @brief Set the value of reachg_area.
     * @param view_area the new value of reach_area
     */
    void setReachArea(Shape reach_area);

    /**
     * @brief  Get the value of reach_area.
     * @return the value of reach_area
     */
    Shape getReachArea();

    /**
     * @brief  Get inventory
     * @return inventory
     */
    ObjectHeap* getInventory();

    //**************************************************************************
    // AGE
    //**************************************************************************

    /**
     * @brief Set the value of age.
     * @param age   new value of age
     */
    void setAge(uint age);

    /**
     * @brief  Get the value of age.
     * @return the value of age
     */
    uint getAge();

    /**
     * @brief Set the value of max age.
     * @param max_age   new value of max age
     */
    void setMaxAge(uint max_age);

    /**
     * @brief  Get the value of max age.
     * @return the value of max age
     */
    uint getMaxAge();

    /**
     * @brief Increase age
     * @param delta the increment value
     * @return the added value
     */
    
    uint increaseAge(uint delta);
    
    /**
     * @brief Decrease age
     * @param delta the decrement value
     * @return subtracted value
     */
    
    uint decreaseAge(uint delta);
    

    //**************************************************************************
    // HEALTH
    //**************************************************************************

    /**
     * @brief Set the value of health.
     * @param health   new value of health
     */
    void setHealth(uint health);

    /**
     * @brief  Get the value of health.
     * @return the value of health
     */
    uint getHealth();

    /**
     * @brief Set the value of max health.
     * @param max_health   new value of max health
     */
    void setMaxHealth(uint max_health);

    /**
     * @brief  Get the value of max age.
     * @return the value of max age
     */
    uint getMaxHealth();

    //**************************************************************************
    // HUNGER
    //**************************************************************************

    /**
     * @brief Set the value of hunger
     * @param hunger new value of hunger 
     */
    void setHunger(uint hunger);

    /**
     * @brief  Get the value of hunger
     * @return the value of hunger
     */
    uint getHunger();

    /**
     * @brief Set the value of max_hunger
     * @param max_hunger new value of max_hunger 
     */
    void setMaxHunger(uint max_hunger);

    /**
     * @brief  Get the value of max_hunger
     * @return the value of max_hunger
     */
    uint getMaxHunger();

    /**
     * @brief Increase hunger
     * @param delta the increment value
     * @return the added value
     */
    
    uint increaseHunger(uint delta);
    
    /**
     * @brief Decrease hunger
     * @param delta the decrement value
     * @return subtracted value
     */
    
    uint decreaseHunger(uint delta);
    

    //**************************************************************************
    // ENDURANCE
    //**************************************************************************
    
    /**
     * @brief Set the value of endurance
     * @param endurance new value of endurance 
     */
    void setEndurance(uint endurance);

    /**
     * @brief  Get the value of endurance
     * @return the value of endurance
     */
    uint getEndurance();

    /**
     * @brief Set the value of max_endurance
     * @param max_endurance new value of max_endurance 
     */
    void setMaxEndurance(uint max_endurance);

    /**
     * @brief  Get the value of max_endurance
     * @return the value of max_endurance
     */
    uint getMaxEndurance();

    /**
     * @brief Increase endurance
     * @param delta the increment value
     * @return the added value
     */
    
    uint increaseEndurance(uint delta);
    
    /**
     * @brief Decrease endurance
     * @param delta the decrement value
     * @return subtracted value
     */
    
    uint decreaseEndurance(uint delta);
    

    //**************************************************************************
    // FORCE
    //**************************************************************************

    /**
     * @brief Set the value of force
     * @param force new value of force 
     */
    void setForce(uint force);
    
    /**
     * @brief  Get the value of force
     * @return the value of force
     */
    uint getForce();

    //**************************************************************************
    // SLEEPINESS
    //**************************************************************************

    /**
     * @brief Set the value of sleepiness
     * @param sleepiness new value of sleepiness 
     */
    void setSleepiness(uint sleepiness);
    
    /**
     * @brief  Get the value of sleepiness
     * @return the value of sleepiness
     */
    uint getSleepiness();
    
    /**
     * @brief Set the value of max_sleepines
     * @param max_sleepines new value of max_sleepines 
     */
    void setMaxSleepiness(uint max_sleepines);
    
    /**
     * @brief  Get the value of max_sleepines
     * @return the value of max_sleepines
     */
    uint getMaxSleepiness();

    /**
     * @brief Increase sleepiness
     * @param delta the increment value
     * @return the added value
     */
    
    uint increaseSleepiness(uint delta);
    
    /**
     * @brief Decrease sleepiness
     * @param delta the decrement value
     * @return subtracted value
     */
    
    uint decreaseSleepiness(uint delta);
    
    
    /**
     * @brief get the id of aim
     * @return id of aim
     */
    const Object* getAim();

    //**************************************************************************
    // DEBUG
    //**************************************************************************
    
    /// Get current action
    uint getCurrentDecision() const;

    //**************************************************************************
    // HEALTH MANIPULATION.
    //**************************************************************************

    uint getHealthPoints() const;
    uint getMaxHealthPoints() const;

    uint damage(uint delta);
    uint heal(uint delta);

    //**************************************************************************
    // Increase attributes
    //**************************************************************************
    /**
     * @brief Increases satiety level
     * @param delta parameter changes
     */
    void feed(uint delta);


    //**************************************************************************
    // INHERETED THINGS.
    //**************************************************************************

    virtual void receiveMessage(Message message) = 0;

    std::string printObjectInfo() const;

private:
    /// Creature's type.
    const CreatureType subtype;

    /// View area for Indexator.
    Shape view_area;

    /// Reach area.
    Shape reach_area;

    /// Typedef for path
    typedef std::stack<Vector> Path;

    /// Route to the goal
    Path route;

    /// Current goal towards which creature is moving
    Object* goal;

    /// Length of the last route
    uint last_route_size;

    //**********************************************************
    // ATTRIBUTES AND NEEDS
    //**********************************************************
    
    /// Force of creations
    uint force;

    /// Max endurance of creations
    uint max_endurance;
    /// Current endurance of creations
    uint endurance;

    /// Maximum possible age.
    uint max_age;
    /// Current age.
    uint age;

    /// Maximum possible health.
    uint max_health;
    /// Current health.
    uint health;

    // Quotient = 100 => creature wants sleep.

    /// Maximum possible value of sleepiness.
    uint max_sleepiness;

    /// Current value of sleepiness.
    uint sleepiness;

    /// Maximum possible value of hunger.
    uint max_hunger;
    // Quotient = 100 => creature wants eat.
    /// Current value of hunger.
    uint hunger;

protected:

    /// Prevoius action.
    ActionType prev_action;

    /// Previous action result
    ActionState prev_action_state;

    /// Previous action error
    ActionError prev_action_error;

    /// Creature's inventory.
    ObjectHeap * inventory;

    /**
     * @brief    Calculate the angle between first (this) and second (aim) object
     * @return   angle
     */
    double setDirection();

    /// Current creature's action.
    CreatureAction current_action;

    /// Creature's enviroment
    ObjectHeap objects_around;

    /// Matrix of attributes
    arma::mat attrs;

    /// Reference to creature's DecisionMaker.
    const DecisionMaker& brains;

    /// Current value of need_in_descendants (0-100)
	uint need_in_descendants;

    // If = 100, creature is in danger.
    /// Current danger.
    uint danger;

    /// Amount for steps to common update.
    uint common_steps;
    /// Amount for steps to age update.
    uint age_steps;
    /// Amount for steps to need_in_descendant update.
    uint desc_steps;
    /// Amount for steps to danger update.
    uint danger_steps;
    /// Amount of steps before decreasion of sleepiness. When creature is sleeping
    uint decr_sleep_step;

    //**************************************************************************
    // DIRECTION
    //**************************************************************************
    /// The direction of creature
    double angle;
    /// Flag that shows if direction is set
    bool direction_is_set;
    /// Current direction (subject) oh NHum
    Object* aim;

    //**************************************************************************
    // DECISION
    //**************************************************************************
    /// Current decision of creature
    CreatureAction current_decision;

    //**************************************************************************
    // UPDATES
    //**************************************************************************
    /**
     * @brief Updates age
     */
    virtual void updateAge() = 0;

    /**
     * @brief Updates need_in_descendants
     */
    virtual void updateNeedInDesc() = 0;

    /**
     * @brief Updates danger
     */
    void updateDanger();

    /**
     * @brief Updates hunger, sleepiness, health
     */
    virtual void updateCommonAttrs() = 0;

    //**************************************************************************
    // GO ACTION
    //**************************************************************************
    /**
     * @brief Updates hunger, sleepiness, health
     */

    void chooseDirectionToEscape();
    /**
     * @brief Generate action GO for creature (slow speed)
     * @param speed type of speed
     */
    void go(SpeedType speed);

    /**
     * @brief   Generate route to the given object
     * @param   goal Object to go to
     * @return  path to the goal
     */
    Path generateRoute();

    /**
     * @brief  Checks if creature can stand on the point
     * @param  point the point we check
     * @return 0 if creature can stand on the point
     *         1 if the point is the goal point
     *        -1 if creature can't stand on the point
     */

    virtual int checkPointIsPassable(Vector point, bool goal_in_sight);

    /// Neighnour offsets for generating vertices for path graph
    static const Vector neighbour_offsets[8];

    /// Heap of obstacles
    ObjectHeap * obstacles;

    //**********************************************************
    // FIGHTING
    //**********************************************************
    
    /**
     * @brief Damages object.
     * @param object victim.
     */
    void fight();

    /**
     * @brief Chases and tries to kill the target.
     */
    void hunt();

    //**********************************************************
    // ACTIONS
    //**********************************************************

    /**
     * @brief Store results of previous action and clear actions
     */
    
    void clearActions();

};


#endif // CREATURE_H
