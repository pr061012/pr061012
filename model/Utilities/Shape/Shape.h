
#ifndef SHAPE_H
#define SHAPE_H

#include "../Point/Point.h"
#include "../../BasicTypes.h"

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

    const Point& getCenter( ) const;

    /**
     * @brief Get type of the shape.
     * @return type of the shape.
     */

    int getType() const;

    /**
     * @brief Set type.
     * @param type new type.
     */

    void setType(int type);

    /**
     * @brief Get size (edge length for polygons, diameter for circle).
     * @return size
     */

    double getSize() const;

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
    bool hitTest (const Point& point) const;

	/**
     * @brief   Tests if a Shape intersects with another Shape.
     * @return  true or false
     * @param   shape   Shape to test
	 */
    bool hitTest (const Shape& shape) const;

    /**
     * @brief   Get intersections of minimal bounding boxes with another shape.
     * @param   shape   another shape
     * @return  flags of intersections
     */
    int intersect(const Shape& shape);

    //**************************************************************************
    // CORNER METHODS
    //**************************************************************************

    /**
     * @brief Gets the left bottom point of the shape.
     */
    Point getLeftBottom() const;

    /**
     * @brief Gets the right top point of the shape.
     */
    Point getRightTop() const;

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

    /**
     * @brief Checks square-circle hit test
     */

    bool squareCircleHitTest(const Shape& square, const Shape& circle) const;

    /**
     *    @brief Checks if a segment overlaps a circle
     */
    bool circleOverlapsSegment(Shape shape, Point pt1, Point pt2) const;

};

#endif // SHAPE_H
