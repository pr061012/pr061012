/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <assert.h>
#include <iostream>

#include "../../model/World/ObjectHeap/ObjectHeap.h"

class AnyObject : public Object
{
private:
    static int count;
    int id;

public:
    AnyObject():Object(RESOURCE)
    {
        id = count;
        count++;
    }

    ~AnyObject();
    void print()
    {
        std::cout << id << std::endl;
    }

    std::vector <Action *> getActions()
    {
        std::vector<Action*> ret;
        return ret;
    }

    void receiveMessage(Action * action)
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
        AnyObject* var = new AnyObject();
        heap -> push(dynamic_cast<Object*>(var));
    }
    for (iter = heap -> begin(RESOURCE); iter != heap -> end(RESOURCE); iter++)
    {
        (dynamic_cast<AnyObject*>(*iter))->print();
    }
}
