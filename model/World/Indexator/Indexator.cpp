#include "Indexator.h"
#include <cmath>

const double Indexator::MAX_CELL_SIZE = 25;
const double Indexator::MIN_CELL_SIZE = 10;

//******************************************************************************
// CONSTRUCTORS/DESTRUCTOR.
//******************************************************************************

Indexator::Indexator(): 
    world_size(0),
    row_size(0),
    cell_size(0), 
    dx(0),
    dy(0),
    world_shape(Shape())
{
}

Indexator::Indexator(double size, ObjectHeap* list, Vector left_bottom, 
                        double cell_size) :
    world_size(size), 
    row_size(ceil(size / cell_size)),
    cell_size(size / row_size),
    dx(left_bottom.getX()),
    dy(left_bottom.getY()),
    world_shape(Shape(Vector(size/2, size/2), SQUARE, size)),

    // say that our cells are not initizlized
    cells(0)
{
    // If we have objects, then indexate them. 
    if (list)
    {
        reindexate(list);
    }
    // Just initialize cells for further operations.
    else
    {
        init();
    }
}

Indexator::~Indexator()
{
    destroy();
}

//******************************************************************************
// GETTING OBJECTS.
//******************************************************************************

// gets objects within given area
ObjectHeap Indexator::getAreaContents(Shape area, Object * viewer)
{
    // Get cells which our area covers
    uint * cells_area = getCellsArea(area);

    /**
     *  Toroidal feature
    // Create more areas to check collisions with objects intersecting 
    // bounds of the world
    Shape areas[4];
    areas[0] = area;
    Vector center = area.getCenter();
    
    // Get the left bottom shape
    if (center.getX() > world_size/2)
    {
        if (center.getY() > world_size / 2)
        {
            areas[0].setCenter(center - Vector(world_size, world_size));
        }
        else
        {
            areas[0].setCenter(center - Vector(world_size, 0)); 
        }
    }
    else
    {
        if (center.getY() > world_size / 2)
        {
            areas[0].setCenter(center - Vector(0, world_size));
        }
    }
    
    // Creat all other shapes
    areas[1] = areas[0];
    areas[1].setCenter(areas[0].getCenter() + Vector(0, world_size));
    areas[2] = areas[1];
    areas[2].setCenter(areas[1].getCenter() + Vector(world_size, 0));
    areas[3] = areas[2];
    areas[3].setCenter(areas[2].getCenter() + Vector(0, -world_size));

    */

    ObjectHeap result;

    // Search for objects in cells
    for (uint x = cells_area[0]; x <= cells_area[2]; x++)
    {
        for (uint y = cells_area[1]; y <= cells_area[3]; y++)
        {
            for (ObjectHeap::iterator i = cells[x % row_size][y % row_size].begin();
                 i != cells[x % row_size][y % row_size].end(); i++)
            {
            //*****************************************************************
            /* Toroidal feature
                // check if an object hits any area
                for (int j = 0; j < 4; j++)
                {
                    if (areas[j].hitTest((*i) -> getShape()))
                    {
                        result -> push(*i);
                        break;
                    }
                }
            */
            //*****************************************************************

                if (area.hitTest((*i) -> getShape()) && (!viewer ||
                    (*i) -> getObjectID() != viewer -> getObjectID()))
                {
                    result.push(*i);
                }
            }
        }
    }
    
    delete[] cells_area;
    return result;
}

//******************************************************************************
// REINDEXATE.
//******************************************************************************

// Reindexate multiple objects
void Indexator::reindexate(ObjectHeap * objects)
{
    // Recreate index
    destroy();
    init();
    
    // add objects
    ObjectHeap::iterator i;

    for (i = objects -> begin(); i != objects -> end(); i++)
    {
        addObject(*i);
    }
}

/* First check if we have the object in index
 * If we dont have it, just add it to the index and store
 * cells that it belongs to in index
 * Else check if object moved far enough to change the intersecting cells
 * If it did, reindex it
 */
