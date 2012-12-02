/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cmath>

#include "Creature.h"
#include "../Resource/Resource.h"
#include "../../../../common/BasicDefines.h"
#include "../../../../common/Math/Random.h"
#include "../../../../common/Math/DoubleComparison.h"
#include "../Weather/Weather.h"

double Creature::world_size = SZ_WORLD_HSIDE;

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

Creature::Creature(CreatureType type, const DecisionMaker & dmaker) :
    Object(CREATURE),
    subtype(type),

    // route computing variables
    goal(0),
    last_goal_pos(0, 0),
    last_route_size(0),
    obstacles_index(0),

    // some general attributes
    force(Random::int_range(CREAT_FORCE_MIN,    CREAT_FORCE_MAX)),
    max_endurance(Random::int_range(CREAT_ENDURANCE_MAX,  CREAT_ENDURANCE_MAX)),
    endurance(max_endurance),
    max_age(0),
    age(0),
    max_health(Random::int_range(CREAT_HEALTH_MIN, CREAT_HEALTH_MAX)),
    health(max_health),
    max_sleepiness(Random::int_range(CREAT_SLEEPINESS_MIN, CREAT_SLEEPINESS_MAX)),
    sleepiness (100 - max_sleepiness),
    max_hunger(Random::int_range(CREAT_HUNGER_MIN,     CREAT_HUNGER_MAX)),
    hunger(100 - max_hunger),
    
    prev_action(GO),
    prev_action_state(SUCCEEDED),
    inventory(new ObjectHeap),
    current_action(NONE),
    attrs(arma::mat(DM_ATR_CONST, 1)),
    brains(dmaker),

    // needs
    need_in_descendants(0),
    danger(0),               // we need in function to calculate it
                             // different for HUM and NON_HUM?
                             //
    // step counters
    common_steps(CREAT_STEPS),
    age_steps(CREAT_AGE_STEPS),
    desc_steps(CREAT_DESC_STEPS),
    danger_steps(1),
    decr_sleep_step(1),
    
    // direction
    angle(0),
    direction_is_set(false),
    aim(0),
    current_decision(NONE)
{
}

Creature::~Creature()
{
    delete inventory;
    delete obstacles_index;
}

//******************************************************************************
// ACCESSORS.
//******************************************************************************
CreatureType Creature::getSubtype() const
{
    return this -> subtype;
}

void Creature::setObjectsAround(ObjectHeap objects_around)
{
    this -> objects_around = objects_around;
}

ObjectHeap * Creature::getObjectsAround()
{
    return &(this -> objects_around);
}

void Creature::setViewArea(Shape view_area)
{
    this -> view_area = view_area;
}

Shape Creature::getViewArea()
{
    return this -> view_area;
}

void Creature::setReachArea(Shape reach_area)
{
    this -> reach_area = reach_area;
}

Shape Creature::getReachArea()
{
    return this -> reach_area;
}

ObjectHeap * Creature::getInventory()
{
    return this -> inventory;
}

uint Creature::getCurrentDecision() const
{
    return current_decision;
}

//**********************************************************
// AGE
//**********************************************************

void Creature::setAge(uint age)
{
    if (age > max_age)
    {
        this -> age = max_age;
    }
    else
    {
        this -> age = age;
    }
}

uint Creature::getAge()
{
    return this -> age;
}

void Creature::setMaxAge(uint max_age)
{
    this -> max_age = max_age;
    if (age > max_age)
    {
        age = max_age;
    }
}

uint Creature::getMaxAge()
{
    return this -> max_age;
}

uint Creature::increaseAge(uint delta)
{
    if (max_age - this -> age < delta)
    {
        delta = max_age - this -> age;
    }

    this -> age += delta;
    return delta;
}

uint Creature::decreaseAge(uint delta)
{
    if (this -> age < delta)
    {
        delta = this -> age;
    }
    
    this -> age -= delta;
    return delta;
}


//**********************************************************
// HEALTH
//**********************************************************


void Creature::setHealth(uint health)
{
    if (health > max_health)
    {
        this -> health = max_health;
    }
    else
    {
        this -> health = health;
    }
}

uint Creature::getHealth()
{
    return this -> health;
}

void Creature::setMaxHealth(uint max_health)
{
    this -> max_health = max_health;
    if (health > max_health)
    {
        health = max_health;
    }
}

uint Creature::getMaxHealth()
{
    return this -> max_health;
}

//******************************************************************************
// CHANGING HEALTH.
//******************************************************************************

