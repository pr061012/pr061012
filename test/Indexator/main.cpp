#include <iostream>
#include "../../model/World/Indexator/Indexator.h"

using namespace std;

class testObject : public Object
{
public:
    testObject() : Object(CREATURE)
    {
    }
    vector<PendingAction*> getPendingActions()
    {
        vector<PendingAction*> a;
        return a;
    }
};

int main()
{
//**************************************************************************
// FOR TEST USE ONLY!!!
typedef std::vector<Object*> ObjectHeap;
//**************************************************************************
    cout << "Hello World!" << endl;
    ObjectHeap a;
    a.push_back(new testObject());
    Indexator index(1000, &a);
    return 0;
}

