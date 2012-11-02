
#ifndef SHAPE_H
#define SHAPE_H

#include "../Point/Point.h"

/// Shape types
enum ShapeType {CIRCLE, SQUARE};

/// Intersection flags
enum IntersectionFlag {NO_INTERSECTION = 16, LEFT = 1, RIGHT = 2,
                        BOTTOM = 4, TOP = 8};

/**
  * class Shape
  * Shape are needed for objects' bounds and view areas
  */

class Shape
{
public:

    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

	/**
     *  @brief  Constructor
     *  @param  type type of the shape
     *  @param  center center of the Shape
     *  @param  size size of the Shape
     *          (edge length for polygons, diameter for circle).
     */
    Shape(Point center, int type, double size);

    /**
     *  @brief Constructor
     */
    Shape();

	/**
     *  @brief Destructor
	 */
    ~Shape();

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Set the value of center.
     * @param new_var the new value of center.
     */

    void setCenter ( Point new_var );

    /**
     * @brief Get the value of center.
     * @return the value of center.
     */

    Point getCenter ( );

    /**
     * @brief Get type of the shape.
     * @return type of the shape.
     */

    int getType();

    /**
     * @brief Set type.
     * @param type new type.
     */

    void setType(int type);

    /**
     * @brief Get size (edge length for polygons, diameter for circle).
     * @return size
     */

    double getSize();

    /**
     * @brief Set size (edge length for polygons, radius for circle).
     * @param size new size
     */

    void setSize(double size);

    /**
     * @brief Get last position of shape
     * @return coordinates of the last position
     */

    Point getLastCenter();

    //**************************************************************************
    // HIT-TEST METHODS.
    //**************************************************************************

	/**
     * @brief   Tests if a Shape includes a point.
     * @return  true or false
     * @param   point    point to test
	 */
    bool hitTest (Point point );

	/**
     * @brief   Tests if a Shape intersects with another Shape.
     * @return  true or false
     * @param   Shape   Shape to test
	 */
    bool hitTest (Shape shape );

    /**
     * @brief   Get intersections of minimal bounding boxes with another shape.
     * @param   Shape   another shape
     * @return  flags of intersections
     */
    int intersect(Shape shape);

    //**************************************************************************
    // CORNER METHODS
    //**************************************************************************

    /**
     * @brief Gets the left bottom point of the shape.
     */
    Point getLeftBottom();

    /**
     * @brief Gets the right top point of the shape.
     */
    Point getRightTop();

private:
    /// Coordinates of the center of the Shape.
    Point center;

    /// Type of shape.
    ShapeType type;

    /// Size of shape.
    double size;

    /// Left bottom point related to center.
    Point left_bottom;

    /// Right top point related to center.
    Point right_top;

    /// Last coordinates.
    Point last_center;

    //**************************************************************************
    // CORNER METHODS
    //**************************************************************************

    /**
     * @brief Computes new corner points related to center
     */

    void computeCorners();

};

#endif // SHAPE_H