uint Creature::damage(uint delta)
{
    uint d = delta;

    if (this -> health < d)
    {
        d = this -> health;
    }

    this -> health -= d;
    return d;
}

uint Creature::heal(uint delta)
{
    uint d = delta;

    if (this -> health + d > this -> max_health)
    {
        d = this -> max_health - this -> health;
    }

    this -> health += d;
    return d;
}

uint Creature::getHealthPoints() const
{
    return this -> health;
}

uint Creature::getMaxHealthPoints() const
{
    return this -> max_health;
}

//**********************************************************
// HUNGER
//**********************************************************


void Creature::setHunger(uint hunger)
{
    if (hunger > max_hunger)
    {
        this -> hunger = max_hunger;
    }
    else
    {
        this -> hunger = hunger;
    }
}

uint Creature::getHunger()
{
    return this -> hunger;
}

void Creature::setMaxHunger(uint max_hunger)
{
    this -> max_hunger = max_hunger;
    if (hunger > max_hunger)
    {
        hunger = max_hunger;
    }
}

uint Creature::getMaxHunger()
{
    return this -> max_hunger;
}

uint Creature::increaseHunger(uint delta)
{
    if (max_hunger - this -> hunger < delta)
    {
        delta = max_hunger - this -> hunger;
    }

    this -> hunger += delta;
    return delta;
}

uint Creature::decreaseHunger(uint delta)
{
    if (this -> hunger < delta)
    {
        delta = this -> hunger;
    }
    
    this -> hunger -= delta;
    return delta;
}

//**********************************************************
// ENDURANCE
//**********************************************************

void Creature::setEndurance(uint endurance)
{
    if (endurance > max_endurance)
    {
        this -> endurance = max_endurance;
    }
    else
    {
        this -> endurance = endurance;
    }
}

uint Creature::getEndurance()
{
    return this -> endurance;
}

void Creature::setMaxEndurance(uint max_endurance)
{
    this -> max_endurance = max_endurance;
    if (endurance > max_endurance)
    {
        endurance = max_endurance;
    }
}

uint Creature::getMaxEndurance()
{
    return this -> max_endurance;
}

uint Creature::increaseEndurance(uint delta)
{
    if (max_endurance - this -> endurance < delta)
    {
        delta = max_endurance - this -> endurance;
    }

    this -> endurance += delta;
    return delta;
}

uint Creature::decreaseEndurance(uint delta)
{
    if (this -> endurance < delta)
    {
        delta = this -> endurance;
    }
    
    this -> endurance -= delta;
    return delta;
}


//**********************************************************
// SLEEPINESS
//**********************************************************

void Creature::setSleepiness(uint sleepiness)
{
    if (sleepiness > max_sleepiness)
    {
        this -> sleepiness = max_sleepiness;
    }
    else
    {
        this -> sleepiness = sleepiness;
    }
}

uint Creature::getSleepiness()
{
    return this -> sleepiness;
}

void Creature::setMaxSleepiness(uint max_sleepiness)
{
    this -> max_sleepiness = max_sleepiness;
    if (sleepiness > max_sleepiness)
    {
        sleepiness = max_sleepiness;
    }
}

uint Creature::getMaxSleepiness()
{
    return this -> max_sleepiness;
}

uint Creature::increaseSleepiness(uint delta)
{
    if (max_sleepiness - this -> sleepiness < delta)
    {
        delta = max_sleepiness - this -> sleepiness;
    }

    this -> sleepiness += delta;
    return delta;
}

uint Creature::decreaseSleepiness(uint delta)
{
    if (this -> sleepiness < delta)
    {
        delta = this -> sleepiness;
    }
    
    this -> sleepiness -= delta;
    return delta;
}


//**********************************************************
// FORCE
//**********************************************************

void Creature::setForce(uint force)
{
    this -> force = force;
}

uint Creature::getForce()
{
    return this -> force;
}


const Object* Creature::getAim()
{
    return this -> aim;
}

//**********************************************************
// DANGER EVALUATION
//**********************************************************

