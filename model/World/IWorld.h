#ifndef IWORLD_H
#define IWORLD_H

#include "../BasicTypes.h"
#include "../../view/ViewObject/ViewObject.h"
#include "Action/Action.h"
#include "ObjectHeap/ObjectHeap.h"
#include "Indexator/Indexator.h"
#include "../Utilities/Shape/Shape.h"
#include "../World/ObjectFactory/ObjectFactory.h"
//#include "../God/God.h"

class IWorld
{
public:
    virtual ~IWorld(){};

    //******************************************************************************
    // WORLD <-> CONTROLLER METHODS.
    //******************************************************************************

    virtual ObjectHeap* getVisibleObjects() = 0;

    virtual ObjectHeap* getHiddenObjects() = 0;

    virtual Indexator* getIndexator() = 0;

    virtual ObjectFactory* getObjectFactory() = 0;

    virtual double getSize() const = 0;

    //******************************************************************************
    // WORLD <-> VIEW METHODS.
    //******************************************************************************

    virtual std::vector<const Object*> getViewObjectsInRange(double x, double y, double radius) const = 0;

    virtual WeatherType getWeatherAtPoint(double x, double y) const = 0;
};

#endif // IWORLD_H

