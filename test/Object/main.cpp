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
    //**************************************************************************
    // TEST CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /// Create helper var.
    ObjectType type = RESOURCE;

    /// Test create Object.
    AnyObject object(type);

    /// Test create ptr for object.
    AnyObject * object_2 = new AnyObject(type);
    assert(object_2 != 0);

    /// Test delete object
    delete object_2;

    //**************************************************************************
    // TEST ACCESSORS.
    //**************************************************************************

    /// Test Health state.
    object.setHealth(100);
    assert(object.getHealth() == 100);

    /// Test MaxHealth state.
    object.setMaxHealth(200);
    assert(object.getMaxHealth() == 200);

    /// Test Angle state.
    object.setAngle(20);
    assert(object.getAngle() == 20);

    /// Test Destroyed state .
    object.setDestroyed(true);
    assert(object.getDestroyed() == true);
    object.setDestroyed(false);

    /// Test Type state.
    assert(object.getType() == RESOURCE);

    /// Test Immortality state.
    object.setImmortality(true);
    assert(object.getImmortality() == true);
    object.setImmortality(false);

    //**************************************************************************
    // TEST OBJECT'S LIFE.
    //**************************************************************************

    /// Set some states.
    object.setHealth(100);
    object.setMaxHealth(150);

    return 0;
}
