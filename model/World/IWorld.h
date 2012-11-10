#ifndef IWORLD_H
#define IWORLD_H

#include "../BasicTypes.h"
#include "../../view/ViewObject/ViewObject.h"
#include "Action/Action.h"
#include "ObjectHeap/ObjectHeap.h"
#include "../Utilities/Shape/Shape.h"
//#include "../God/God.h"

class IWorld
{
public:
    //******************************************************************************
    // WORLD <-> CONTROLLER METHODS.
    //******************************************************************************

    virtual ObjectHeap* getAllObjects() = 0;

    virtual ObjectHeap* getObjectsInRange(double x, double y, double radius) = 0;

    virtual double getWidth() = 0;
    virtual double getHeight() = 0;

    //******************************************************************************
    // WORLD <-> VIEW METHODS.
    //******************************************************************************

    virtual Object** getViewObjectsInRange(double x, double y, double radius) = 0;

    virtual WeatherType getWeatherAtPoint(double x, double y) = 0;
};

#endif // IWORLD_H

