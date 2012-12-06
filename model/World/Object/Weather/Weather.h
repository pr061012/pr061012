/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef WEATHER_H
#define WEATHER_H

#include "../Object.h"
#include "../../ObjectHeap/ObjectHeap.h"

/**
 * @class Weather
 * @brief Weather class
 */
class Weather : public Object
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    Weather(WeatherType type, uint living_steps = 0);

    /**
     * @brief Destructor.
     */
    virtual ~Weather();

    //**************************************************************************
    // INHERETED THINGS.
    //**************************************************************************

    std::vector<Action>* getActions();
    void receiveMessage(Message message);

    std::string getTypeName() const;
    std::string printObjectInfo(bool full) const;

    //**************************************************************************
    // WEATHER TYPE.
    //**************************************************************************

	/**
     * @brief  Get the value of subtype.
	 * @return the value of subtype
	 */
    WeatherType getSubtype() const;

    //**************************************************************************
    // HEALTH MANIPULATION.
    //**************************************************************************

    uint damage(uint delta);
    uint heal(uint delta);

    uint getHealthPoints() const;
    uint getMaxHealthPoints() const;


    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

	/**
     * @brief  Gets reference to heap with covered objects. This heap can be
     *         modified (in fact, Controller modify it by using Weather shape).
     * @return reference to heap with covered objects
	 */
    ObjectHeap* getCoveredObjects();

    /**
     * @brief Set covere objects
     * @param heap covered_objects
     */
    void setCoveredObjects(ObjectHeap heap);

    /**
     * @brief  Gets amount of living steps.
     * @return amount of living steps.
     */
    uint getLivingSteps() const;

private:
    /// Weather type.
    const WeatherType subtype;

    /// Covered objects. Is setted up by Controller by using Weather shape.
    ObjectHeap covered_objs;

    /// Steps for living.
    uint steps;

    /// Direction angle.
    double direction_angle;

    /// Roam steps.
    uint roam_steps;
};

#endif // WEATHER_H
