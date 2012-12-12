/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef GOD_H
#define GOD_H

#include "../World/World.h"
#include "../../common/Vector/Vector.h"
#include <vector>

/**
 * @class God
 * @brief God class
 */
class God
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    God(World& world);

    /**
     * @brief Destructor.
     */
    ~God();

    /**
     * @brief setWeatherAt
     * @param x
     * @param type
     * @return successful of operation
     */
    void setWeatherAt(Vector x, WeatherType type);

private:
    World& world;

protected:
    /// Array with actions.
    std::vector <Action> actions;

};

#endif // GOD_H