// Evaluates object's danger depending on the distance to it.
double Creature::evaluateDanger(const Object * obj)
{
    
    double view_radius = view_area.getSize() / 2;
    double distance = getCoords().getDistance(obj -> getCoords());
    double my_radius = getShape().getSize() / 2;
    double obj_radius = getShape().getSize() / 2;

    // ~1/R
    // - infinitely grows at r = 0 for any object - may cause problems
    /*
    // Dependent on:
    // - the ratio of object's danger to ours (== 1 if same)
    double danger_ratio = double(obj -> getDangerLevel()) / getDangerLevel();

    // - distance to object (== 1 if we stand right next to the object)
    //                      (== 1 + 1/CREAT_DANGER_DISTANCE_FACTOR if distacne == 0)
    double distance_ratio = (my_radius + obj_radius) * (CREAT_DANGER_DISTANCE_FACTOR + 1) / 
                            (distance + CREAT_DANGER_DISTANCE_FACTOR * (my_radius + obj_radius));

    // - size of view_area  (== 0 if we can't see object,
    //                       == 1 if we stand right next to the object)
    double view_ratio = fmax(0, (view_radius + obj_radius - distance) / 
                                (view_radius - my_radius));

    // - constant factor
    return pow(danger_ratio, 2) * distance_ratio * view_ratio * CREAT_DANGER_FACTOR;
    */

    // ~r
    double danger_ratio = pow(double(obj -> getDangerLevel()) / getDangerLevel(), 2) *
                            CREAT_DANGER_FACTOR;

    return fmax(- danger_ratio / (view_radius - my_radius) * distance + 
            danger_ratio * (1 + 1 / (view_radius - my_radius)), 0);
}

void Creature::chooseDirectionToEscape()
{
    // Initialize vector of escaping.
    Vector escape_vector(0, 0);

    // Add all dangerous objects danger levels as vectors
    // with length equal to object's danger level and
    // angle equal to direction to the object
    ObjectHeap::const_iterator iter;
    for(
        iter = objects_around.begin();
        iter != objects_around.end(); iter++
       )
    {
        angle = getCoords().getAngle((*iter) -> getCoords());
        escape_vector += Vector(cos(angle), sin(angle)) * evaluateDanger(*iter);
    }

    // go to the opposite direction of biggest danger
    this -> angle = Vector(0, 0).getAngle(escape_vector) + M_PI;
    aim = 0;
    direction_is_set = true;
}

//**********************************************************
// ACTIONS
//**********************************************************

// Go with the given speed
void Creature::go(SpeedType speed)
{
    // If we could not move, then reset direction
    if (prev_action == GO && prev_action_state == FAILED)
    {
        direction_is_set = false;
        // If we have the same route to the same aim, try to go random
        if (aim != nullptr && aim == goal && last_route_size == route.size())
        {
            angle = Random::double_num(M_PI * 2);
            Action act(GO, this);
            act.addParam<double>("angle", angle);
            act.addParam<SpeedType>("speed", speed);
            this -> actions.push_back(act);
            return;
        }
    }

    // if we don't have any aim, go the way we went before
    if (!aim)
    {
        // if there is no direction, then go random
        // or there is an error in angle
        if (!direction_is_set || isnan(angle))
        {
            direction_is_set = true;
            angle = Random::double_num(M_PI * 2);
        }
    }
    else
    {
        // if we can't go the way we went, or the aim changed,
        // or the aim moved too far, reset route
        if (!direction_is_set || !goal || 
            aim -> getObjectID() != goal -> getObjectID() || 
            !DoubleComparison::isLess(last_goal_pos.getDistance(goal -> getCoords()),
                                        MAX_OFFSET * getShape().getSize()/2))
        {
            goal = aim;
            last_goal_pos = goal -> getCoords();
            
            //generate route
            last_route_size = route.size();
            route = generateRoute();
            angle = this -> getCoords().getAngle(route.top()); 
            direction_is_set = true;
        }

        // if we reached the target, face to the next point
        double my_speed = 0;
        if (speed == SLOW_SPEED)
        {   
            my_speed = CREAT_SPEED_SLOW_VALUE;
        }
        else
        {
            my_speed = CREAT_SPEED_FAST_VALUE;
        }

        while (getCoords().getDistance(route.top()) < my_speed)
        {
            route.pop();

            // check if we reached the end
            if (route.empty())
            {
                direction_is_set = false;
                return;
            }

            // face to the the next point
            angle = this -> getCoords().getAngle(route.top());
            direction_is_set = true;
        }
    }

    // Generate GO action
    Action act(GO, this);
    act.addParam<double>("angle", angle);
    act.addParam<SpeedType>("speed", speed);
    this -> actions.push_back(act);
    if (speed == FAST_SPEED)
    {
        decreaseEndurance(1);
    }
}

// Fights the aim.
void Creature::fight()
{
    if (aim)
    {
        Action act(HARM_OBJS, this);
        act.addParticipant(aim);
        this -> actions.push_back(act);
    }
}

