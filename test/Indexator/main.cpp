#include <iostream>
#include <assert.h>
#include <cmath>
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

    // vitrual methods
    void destroy(){}
    std::vector<Action>* getActions(){
        return 0;
    }
    void receiveMessage(Action *){}

};

bool find(ObjectHeap* heap, Object * object)
{
    for (ObjectHeap::iterator i = heap -> begin(); i != heap -> end(); i++)
    {
        if (*i == object)
        {
            return true;
        }
    }
    return false;
}

Action::~Action(){}

int main()
{
    // Create a heap and a vector
    ObjectHeap heap;
    vector<testObject *> vec;
    Shape form(Point(0,0), SQUARE, 80);
    for (int i = 0; i < 10; i++)
    {
        // Create objects on a cross
        vec.push_back(new testObject(Point(i * 100 + 50, i * 100 + 50),
                                form));
        vec.push_back(new testObject(Point(i * 100 + 50, 1000 - i * 100 - 50),
                                form));
        heap.push(vec[i * 2]);
        heap.push(vec[i * 2 + 1]);
    }

    // Create an index
    Indexator index(1000, &heap);

    // Create an area for looking for objects
    Shape area(Point(500, 500), CIRCLE, 400);

    // Get contents
    ObjectHeap * contents = index.getAreaContents(area);

    // Middle 8 objects in area
    assert(contents -> getTypeAmount(ObjectType(-1)) == 8);
    for (int i = 6; i < 14; i++)
    {
        assert(find(contents, vec[i]));
    }

    area.setSize(300);
    delete contents;
    contents = index.getAreaContents(area);

    // Only 4 now
    assert(contents -> getTypeAmount(ObjectType(-1)) == 4);
    for (int i = 8; i < 12; i++)
    {
        assert(find(contents, vec[i]));
    }

    area.setCenter(Point(250, 750));
    delete contents;
    contents = index.getAreaContents(area);

    // 3 in the middle of left top beam of cross
    assert(contents -> getTypeAmount(ObjectType(-1)) == 3);
    for (int i = 3; i < 9; i += 2)
    {
        assert(find(contents, vec[i]));
    }
    
    // move objects a little bit so they don't chnage their cells, 
    // then reindex them
    
    for (int i = 0; i < 20; i++)
    {
        vec[i] -> setCoords(vec[i] -> getCoords() + Point (10, 10));
        index.reindexate(vec[i]);
    }

    // repeat the tests
    //
    
    area.setSize(400);
    area.setCenter(Point(500, 500));

    // Get contents
    contents = index.getAreaContents(area);

    // Middle 8 objects in area
    assert(contents -> getTypeAmount(ObjectType(-1)) == 8);
    for (int i = 6; i < 14; i++)
    {
        assert(find(contents, vec[i]));
    }

    area.setSize(2 * 100 * sqrt(2));
    delete contents;
    contents = index.getAreaContents(area);

    // This time 5: Object #6 wtih (360, 360) has right top at (400, 400)
    assert(contents -> getTypeAmount(ObjectType(-1)) == 5);
    for (int i = 8; i < 12; i++)
    {
        assert(find(contents, vec[i]));
    }
    assert(find(contents, vec[6]));

    area.setCenter(Point(250, 750));
    delete contents;
    contents = index.getAreaContents(area);

    // 3 in the middle of left top beam of cross
    assert(contents -> getTypeAmount(ObjectType(-1)) == 3);
    for (int i = 3; i < 9; i += 2)
    {
        assert(find(contents, vec[i]));
    }
    
    // Now tests with intersecting multiple grid cells
    delete contents;
    vec.clear();

    return 0;
}

