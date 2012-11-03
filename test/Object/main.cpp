/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <assert.h>

#include "../../model/World/Object/Object.h"

class AnyObject : public Object
{
public:
    AnyObject(ObjectType type) : Object(type) {}
    ~AnyObject() {}

    void destroy()
    {
        this -> setDestroyed(true);
    }

    std::vector <Action> * getActions()
    {
        return &this -> actions;
    }

    void receiveMessage(Action * action) {}
};

int main()
{
    ObjectType type = RESOURCE;
    AnyObject object(type);

    //**************************************************************************
    // TEST ACCESSORS.
    //**************************************************************************

    // Test Health state.
    object.setHealth(100);
    assert(object.getHealth() == 100);

    // Test MaxHealth state.
    object.setMaxHealth(200);
    assert(object.getMaxHealth() == 200);

    // Test Angle state.
    object.setAngle(20);
    assert(object.getAngle() == 20);

    // Test Destroyed state.
    object.setDestroyed(true);
    assert(object.getDestroyed() == true);
    object.setDestroyed(false);

    // Test Type state.
    assert(object.getType() == RESOURCE);

    // Test Immortality state.
    object.setImmortality(true);
    assert(object.getImmortality() == true);
    object.setImmortality(false);

    //**************************************************************************
    // TEST OBJECT'S LIFE.
    //**************************************************************************

    // Set some states.
    object.setHealth(100);
    object.setMaxHealth(150);

    // Test increaseHealth() method.
    object.increaseHealth(10);
    assert(object.getHealth() == 110);

    object.increaseHealth(50);
    assert(object.getHealth() == object.getMaxHealth());

    // Test decreaseHealth() method.
    object.decreaseHealth(10);
    assert(object.getHealth() == 140);

    object.decreaseHealth(150);
    assert(object.getHealth() == 0);

    return 0;
}