// Huunting algorithm.
void Creature::hunt()
{
    if (aim)
    {
        reach_area.setCenter(getCoords());
        // Hit the aim if it is within our reach
        if (reach_area.hitTest(aim -> getShape()))
        {
            fight();
        }
        else
        {
            // FIXME Magic constant
            if (getCoords().getDistance(aim -> getCoords()) < 7)
            {
                go(FAST_SPEED);
            }
            else
            {
                go(SLOW_SPEED);
            }
        }
    }
}

// Sleeping
void Creature::sleep()
{
    // if the time has come, then sleep, heal, and rest.
    if (!decr_sleep_step)
    {
        decreaseSleepiness(1);
        if (!sleepiness)
        {
            this -> attrs(ATTR_SLEEPINESS, 0) = 0;
        }
        increaseEndurance(1);
        heal(CREAT_DELTA_HEALTH);
        decr_sleep_step = max_decr_sleep_step;
    }
    else
    {
        decr_sleep_step--;
    }
}

// Clears actions and saves the result of previous one.
void Creature::clearActions()
{
    // TODO
    // Make it better (more info, history)
    if (actions.size())
    {
        prev_action = actions[0].getType();
        prev_action_state = actions[0].getState();
        prev_action_error = actions[0].getError();
    }
    actions.clear();

    // FIXME
    // maybe put this function outsitde?
    // 
    // Clear inventory from destroyed objects.
    // First place them in buffer.
    std::vector<Object*> buffer;
    for (ObjectHeap::iterator i = inventory -> begin();
         i != inventory -> end(); i++)
    {
        if ((*i) -> isDestroyed())
        {
            buffer.push_back(*i);
        }
    }

    // Then remove them from inventory.
    for (uint i = 0; i < buffer.size(); i++)
    {
        inventory -> remove(buffer[i]);
    }
}

//******************************************************************************
// INHERETED THINGS.
//******************************************************************************

std::string Creature::printObjectInfo() const
{
    std::string output = Object::printObjectInfo();

    std::stringstream ss;

    ss << "Current action\t\t";
    switch (current_action)
    {
        case NONE:          ss << "none";          break;
        case SLEEP:         ss << "sleep";         break;
        case EAT:           ss << "eat";           break;
        case BUILD:         ss << "build";         break;
        case GATHER:        ss << "gather";        break;
        case RELAX:         ss << "relax";         break;
        case EXPLORE:       ss << "explore";       break;
        case COMMUNICATE:   ss << "communicate";   break;
        case WORK:          ss << "work";          break;
        case REALIZE_DREAM: ss << "realize dream"; break;
        case ESCAPE:        ss << "escape";        break;
        case REPRODUCE:     ss << "reproduce";     break;
        case DO_NOTHING:    ss << "do nothing";    break;
        default:            ss << "unknown";       break;
    }
    ss << "\n";

    ss << "Force\t\t\t"           << force << std::endl <<
          "Age\t\t\t"             << age << "/" << max_age << std::endl <<
          "Endurance\t\t"         << endurance << "/" << max_endurance <<
                                     std::endl <<
          "Sleepiness\t\t"        << sleepiness << "/" << max_sleepiness <<
                                     std::endl <<
          "Hunger\t\t\t"          << hunger << "/" << max_hunger << std::endl <<
          "Need in descendants\t" << need_in_descendants << std::endl <<
          "Danger around\t\t"     << danger << std::endl <<
          "Direction is set\t"    << (direction_is_set ? "yes" : "no") <<
                                     std::endl <<
          "Direction angle\t\t"   << angle << std::endl <<
          "Aim ID\t\t\t"          << (aim == nullptr ? "none" :
                                     std::to_string(aim -> getObjectID())) <<
                                     std::endl <<
          "Inventory\t\t\t"       << std::endl << inventory -> printIDs() <<
          "Objects around\t\t"    << std::endl << objects_around.printIDs() <<
          "Matrix of attrs:\t\t"  << printAttrs() << std::endl <<
          "Matrix of act\t\t"     << printActMatrix() << std::endl;

    return output + ss.str();
}

