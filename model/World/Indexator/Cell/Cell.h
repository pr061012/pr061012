/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef CELL_H
#define CELL_H

#include "../../../Utilities/Shape/Shape.h"
#include "../../ObjectHeap/ObjectHeap.h"

/**
 *  @class Cell
 *  @brief A construction unit of Indexator's grid
 */
class Cell
{

public:

    //**************************************************************************
    // CONSTRUCTORS / DESTRUCTORS
    //**************************************************************************

    /**
     *  @brief Constructor
     */

    Cell();

    /**
     *  @brief Destructor
     */

    ~Cell();

    /**
     *  @brief Creates a cell within given area
     */

    Cell(Shape area);

    //**************************************************************************
    // ACCESSORS METHODS
    //**************************************************************************

    /**
     *  @brief  Gets cell area
     *  @return cell area
     */

    Shape getArea();

    /**
     *  @brief  Sets cell area
     *  @param  area new cell area
     */

    void setArea(Shape area);

    /**
     *  @brief  Gets cell neighbours
     *  @return cell neighbours
     */

    Cell ** getNeighbours();

    /**
     *  @brief  Sets cell neighbours
     *  @param  neighbours new cell neighbours (four)
     */

    void setNeighbours(const Cell ** neighbours);

    //**************************************************************************
    // OTHER
    //**************************************************************************

    /**
     *  @brief  Check if an object belongs to this cell
     *  @param  object  an object to check
     */

    void checkObject(Object * object);

    /**
     *  @brief  Make a step
     */

    void step();

private:

    /// An area of the cell
    Shape area;

    /// Cell neighbours
    Cell * neighbours[4];

    /// A list of objects that lie within cell area
    ObjectHeap objects;
};

#endif // CELL_H
