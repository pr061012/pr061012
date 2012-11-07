#ifndef IWORLD_H
#define IWORLD_H

#include "../BasicTypes.h"
#include "../../view/ViewObject.h"
#include "Action/Action.h"
#include "../God/God.h"

class IWorld
{
public:

    //******************************************************************************
    // WORLD <-> GOD METHODS.
    //******************************************************************************

    // TODO: Ask my fellow team members if we are going to
    //       have multiple gods support.
    virtual void addGodAction(/*IGod* god, */Action* action) = 0;

    //******************************************************************************
    // WORLD <-> VIEW METHODS.
    //******************************************************************************

    virtual std::vector <ViewObject*> getViewObjectsInRange(double x, double y, double radius) = 0;

    virtual WeatherType getWeatherAtPoint(double x, double y) = 0;
};

#endif // IWORLD_H

