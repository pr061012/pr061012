#ifndef IWORLD_H
#define IWORLD_H

#include "../BasicTypes.h"
#include "../../view/ViewObject/ViewObject.h"
#include "Action/Action.h"
#include "ObjectHeap/ObjectHeap.h"
#include "Indexator/Indexator.h"
#include "../Utilities/Shape/Shape.h"
//#include "../God/God.h"

class IWorld
{
public:
    virtual ~IWorld() = 0;

    //******************************************************************************
    // WORLD <-> CONTROLLER METHODS.
    //******************************************************************************

    virtual ObjectHeap* getVisibleObjects() = 0;

    virtual ObjectHeap* getHiddenObjects() = 0;

    virtual Indexator* getIndexator() = 0;

    virtual double getSize() = 0;

    //******************************************************************************
    // WORLD <-> VIEW METHODS.
    //******************************************************************************

    virtual Object** getViewObjectsInRange(double x, double y, double radius) = 0;

    virtual WeatherType getWeatherAtPoint(double x, double y) = 0;
};

#endif // IWORLD_H

