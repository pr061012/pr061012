#include <iostream>
#include "../../model/World/Indexator/Indexator.h"

using namespace std;

class testObject : public Object
{
public:
    static int test_id;

    testObject() : Object(CREATURE)
    {
        setShape(Shape(Point(test_id, test_id), CIRCLE, 2));
        test_id++;
    }
    vector<PendingAction*> getPendingActions()
    {
        vector<PendingAction*> a;
        return a;
    }
};

int testObject::test_id = 0;

int main()
{
//**************************************************************************
// FOR TEST USE ONLY!!!
typedef std::set<Object*> ObjectHeap;
//**************************************************************************
    cout << "Hello World!" << endl;
    ObjectHeap a;
    for (int i = 0; i < 10; i++)
    {
        a.insert(new testObject());
    }
    Indexator index(1000, &a);
    return 0;
}

