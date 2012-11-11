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
    void damage(uint a){};
    void heal(uint b){};
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

    //*************************************************************************
    // check indexing
    //*************************************************************************
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
    
    //*************************************************************************
    // move objects a little bit so they don't chnage their cells, 
    // then reindex them
    //*************************************************************************
    
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
    delete contents;
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
    
    //*************************************************************************
    // Now tests with intersecting multiple grid cells
    //*************************************************************************
    delete contents;
    for (vector<testObject*>::iterator i = vec.begin(); i != vec.end(); i++)
    {
        delete *i;
    }
    vec.clear();

    form.setSize(100);
    vec.push_back(new testObject(Point(300, 300), form));
    Indexator index1(1000);
    index1.reindexate(vec[0]);

    area.setSize(100);
    area.setCenter(Point(200, 200));
    contents = index1.getAreaContents(area);
    assert(contents -> getTypeAmount(ObjectType(-1)) == 0);

    delete contents;
    area.setCenter(Point(220, 220));
    contents = index1.getAreaContents(area);
    assert(contents -> getTypeAmount(ObjectType(-1)) == 1);
    assert(find(contents, vec[0]));
    
    delete contents;
    area.setCenter(Point(400, 400));
    contents = index1.getAreaContents(area);
    assert(contents -> getTypeAmount(ObjectType(-1)) == 0);

    delete contents;
    area.setCenter(Point(380, 380));
    contents = index1.getAreaContents(area);
    assert(contents -> getTypeAmount(ObjectType(-1)) == 1);
    assert(find(contents, vec[0]));

    delete contents;
    area.setCenter(Point(200, 400));
    contents = index1.getAreaContents(area);
    assert(contents -> getTypeAmount(ObjectType(-1)) == 0);

    delete contents;
    area.setCenter(Point(220, 380));
    contents = index1.getAreaContents(area);
    assert(contents -> getTypeAmount(ObjectType(-1)) == 1);
    assert(find(contents, vec[0]));

    delete contents;
    area.setCenter(Point(400, 200));
    contents = index1.getAreaContents(area);
    assert(contents -> getTypeAmount(ObjectType(-1)) == 0);

    delete contents;
    area.setCenter(Point(380, 220));
    contents = index1.getAreaContents(area);
    assert(contents -> getTypeAmount(ObjectType(-1)) == 1);
    assert(find(contents, vec[0]));

    //*************************************************************************
    // Testing moving objects
    //*************************************************************************

    area.setCenter(Point(500, 500));
    area.setSize(600);
    vec.push_back(new testObject(Point(700, 1000), form));
    vec.push_back(new testObject(Point(500, 400), form));

    ObjectHeap heap1;
    heap1.push(vec[0]);
    heap1.push(vec[1]);
    heap1.push(vec[2]);

    for (int t = 0; t < 1000; t++)
    {
        delete contents;
        /* #0 goes on the line y = 500
         * #1 goes on the circle (x = 700, y = 800, r = 200)
         * #2 goes on the parabola y = (500 - x)^2 / 100 + 400
         */
        vec[0] -> setCoords(Point(t, 500));
        vec[1] -> setCoords(Point(700 + cos(t) * 200, 700 + sin(t) * 200));
        // this also checks world for cycling :)
        vec[2] -> setCoords(Point(t * 0.4 + 200,
                                 -pow((t * 0.4 + 200) - 500, 2) / 100 + 400));
        
        index1.reindexate(&heap1);
        contents = index1.getAreaContents(area);
        unsigned int k = 0;
        
        for (int j = 0; j < 3; j++)
        {
            if (area.hitTest(vec[j] -> getShape()))
            {
                k++;
                assert(find(contents, vec[j]));
            }
        }
    }

    for (ObjectHeap::iterator i = heap1.begin(); i != heap1.end(); i++)
    {
        delete *i;
    }

    delete contents;

    //*************************************************************************
    // Test bounds
    //*************************************************************************
    
    vec.clear();

    form.setSize(90);

    // 0 - 3 near corners
    vec.push_back(new testObject(Point( 50,  50), form));
    vec.push_back(new testObject(Point( 50, 950), form));
    vec.push_back(new testObject(Point(950, 950), form));
    vec.push_back(new testObject(Point(950,  50), form));

    // 4 - 7 near middle of the bounds
    vec.push_back(new testObject(Point(500,  50), form));
    vec.push_back(new testObject(Point( 50, 500), form));
    vec.push_back(new testObject(Point(500, 950), form));
    vec.push_back(new testObject(Point(950, 500), form));

    // 8 - 11 intersect corners
    vec.push_back(new testObject(Point(  0,   0), form));
    vec.push_back(new testObject(Point(  0, 999), form));
    vec.push_back(new testObject(Point(999, 999), form));
    vec.push_back(new testObject(Point(999,   0), form));

    // 12 - 15 intersect bounds
    vec.push_back(new testObject(Point(500,   0), form));
    vec.push_back(new testObject(Point(  0, 500), form));
    vec.push_back(new testObject(Point(500, 999), form));
    vec.push_back(new testObject(Point(999, 500), form));
    
    ObjectHeap heap2;
    for (std::vector<testObject*>::iterator i = vec.begin();
                    i != vec.end(); i++)
    {
        heap2.push(*i);
    }
    index1.reindexate(&heap2);

    area.setSize(200);

    //*************************************************************************
    // check corners
    //*************************************************************************

    area.setCenter(Point(100, 100));
    contents = index1.getAreaContents(area);
    assert(contents -> getAmount() == 5);
    assert(find(contents, vec[11]) && find(contents, vec[8]));
    assert(find(contents, vec[9]) && find(contents, vec[10]));
    assert(find(contents, vec[0]));

    area.setCenter(Point(100, 900));
    contents = index1.getAreaContents(area);
    assert(contents -> getAmount() == 5);
    assert(find(contents, vec[11]) && find(contents, vec[8]));
    assert(find(contents, vec[9]) && find(contents, vec[10]));
    assert(find(contents, vec[1]));
    
    area.setCenter(Point(900, 900));
    contents = index1.getAreaContents(area);
    assert(contents -> getAmount() == 5);
    assert(find(contents, vec[11]) && find(contents, vec[8]));
    assert(find(contents, vec[9]) && find(contents, vec[10]));
    assert(find(contents, vec[2]));

    area.setCenter(Point(900, 100));
    contents = index1.getAreaContents(area);
    assert(contents -> getAmount() == 5);
    assert(find(contents, vec[11]) && find(contents, vec[8]));
    assert(find(contents, vec[9]) && find(contents, vec[10]));
    assert(find(contents, vec[3]));

    return 0;
}

