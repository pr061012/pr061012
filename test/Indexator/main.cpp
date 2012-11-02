#include <iostream>
#include <assert.h>
#include "../../model/World/Indexator/Indexator.h"

using namespace std;

class testObject : public Object
{
public:

    testObject() : Object(CREATURE)
    {
    }
    testObject(Point center, Shape shape) : Object(CREATURE)
    {
        shape.setCenter(center);
        setShape(shape);
    }
    vector<PendingAction*> getPendingActions()
    {
        vector<PendingAction*> a;
        return a;
    }
};

int main()
{
    // Create a heap and a vector
    Indexator::ObjectHeap heap;
    vector<Object *> vec;
    Shape form(Point(0,0), SQUARE, 80);
    for (int i = 0; i < 10; i++)
    {
        // Create objects on a cross
        vec.push_back(new testObject(Point(i * 100 + 50, i * 100 + 50),
                                form));
        vec.push_back(new testObject(Point(i * 100 + 50, 1000 - i * 100 - 50),
                                form));
        heap.insert(vec[i * 2]);
        heap.insert(vec[i * 2 + 1]);
    }

    // Create an index
    Indexator index(1000, &heap);

    // Create an area for looking for objects
    Shape area(Point(500, 500), CIRCLE, 300);

    // Get contents
    Indexator::ObjectHeap * contents = index.getAreaContents(area);

    //
    for (int i = 6; i < 14; i++)
    {
        assert(contents -> find(vec[i]) != contents -> end());
    }

    cout << "Hello World!" << endl;
    return 0;
}

