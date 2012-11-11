/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <assert.h>
#include <iostream>

#include "../../model/World/ObjectHeap/ObjectHeap.h"
#include "../../model/World/Object/Object.h"
#include "../../model/Utilities/Shape/Shape.h"

class AnyObject : public Object
{
private:
    static int count;
    int id;

public:
    AnyObject(ObjectType type):Object(type)
    {
        if ( type == RESOURCE )
        {
            id = count;
        }
        else
        {
            id = -count;
        }
        count++;
    }

    AnyObject():Object(BUILDING)
    {
        id = -count;
        count++;
    }

    ~AnyObject(){};

    void print()
    {
        std::cout << id << std::endl;
    }

    virtual std::vector <Action>* getActions()
    {
        std::vector<Action> *ret = 0;
        return ret;
    }

    virtual void damage(uint delta)
    {

    }

    virtual void heal(uint delta)
    {

    }
};

int AnyObject::count=0;

int main()
{
    //**************************************************************************
    // TEST CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    ///Create ObjectHeap
    ObjectHeap* heap = new ObjectHeap();
    ObjectHeap::iterator iter;

    for (int i = 0; i<5; i++)
    {
        AnyObject* var = new AnyObject(RESOURCE);
        heap -> push(var);
    }

    AnyObject* any = new AnyObject();

    for (int i = 0; i<5; i++)
    {
        AnyObject* var = new AnyObject(BUILDING);
        heap -> push(var);
    }

    for (iter = heap -> begin(RESOURCE); iter != heap -> end(RESOURCE); iter++)
    {
        (dynamic_cast<AnyObject*>(*iter))->print();
    }

    for (iter = heap -> begin(); iter != heap -> end(); iter++)
    {
        (dynamic_cast<AnyObject*>(*iter))->print();
    }

    (dynamic_cast<AnyObject*>(*(heap -> find(any)))) -> print();

}
