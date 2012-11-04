#include "Indexator.h"
#include <cmath>

const double Indexator::MAX_CELL_SIZE = 100;

//******************************************************************************
// CONSTRUCTORS/DESTRUCTOR.
//******************************************************************************

Indexator::Indexator()
{
}

Indexator::Indexator(double size, ObjectHeap *list)
{
    world_size = size;
    row_size = ceil(size/MAX_CELL_SIZE);
    cell_size = size / row_size;
    cells = new ObjectHeap*[row_size];

    for (unsigned int i = 0; i< row_size; i++)
    {
        cells[i] = new ObjectHeap[row_size];
    }

    if (list)
    {
        reindexate(list);
    }
}

Indexator::~Indexator()
{
    for (unsigned int i = 0; i < row_size; i++)
    {
        delete[] cells[i];
    }
    delete cells;
    index.clear();
}

//******************************************************************************
// GETTING OBJECTS.
//******************************************************************************

ObjectHeap * Indexator::getAreaContents(Shape area)
{
    unsigned int * cells_area = getCellsArea(area);
    ObjectHeap * result = new ObjectHeap();

    for (unsigned int x = cells_area[0]; x <= cells_area[2]; x++)
    {
        for (unsigned int y = cells_area[1]; y <= cells_area[3]; y++)
        {
            for (ObjectHeap::iterator i = cells[x % row_size][y % row_size].begin();
                 i != cells[x % row_size][y % row_size].end(); i++)
            {
                if (area.hitTest((*i) -> getShape()))
                {
                    result -> push(*i);
                }
            }
        }
    }

    return result;
}

//******************************************************************************
// REINDEXATE.
//******************************************************************************

// Reindexate multiple objects
void Indexator::reindexate(ObjectHeap * objects)
{
    ObjectHeap::iterator i;

    for (i = objects -> begin(); i != objects -> end(); i++)
    {
        reindexate(*i);
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
    unsigned int j,k;

    unsigned int * area = getCellsArea(object -> getShape());

    // Check if an object exists in our index
    Index::iterator i = index.find(object); 
    if (i == index.end())
    {
        // Add the cells coordinates lies in
        index[object] = area;

        // Add object to cells
        for (j = area[0]; j <= area[2]; j++)
        {
            for (k = area[1]; k <= area[3]; k++)
            {
                cells[j % row_size][k % row_size].push(object);
            }
        }
        return;
    }

    // Check if an object moved to another cells
    unsigned int * &old_area = index[object];
    k = 0;
    for (j = 0; j < 4; j++)
    {
        if (area[j] != old_area[j])
        {
            k = 1;
            break;
        }
    }

    // If object did not move, don't do anything.
    if (!k)
    {
        delete area;
        return;
    }

    // Change cells
    unsigned int minx = min(area[0], old_area[0]);
    unsigned int maxx = max(area[2], old_area[2]);
    unsigned int miny = min(area[1], old_area[1]);
    unsigned int maxy = max(area[3], old_area[3]);

    for (unsigned int x = minx; x <= maxx; x++)
    {
        for(unsigned int y = miny; y <= maxy; y++)
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
    delete old_area;
    old_area = area;
}

//******************************************************************************
// UTILITIES
//******************************************************************************

inline unsigned int Indexator::min(unsigned int a, unsigned int b)
{
    if (a < b)
        return a;
    else
        return b;
}

inline unsigned int Indexator::max(unsigned int a, unsigned int b)
{
    if (a > b)
        return a;
    else
        return b;
}

// Get cells wich given object hits

unsigned int * Indexator::getCellsArea(Shape shape)
{
    // Get object boundaries
    Point rt = shape.getRightTop();
    Point lb = shape.getLeftBottom();

    // Compute the cells it intersects
    unsigned int * area = new unsigned int[4];
    area[0] = getRow(lb.getX());
    area[1] = getRow(lb.getY());
    area[2] = getRow(rt.getX());
    area[3] = getRow(rt.getY());
    if (lb.getX() < 0 && rt.getX() >= 0)
    {
        area[2] += row_size;
    }
    else if (lb.getY() < 0 && rt.getY() >= 0)
    {
        area[3] += row_size;
    }

    return area;
}

// Gets the row index for given coordinate.
// It is assumed that world controls that 0 <= coordinate < world_size
// and size < world_size for any shape.
// Row's index >= 0
unsigned int Indexator::getRow(double coordinate)
{
    return (unsigned int)(floor((coordinate + world_size) / cell_size)) 
                            % row_size;
}