void Indexator::reindexate(Object * object)
{
    Shape object_shape = object -> getShape();

    // Check if an object exists in our index
    Index::iterator i = index.find(object); 
    if (i == index.end())
    {
        addObject(object);
        return;
    }

    uint * area = getCellsArea(object_shape);

    // Check if an object moved to another cells
    uint * &old_area = index[object];
    bool same_area = true;
    for (uint j = 0; j < 4; j++)
    {
        if (area[j] != old_area[j])
        {
            same_area = false;
            break;
        }
    }

    // If object did not move, don't do anything.
    if (same_area)
    {
        delete[] area;
        return;
    }

    // Change cells
    uint minx = min(area[0], old_area[0]);
    uint maxx = max(area[2], old_area[2]);
    uint miny = min(area[1], old_area[1]);
    uint maxy = max(area[3], old_area[3]);

    for (uint x = minx; x <= maxx; x++)
    {
        for(uint y = miny; y <= maxy; y++)
        {
            // delete object from cells tha don't contain it
            if ((x < area[0] || x > area[2] ||
                        y < area[1] || y > area[3]) &&
                    (x >= old_area[0] && x <= old_area[2] &&
                     y >= old_area[1] && y <= old_area[3]))
            {
                cells[x % row_size][y % row_size].remove(object);
            }
            // push object in cells that did not contain it
            else if ((x >= area[0] && x <= area[2] &&
                        y >= area[1] && y <= area[3]) &&
                    (x < old_area[0] || x > old_area[2] ||
                     y < old_area[1] || y > old_area[3]))
            {
                cells[x % row_size][y % row_size].push(object);
            }
        }
    }

    // save new cells
    delete[] old_area;
    old_area = area;
}

// adds object to index
void Indexator::addObject(Object* object)
{
    Shape object_shape = object -> getShape();
    uint * area = getCellsArea(object_shape);

    // Add the cells coordinates lies in
    index[object] = area;

    // Add object to cells
    for (uint j = area[0]; j <= area[2]; j++)
    {
        for (uint k = area[1]; k <= area[3]; k++)
        {
            cells[j % row_size][k % row_size].push(object);
        }
    }
}

void Indexator::removeObject(Object* object)
{
    Index::iterator i = index.find(object);
    if (i != index.end())
    {
        for (uint x = i -> second[0]; x <= i -> second[2]; x++)
        {
            for (uint y = i -> second[1]; y <= i -> second[3]; y++)
            {
                cells[x % row_size][y % row_size].remove(object);
            }
        }
    }
}

//******************************************************************************
// UTILITIES
//******************************************************************************

inline int Indexator::min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

inline int Indexator::max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

// Get cells wich given object hits

uint * Indexator::getCellsArea(Shape& shape)
{
    // Get object boundaries
    Vector rt = shape.getRightTop();
    Vector lb = shape.getLeftBottom();

    // Compute the cells it intersects
    uint * area = new uint[4];
    area[0] = getRow(lb.getX() - dx);
    area[1] = getRow(lb.getY() - dy);
    area[2] = getRow(rt.getX() - dx);
    area[3] = getRow(rt.getY() - dy);
    
    //*************************************************************************
    /** Toroidal feature
     *
    // Move the shape to the corresponding cells
    if (lb.getX() < 0)
    {
        area[2] += row_size;
        shape.setCenter(shape.getCenter() + Vector(row_size, 0));
    } 
    else if (rt.getX() >= world_size) 
    {
        area[2] += row_size;
    }

    if (lb.getY() < 0)
    {
        area[3] += row_size;
        shape.setCenter(shape.getCenter() + Vector(0, row_size));
    }
    else if (rt.getY() >= world_size) 
    {
        area[3] += row_size;
    }
    */
    //*************************************************************************

    return area;
}

// Gets the row index for given coordinate.
// It is assumed that world controls that 0 <= coordinate < world_size
// and size < world_size for any shape.
// Row's index >= 0
int Indexator::getRow(double coordinate)
{
    return max(0, min(coordinate / cell_size, row_size - 1));
}

// Destroys index and cells
void Indexator::destroy()
{
    // destroy if cells are inited
    if (cells)
    {
        // Delete all object heaps
        for (uint i = 0; i < row_size; i++)
        {
            delete[] cells[i];
        }
        delete[] cells;
    }

    // Delete all cell areas.
    for (Index::iterator i = index.begin(); i != index.end(); i++)
    {
        delete[] i -> second;
    }
    index.clear();
}

// Index initializer
void Indexator::init()
{
    // create cells
    cells = new ObjectHeap*[row_size];

    for (uint i = 0; i< row_size; i++)
    {
        cells[i] = new ObjectHeap[row_size];
    }
}