std::string Creature::printAttrs() const
{
    std::stringstream ss;
    ss << std::endl;
    ss << "\tHUNGER:\t\t "       << attrs(ATTR_HUNGER,0)         << std::endl
       << "\tSLEEPINESS:\t "     << attrs(ATTR_SLEEPINESS,0)     << std::endl
       << "\tNEED_IN_HOUSE:\t "  << attrs(ATTR_NEED_IN_HOUSE,0)  << std::endl
       << "\tNEED_IN_POINTS:\t " << attrs(ATTR_NEED_IN_POINTS,0) << std::endl
       << "\tLAZINESS:\t "       << attrs(ATTR_LAZINESS,0)       << std::endl
       << "\tHEALTH:\t\t "       << attrs(ATTR_HEALTH,0)         << std::endl
       << "\tCOMMUNICATION:\t "  << attrs(ATTR_COMMUNICATION,0)  << std::endl
       << "\tDANGER:\t\t "       << attrs(ATTR_DANGER,0)         << std::endl
       << "\tNEED_IN_DESC:\t "   << attrs(ATTR_NEED_IN_DESC,0)   << std::endl;

    return ss.str();
}

std::string Creature::printActMatrix() const
{
    std::stringstream ss;
    arma::mat act = brains.getActMatrix(attrs);
    ss << std::endl;
    ss << "\tSLEEP:\t\t"        << act(0,0) << std::endl
       << "\tBUILD:\t\t"        << act(1,0) << std::endl
       << "\tWORK:\t\t"         << act(2,0) << std::endl
       << "\tEAT:\t\t"          << act(3,0) << std::endl
       << "\tRELAX:\t\t"        << act(4,0) << std::endl
       << "\tCOMMUNICATE:\t"    << act(5,0) << std::endl
       << "\tESCAPE:\t:\t"      << act(6,0) << std::endl
       << "\tREALIZE_DREAM:\t"  << act(7,0) << std::endl
       << "\tREPRODUCE:\t"      << act(8,0) << std::endl;

   return ss.str();
}

double Creature::setDirection()
{
    if (aim)
        return this -> getCoords().getAngle(aim -> getCoords());
    else
        return Random::double_num(M_PI * 2);
}


//**********************************************************
// UPDATES
//**********************************************************

// look for objects around and count danger level
void Creature::updateDanger()
{
    ObjectHeap::const_iterator iter;
    this -> danger = 0;

    for(
        iter = objects_around.begin();
        iter != objects_around.end(); iter++
       )
    {
        this -> danger += evaluateDanger(*iter);
        assert(!isnan(danger));
    }

    // Update stats
    danger_steps = CREAT_DANGER_STEPS;
    attrs(ATTR_DANGER,0) = danger;
}

// Update age, hunger, sleepiness, health, danger.
void Creature::updateCommonAttrs()
{
    // Age updating
    if (!age_steps)
    {
        increaseAge(1);
        age_steps = CREAT_AGE_STEPS;
    }
    else
    {
        age_steps--;
    }
    
    // Sleepiness and hunger updating
    if (!common_steps)
    {
        increaseHunger(CREAT_DELTA_HUNGER);

        if (current_action != SLEEP)
        {
            increaseSleepiness(CREAT_DELTA_SLEEP);
        }
        common_steps = CREAT_STEPS;
        // Update attributes
        this -> attrs(ATTR_SLEEPINESS, 0) = 100 * sleepiness / max_sleepiness;
        this -> attrs(ATTR_HUNGER, 0) = 100 * hunger / max_hunger;
        this -> attrs(ATTR_HEALTH, 0) = 100 * (100 - health) / max_health;
    }
    else
    {
        common_steps--;
    }

    // Starving
    if (hunger == max_hunger)
    {
        damage(CREAT_DELTA_HEALTH);
    }

    // Danger updating
    if (danger_steps)
    {
        updateDanger();
    }
    else
    {
        danger_steps--;
    }

}

//******************************************************************************
// INVENTORY
//******************************************************************************

// Adds object to inventory.
void Creature::addToInventory(Object *obj)
{
    // Resources should be stacked together
    if (obj -> getType() == RESOURCE)
    {
        ResourceType subtype = dynamic_cast<Resource*>(obj) -> getSubtype();
        for (ObjectHeap::iterator i = inventory -> begin(RESOURCE);
             i != inventory -> end(RESOURCE); i++)
        {
            if (dynamic_cast<Resource*>(*i) -> getSubtype() == subtype)
            {
                (*i) -> heal(obj -> getHealthPoints());
                obj -> markAsDestroyed();
                return;
            }
        }
    }

    // If there are no resources of this type, or it's something else, just push it.
    this -> inventory -> push(obj);
}

// Remove object from inventory.
void Creature::removeFromInventory(Object * obj)
{
    inventory -> remove(obj);
}
