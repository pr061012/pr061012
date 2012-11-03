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

    // vitrual methods
    void destroy(){}
    std::vector<Action>* getActions(){
        return 0;
    }
    void receiveMessage(Action *){}

    // methos for testing
    const Point& getCenter() const
    {
        return shape.getCenter();
    }

    void setCenter(Point center)
    {
        shape.setCenter(center);
    }
};

Action::~Action(){}

int main()
{
    // Create a heap and a vector
    Indexator::ObjectHeap heap;
    vector<testObject *> vec;
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
    Shape area(Point(500, 500), CIRCLE, 400);

    // Get contents
    Indexator::ObjectHeap * contents = index.getAreaContents(area);

    // Middle 8 objects in area
    assert(contents -> size() == 8);
    for (int i = 6; i < 14; i++)
    {
        assert(contents -> find(vec[i]) != contents -> end());
    }

    area.setSize(300);
    delete contents;
    contents = index.getAreaContents(area);

    // Only 4 now
    assert(contents -> size() == 4);
    for (int i = 8; i < 12; i++)
    {
        assert(contents -> find(vec[i]) != contents -> end());
    }

    area.setCenter(Point(250, 750));
    delete contents;
    contents = index.getAreaContents(area);

    // 3 in the middle of left top beam of cross
    assert(contents -> size() == 3);
    for (int i = 3; i < 9; i += 2)
    {
        assert(contents -> find(vec[i]) != contents -> end());
    }
    
    // move objects a little bit so they don't chnage their cells, 
    // then reindex them
    
    for (int i = 0; i < 20; i++)
    {
        vec[i] -> setCenter(vec[i] -> getCenter() + Point (10, 10));
        index.reindexate(vec[i]);
    }

    // repeat the tests

    delete contents;
    area.setCenter(Point(500, 500));
    area.setSize(400);
    contents = index.getAreaContents(area);

    // Middle 8 objects in area
    assert(contents -> size() == 8);
    for (int i = 6; i < 14; i++)
    {
        assert(contents -> find(vec[i]) != contents -> end());
    }

    area.setSize(300);
    delete contents;
    contents = index.getAreaContents(area);

    // Only 4 now
    assert(contents -> size() == 4);
    for (int i = 8; i < 12; i++)
    {
        assert(contents -> find(vec[i]) != contents -> end());
    }

    area.setCenter(Point(250, 750));
    delete contents;
    contents = index.getAreaContents(area);

    // 3 in the middle of left top beam of cross
    assert(contents -> size() == 3);
    for (int i = 3; i < 9; i += 2)
    {
        assert(contents -> find(vec[i]) != contents -> end());
    }
    
    return 0;
}

