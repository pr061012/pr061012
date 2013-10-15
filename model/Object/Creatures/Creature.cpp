/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cmath>

#include "Creature.h"
#include "../Resource/Resource.h"
#include "../Weather/Weather.h"
#include "../../../common/BasicDefines.h"
#include "../../../common/Math/Random.h"
#include "../../../common/Math/DoubleComparison.h"
#include <assert.h>

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
    force(Random::int_range(CREAT_FORCE_MIN, CREAT_FORCE_MAX)),
    max_endurance(Random::int_range(CREAT_ENDURANCE_MAX,  CREAT_ENDURANCE_MAX)),
    endurance(max_endurance),
    max_age(0),
    age(0),
    max_health(Random::int_range(CREAT_HEALTH_MIN, CREAT_HEALTH_MAX)),
    health(max_health),
    max_sleepiness(Random::int_range(CREAT_SLEEPINESS_MIN, CREAT_SLEEPINESS_MAX)),
    sleepiness (0),
    max_hunger(Random::int_range(CREAT_HUNGER_MIN, CREAT_HUNGER_MAX)),
    hunger(0),

    // steps
    hunger_steps(CREAT_STEPS),
    sleepiness_steps(CREAT_STEPS),
    age_steps(CREAT_AGE_STEPS),
    health_steps(CREAT_REGEN_HEALTH_STEPS),
    endurance_steps(CREAT_REGEN_ENDURANCE_STEPS),
    danger_steps(0),
    
    prev_action(GO),
    prev_action_state(SUCCEEDED),

    // needs
    need_in_descendants(0),  // we need in function to calculate it
                             // different for HUM and NON_HUM?
                             //
    desc_steps(CREAT_DESC_STEPS),
    decr_sleep_step(0),
    max_decr_sleep_step(0),
    danger(0),
    
    // direction
    angle(0),
    direction_is_set(false),
    aimless(true),
    current_goal_point(0, 0),
    aim(0),

    // decision
    current_decision(NONE),
    current_action(NONE),
    attrs(arma::mat(DM_ATR_CONST, 1)),
    brains(dmaker)
{
}

