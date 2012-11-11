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

    std::vector <Action> * getActions()
    {
        return &this -> actions;
    }

    void damage(uint delta){}

    void heal(uint delta){}
};

int main()
{
    ObjectType type = RESOURCE;
    AnyObject object(type);

    //**************************************************************************
    // TEST ACCESSORS.
    //**************************************************************************

    // Test Angle state.
    object.setAngle(20);
    assert(object.getAngle() == 20);

    // Test Destroyed state.
    object.markAsDestroyed();
    assert(object.isDestroyed() == true);

    // Test Type state.
    assert(object.getType() == RESOURCE);

    // Test Immortality state.
    object.makeImmortal();
    assert(object.isImmortal() == true);
    object.makeMortal();

    return 0;
}
