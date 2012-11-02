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
    row_size = ceil(size/MAX_CELL_SIZE);
    cell_size = size / row_size;
    cells = new ObjectHeap*[row_size];

    for (int i = 0; i< row_size; i++)
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

}

//******************************************************************************
// GETTING OBJECTS.
//******************************************************************************

Indexator::ObjectHeap * Indexator::getAreaContents(Shape area)
{
    int * cells_area = getCellsArea(area);
    ObjectHeap * result = new ObjectHeap();

    for (int x = cells_area[0]; x <= cells_area[2]; x++)
    {
        for (int y = cells_area[1]; y <= cells_area[3]; y++)
        {
            for (ObjectHeap::iterator i = cells[x][y].begin();
                 i != cells[x][y].end(); i++)
            {
                if (area.hitTest((*i) -> getShape()))
                {
                    result -> insert(*i);
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
    int j,k;

    int * area = getCellsArea(object -> getShape());

    // Check if an object exists in our index
    Index::iterator i = index.find(object); 
    if (i == index.end())
    {
        // Add the cells coordinates lies in
        index[object] = new int[4];
        for (j = 0; j < 4; j++)
        {
            index[object][j] = area[j];
        }

        // Add object to cells
        for (j = area[0]; j <= area[2]; j++)
        {
            for (k = area[1]; k <= area[3]; k++)
            {
                cells[j][k].insert(object);
            }
        }
        return;
    }

    // Check if an object moved to another cells
    int * &old_area = index[object];
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
        return;
    }

    // Change cells
    int minx = min(area[0], old_area[0]);
    int maxx = max(area[2], old_area[2]);
    int miny = min(area[1], old_area[1]);
    int maxy = max(area[3], old_area[3]);

    for (int x = minx; x < maxx; x++)
    {
        for(int y = miny; y < maxy; y++)
        {
            // delete object from cells tha don't contain it
            if ((x < area[0] || x > area[2] ||
                 y < area[1] || y > area[3]) &&
                (x >= old_area[0] && x <= old_area[2] &&
                 y >= old_area[1] && y <= old_area[3]))
            {
                cells[x][y].erase(object);
            }
            // push object in cells that did not contain it
            else if ((x >= area[0] && x <= area[2] &&
                      y >= area[1] && y <= area[3]) &&
                     (x < old_area[0] || x > old_area[2] ||
                      y < old_area[1] || y > old_area[3]))
            {
                cells[x][y].insert(object);
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

int * Indexator::getCellsArea(Shape shape)
{
    // Get object boundaries
    Point rt = shape.getRightTop();
    Point lb = shape.getLeftBottom();

    // Compute the cells it intersects
    int * area = new int[4];
    area[0] = ceil(lb.getX() / cell_size);
    area[1] = ceil(lb.getY() / cell_size);
    area[2] = ceil(rt.getX() / cell_size);
    area[3] = ceil(rt.getY() / cell_size);

    return area;
}
