#ifndef IWORLD_H
#define IWORLD_H

#include "../BasicTypes.h"
#include "../../view/ViewObject/ViewObject.h"
#include "Action/Action.h"
//#include "../God/God.h"

class IWorld
{
public:

    //******************************************************************************
    // WORLD <-> VIEW METHODS.
    //******************************************************************************

    virtual Object** getViewObjectsInRange(double x, double y, double radius) = 0;

    virtual WeatherType getWeatherAtPoint(double x, double y) = 0;
};

#endif // IWORLD_H