Creature::~Creature()
{
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

CreatureAction Creature::getCurrentDecision() const
{
    return current_decision;
}

CreatureAction Creature::getCurrentAction() const
{
    return current_action;
}

void Creature::setCurrentAction(CreatureAction act)
{
    this -> current_action = act;
}

double Creature::getAngle() const
{
    return angle;
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
    this -> attrs(ATTR_HEALTH, 0) = 100 * (100 - health) / max_health;
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
    this -> attrs(ATTR_HEALTH, 0) = 100 * (100 - health) / max_health;
    return d;
}

ObjectHeap * Creature::getDropObjects()
{
    return &drop_objects;
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


const Object* Creature::getAim() const
{
    return this -> aim;
}

//**********************************************************
// DANGER EVALUATION
//**********************************************************

// Evaluates object's danger depending on the distance to it.
double Creature::evaluateDanger(const Object * obj, const Vector& coords)
{
    double view_radius = view_area.getSize() / 2;
    double distance = coords.getDistance(obj -> getCoords());
    double my_radius = getShape().getSize() / 2;
    double obj_radius = obj -> getShape().getSize() / 2;

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

    double danger_ratio = obj -> getDangerLevel() * CREAT_DANGER_FACTOR;

    if (obj -> isMovable())
    {
        // linear dependency: == 0 at bounds of view_area
        //                    == danger_ratio when standing next to the object.
        return fmax(- danger_ratio / (view_radius - my_radius) * distance + 
            danger_ratio * (1 + 1 / (view_radius - my_radius)) - getDangerLevel(), 0);
    }
    else
    {
        // immovable objects are dangerous only at near distances.
        if (distance - obj_radius < 
            CREAT_DANGER_IMMOVABLE_FACTOR * obj -> getNormalSpeed())
        {
            return danger_ratio;
        }
        else
        {
            return 0;
        }
    }
}

void Creature::chooseDirectionToEscape()
{
    // Initialize vector of escaping.
    Vector escape_vector(0, 0);

    // Add all dangerous objects danger levels as vectors
    // with length equal to object's danger level and
    // angle equal to direction to the object
    ObjectHeap::const_iterator iter;
    Vector coords = getCoords();
    for(
        iter = objects_around.begin();
        iter != objects_around.end(); iter++
       )
    {
        angle = getCoords().getAngle((*iter) -> getCoords());
        escape_vector += Vector(cos(angle), sin(angle)) * 
                         evaluateDanger(*iter, coords);
    }

    // go to the opposite direction of biggest danger
    escape_vector = getCoords() - escape_vector * getViewArea().getSize() / 2;
    setAim(escape_vector);
}

//**********************************************************
// ACTIONS
//**********************************************************

void Creature::setAim(Object * aim)
{
    this -> aim = aim;
    direction_is_set = false;
    aimless = false;
}

void Creature::setAim(Vector point)
{
    this -> aim = nullptr;
    direction_is_set = false;
    aimless = false;
    current_goal_point = point;
}

void Creature::resetAim()
{
    this -> aim = nullptr;
    goal = nullptr;
    direction_is_set = false;
    aimless = true;
}

// Go with the given speed
void Creature::go(SpeedType speed)
{
    // Update attributes.
    if (speed == FAST_SPEED)
    {
        decreaseEndurance(1);
    }
    endurance_steps++;

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

    // If we don't have any aim, go the way we went before
    if (aimless)
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
        // FIXME Need Refactoring!!!
        // Check if we have any particular object to move to.
        if (aim)
        {
            if(!goal || aim -> getObjectID() != goal -> getObjectID())
            {
                goal = aim;
            }
            current_goal_point = goal -> getCoords();
        }

        // Reset route if we got stuck or the goal has changed.
        if (!direction_is_set ||
            !DoubleComparison::isLess(last_goal_pos.getDistance(current_goal_point),
                                        MAX_OFFSET * getShape().getSize()/2))
        {
            last_goal_pos = current_goal_point;
            
            //generate route
            last_route_size = route.size();
            route = generateRoute();
            angle = this -> getCoords().getAngle(route.top()); 
            direction_is_set = true;
        }

        // if we reached the target, face to the next point
        double my_speed = getNormalSpeed();
        if (speed == FAST_SPEED)
        {
            my_speed *= SPD_FAST_SPEED_COEF;
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
        // Hit the aim if it is within our reach
        if (reach_area.hitTest(aim -> getShape()))
        {
            fight();
        }
        else
        {
            // Run at the target if it is close enough.
            if (getCoords().getDistance(aim -> getCoords()) < CREAT_RUSH_DISTANCE)
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

void Creature::relax()
{
    health_steps -= CREAT_RELAX_REGEN_HEALTH;
    endurance_steps -= CREAT_RELAX_REGEN_ENDURANCE;
}

// Sleeping
void Creature::sleep()
{
    health_steps -= CREAT_SLEEP_REGEN_HEALTH;
    endurance_steps -= CREAT_SLEEP_REGEN_ENDURANCE;

    // if the time has come, then decrease sleepiness
    if (decr_sleep_step <= 0)
    {
        decreaseSleepiness(1);
        if (!sleepiness)
        {
            this -> attrs(ATTR_SLEEPINESS, 0) = 0;
        }
        decr_sleep_step += max_decr_sleep_step;
    }
    else
    {
        decr_sleep_step--;
    }
}

// Clears actions and saves the result of previous one.
void Creature::clearActions()
{
    if (actions.size())
    {
        prev_action = actions[0].getType();
        prev_action_state = actions[0].getState();
        prev_action_error = actions[0].getError();
    }
    actions.clear();
}

//******************************************************************************
// INHERETED THINGS.
//******************************************************************************

std::string Creature::printObjectInfo(bool full) const
{
    std::stringstream ss;

    ss << Object::printObjectInfo(full) <<
          insertSpaces("Current action");

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
    ss << std::endl;

    ss << insertSpaces("Force")                << force << std::endl <<
          insertSpaces("Age")                  << age << "/" << max_age << std::endl <<
          insertSpaces("Endurance")            << endurance << "/" << max_endurance << std::endl <<
          insertSpaces("Sleepiness")           << sleepiness << "/" << max_sleepiness << std::endl <<
          insertSpaces("Hunger")               << hunger << "/" << max_hunger << std::endl <<
          insertSpaces("Need in descendants")  << need_in_descendants << std::endl <<
          insertSpaces("Danger around")        << danger << std::endl;

    if (full)
    {
        ss << insertSpaces("Direction is set") << (direction_is_set ? "yes" : "no") << std::endl <<
              insertSpaces("Direction angle")  << angle << std::endl;
    }

    ss << insertSpaces("Aim ID")               << (aim == nullptr ? "none" : std::to_string(aim -> getObjectID())) << std::endl;

    if (full)
    {
        ss << insertSpaces("Aimless")          << (aimless ? "yes" : "no") << std::endl <<
              insertSpaces("Goal point")       << current_goal_point.getX() << ", " << current_goal_point.getY() << std::endl <<
              "Drop objects"                   << std::endl << drop_objects.printIDs() <<
              "Objects around"                 << std::endl << objects_around.printIDs() <<
              "Matrix of attrs"                << printAttrs() <<
              "Matrix of action"               << printActMatrix();
    }

    return ss.str();
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

//**********************************************************
// UPDATES
//**********************************************************

// look for objects around and count danger level
void Creature::updateDanger()
{
    ObjectHeap::const_iterator iter;
    this -> danger = 0;
    Vector coords = getCoords();

    for(
        iter = objects_around.begin();
        iter != objects_around.end(); iter++
       )
    {
        this -> danger += evaluateDanger(*iter, coords);
        assert(!isnan(danger));
    }

    // Update stats
    danger_steps = CREAT_DANGER_STEPS;
    attrs(ATTR_DANGER,0) = danger;
}

// Update age, hunger, sleepiness, health, danger.
void Creature::updateCommonAttrs()
{
    // Reset reach and view area.
    reach_area.setCenter(getCoords());
    view_area.setCenter(getCoords());

    // Age updating
    if (age_steps <= 0)
    {
        increaseAge(1);
        age_steps += CREAT_AGE_STEPS;
    }
    else
    {
        age_steps--;
    }

    if (!hunger)
    {
        this -> attrs(ATTR_HUNGER, 0) = 0;
    }
    
    // Hunger updating
    if (hunger_steps <= 0)
    {
        // Starving
        if (hunger == max_hunger)
        {
            damage(CREAT_DELTA_HEALTH); 
            hunger_steps += CREAT_STARVING_STEPS;
        }
        else
        {
            increaseHunger(CREAT_DELTA_HUNGER);
            hunger_steps += CREAT_STEPS;
        }
        this -> attrs(ATTR_HUNGER, 0) = 100 * hunger / max_hunger;
    }
    else
    {
        hunger_steps--;
    }

    // Sleepiness updating
    if (sleepiness_steps <= 0)
    {
        if (current_action != SLEEP)
        {
            increaseSleepiness(CREAT_DELTA_SLEEP);
        }
        sleepiness_steps += CREAT_STEPS;
        this -> attrs(ATTR_SLEEPINESS, 0) = 100 * sleepiness / max_sleepiness;
    }
    else
    {
        sleepiness_steps--;
    }

    // Regenerating health.
    if (health_steps <= 0)
    {
        heal(CREAT_DELTA_HEALTH);
        health_steps += CREAT_REGEN_HEALTH_STEPS;
    }
    else
    {
        health_steps--;
    }

    // Regenerating endurance.
    if (endurance_steps <= 0)
    {
        increaseEndurance(CREAT_DELTA_ENDUR);
        endurance_steps += CREAT_REGEN_ENDURANCE_STEPS;
    }
    else
    {
        endurance_steps--;
    }


    // Danger updating
    if (danger_steps <= 0)
    {
        updateDanger();
    }
    else
    {
        danger_steps--;
    }

}
