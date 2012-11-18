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
    testObject(Vector center, Shape shape) : Object(CREATURE)
    {
        setCoords(center);
        setShapeSize(shape.getSize());
        setShapeType(ShapeType(shape.getType()));

    }

    // vitrual methods
    void destroy(){}
    std::vector<Action>* getActions(){
        return 0;
    }
    void damage(uint a){};
    void heal(uint b){};
    void receiveMessage(Action *){}
    uint getHealthPoints() const
    {
        return 0; 
    }
    uint getMaxHealthPoints() const
    {
        return 0;
    }

};

bool find(ObjectHeap heap, Object * object)
{
    for (ObjectHeap::iterator i = heap.begin(); i != heap.end(); i++)
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
    Shape form(Vector(0,0), SQUARE, 80);
    for (int i = 0; i < 10; i++)
    {
        // Create objects on a cross
        vec.push_back(new testObject(Vector(i * 100 + 50, i * 100 + 50),
                                form));
        vec.push_back(new testObject(Vector(i * 100 + 50, 1000 - i * 100 - 50),
                                form));
        heap.push(vec[i * 2]);
        heap.push(vec[i * 2 + 1]);
    }

    // Create an index
    Indexator index(1000, &heap);

    // Create an area for looking for objects
    Shape area(Vector(500, 500), CIRCLE, 400);

    // Get contents
    ObjectHeap contents = index.getAreaContents(area);

    //*************************************************************************
    // check indexing
    //*************************************************************************
    // Middle 8 objects in area
    assert(contents.getTypeAmount(ObjectType(-1)) == 8);
    for (int i = 6; i < 14; i++)
    {
        assert(find(contents, vec[i]));
    }

    area.setSize(300);
    
    contents = index.getAreaContents(area);

    // Only 4 now
    assert(contents.getTypeAmount(ObjectType(-1)) == 4);
    for (int i = 8; i < 12; i++)
    {
        assert(find(contents, vec[i]));
    }

    area.setCenter(Vector(250, 750));
    
    contents = index.getAreaContents(area);

    // 3 in the middle of left top beam of cross
    assert(contents.getTypeAmount(ObjectType(-1)) == 3);
    for (int i = 3; i < 9; i += 2)
    {
        assert(find(contents, vec[i]));
    }

    // borders of worlds
    area.setCenter(Vector(0, 0));
    contents = index.getAreaContents(area);

    assert(contents.getAmount() == 1);
    assert(find(contents, vec[0]));
    
    //*************************************************************************
    // move objects a little bit so they don't chnage their cells, 
    // then reindex them
    //*************************************************************************
    
    for (int i = 0; i < 20; i++)
    {
        vec[i] -> setCoords(vec[i] -> getCoords() + Vector (10, 10));
        index.reindexate(vec[i]);
    }

    // repeat the tests
    //
    
    area.setSize(400);
    area.setCenter(Vector(500, 500));

    // Get contents
    
    contents = index.getAreaContents(area);

    // Middle 8 objects in area
    assert(contents.getTypeAmount(ObjectType(-1)) == 8);
    for (int i = 6; i < 14; i++)
    {
        assert(find(contents, vec[i]));
    }

    area.setSize(2 * 100 * sqrt(2));
    
    contents = index.getAreaContents(area);

    // This time 5: Object #6 wtih (360, 360) has right top at (400, 400)
    assert(contents.getTypeAmount(ObjectType(-1)) == 5);
    for (int i = 8; i < 12; i++)
    {
        assert(find(contents, vec[i]));
    }
    assert(find(contents, vec[6]));

    area.setCenter(Vector(250, 750));
    
    contents = index.getAreaContents(area);

    // 3 in the middle of left top beam of cross
    assert(contents.getTypeAmount(ObjectType(-1)) == 3);
    for (int i = 3; i < 9; i += 2)
    {
        assert(find(contents, vec[i]));
    }
    
    //*************************************************************************
    // Now tests with intersecting multiple grid cells
    //*************************************************************************
    
    for (vector<testObject*>::iterator i = vec.begin(); i != vec.end(); i++)
    {
        delete *i;
    }
    vec.clear();

    form.setSize(100);
    vec.push_back(new testObject(Vector(300, 300), form));
    Indexator index1(1000);
    index1.reindexate(vec[0]);

    area.setSize(100);
    area.setCenter(Vector(200, 200));
    contents = index1.getAreaContents(area);
    assert(contents.getTypeAmount(ObjectType(-1)) == 0);

    
    area.setCenter(Vector(220, 220));
    contents = index1.getAreaContents(area);
    assert(contents.getTypeAmount(ObjectType(-1)) == 1);
    assert(find(contents, vec[0]));
    
    
    area.setCenter(Vector(400, 400));
    contents = index1.getAreaContents(area);
    assert(contents.getTypeAmount(ObjectType(-1)) == 0);

    
    area.setCenter(Vector(380, 380));
    contents = index1.getAreaContents(area);
    assert(contents.getTypeAmount(ObjectType(-1)) == 1);
    assert(find(contents, vec[0]));

    
    area.setCenter(Vector(200, 400));
    contents = index1.getAreaContents(area);
    assert(contents.getTypeAmount(ObjectType(-1)) == 0);

    
    area.setCenter(Vector(220, 380));
    contents = index1.getAreaContents(area);
    assert(contents.getTypeAmount(ObjectType(-1)) == 1);
    assert(find(contents, vec[0]));

    
    area.setCenter(Vector(400, 200));
    contents = index1.getAreaContents(area);
    assert(contents.getTypeAmount(ObjectType(-1)) == 0);

    
    area.setCenter(Vector(380, 220));
    contents = index1.getAreaContents(area);
    assert(contents.getTypeAmount(ObjectType(-1)) == 1);
    assert(find(contents, vec[0]));

    //*************************************************************************
    // Testing moving objects
    //*************************************************************************

    area.setCenter(Vector(500, 500));
    area.setSize(600);
    vec.push_back(new testObject(Vector(700, 1000), form));
    vec.push_back(new testObject(Vector(500, 400), form));

    ObjectHeap heap1;
    heap1.push(vec[0]);
    heap1.push(vec[1]);
    heap1.push(vec[2]);

    for (int t = 0; t < 1000; t++)
    {
        
        /* #0 goes on the line y = 500
         * #1 goes on the circle (x = 700, y = 800, r = 200)
         * #2 goes on the parabola y = (500 - x)^2 / 100 + 400
         */
        vec[0] -> setCoords(Vector(t, 500));
        vec[1] -> setCoords(Vector(700 + cos(t) * 200, 700 + sin(t) * 200));
        // this also checks world for cycling :)
        vec[2] -> setCoords(Vector(t * 0.4 + 200,
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

    

    /**************************************************************************
    * Toroidal feature
    *
    *************************************************************************
    // Test bounds
    *************************************************************************
    
    vec.clear();

    form.setSize(90);

    // 0 - 3 near corners
    vec.push_back(new testObject(Vector( 50,  50), form));
    vec.push_back(new testObject(Vector( 50, 950), form));
    vec.push_back(new testObject(Vector(950, 950), form));
    vec.push_back(new testObject(Vector(950,  50), form));

    // 4 - 7 near middle of the bounds
    vec.push_back(new testObject(Vector(500,  50), form));
    vec.push_back(new testObject(Vector( 50, 500), form));
    vec.push_back(new testObject(Vector(500, 950), form));
    vec.push_back(new testObject(Vector(950, 500), form));

    // 8 - 11 intersect corners
    vec.push_back(new testObject(Vector(  0,   0), form));
    vec.push_back(new testObject(Vector(  0, 999), form));
    vec.push_back(new testObject(Vector(999, 999), form));
    vec.push_back(new testObject(Vector(999,   0), form));

    // 12 - 15 intersect bounds
    vec.push_back(new testObject(Vector(500,   0), form));
    vec.push_back(new testObject(Vector(  0, 500), form));
    vec.push_back(new testObject(Vector(500, 999), form));
    vec.push_back(new testObject(Vector(999, 500), form));
    
    ObjectHeap heap2;
    for (std::vector<testObject*>::iterator i = vec.begin();
                    i != vec.end(); i++)
    {
        heap2.push(*i);
    }
    index1.reindexate(&heap2);

    area.setSize(200);

    *************************************************************************
    // check corners
    *************************************************************************

    area.setCenter(Vector(100, 100));
    contents = index1.getAreaContents(area);
    assert(contents.getAmount() == 5);
    assert(find(contents, vec[11]) && find(contents, vec[8]));
    assert(find(contents, vec[9]) && find(contents, vec[10]));
    assert(find(contents, vec[0]));

    area.setCenter(Vector(100, 900));
    contents = index1.getAreaContents(area);
    assert(contents.getAmount() == 5);
    assert(find(contents, vec[11]) && find(contents, vec[8]));
    assert(find(contents, vec[9]) && find(contents, vec[10]));
    assert(find(contents, vec[1]));
    
    area.setCenter(Vector(900, 900));
    contents = index1.getAreaContents(area);
    assert(contents.getAmount() == 5);
    assert(find(contents, vec[11]) && find(contents, vec[8]));
    assert(find(contents, vec[9]) && find(contents, vec[10]));
    assert(find(contents, vec[2]));

    area.setCenter(Vector(900, 100));
    contents = index1.getAreaContents(area);
    assert(contents.getAmount() == 5);
    assert(find(contents, vec[11]) && find(contents, vec[8]));
    assert(find(contents, vec[9]) && find(contents, vec[10]));
    assert(find(contents, vec[3]));

    */

    return 0;
}

