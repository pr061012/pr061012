
#ifndef SHAPE_H
#define SHAPE_H

#include "../Vector/Vector.h"
#include "../../../common/BasicTypes.h"

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
    Shape(Vector center, int type, double size);

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

    void setCenter ( Vector new_var );

    /**
     * @brief Get the value of center.
     * @return the value of center.
     */

    const Vector& getCenter( ) const;

    /**
     * @brief Get type of the shape.
     * @return type of the shape.
     */
    ShapeType getType() const;

    /**
     * @brief  Gets type's name.
     * @return type of the shape
     */
    std::string getTypeName() const;

    /**
     * @brief Set type.
     * @param type new type.
     */

    void setType(ShapeType type);

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

    Vector getLastCenter();

    //**************************************************************************
    // HIT-TEST METHODS.
    //**************************************************************************

	/**
     * @brief   Tests if a Shape includes a vector.
     * @return  true or false
     * @param   vector    vector to test
	 */
    bool hitTest (const Vector& vector) const;

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
     * @brief Gets the left bottom vector of the shape.
     */
    Vector getLeftBottom() const;

    /**
     * @brief Gets the right top vector of the shape.
     */
    Vector getRightTop() const;

private:
    /// Coordinates of the center of the Shape.
    Vector center;

    /// Type of shape.
    ShapeType type;

    /// Size of shape.
    double size;

    /// Left bottom vector related to center.
    Vector left_bottom;

    /// Right top vector related to center.
    Vector right_top;

    /// Last coordinates.
    Vector last_center;

    //**************************************************************************
    // CORNER METHODS
    //**************************************************************************

    /**
     * @brief Computes new corner vectors related to center
     */

    void computeCorners();

    /**
     * @brief Checks square-circle hit test
     */

    bool squareCircleHitTest(const Shape& square, const Shape& circle) const;

    /**
     *    @brief Checks if a segment overlaps a circle
     */
    bool circleOverlapsSegment(Shape shape, Vector pt1, Vector pt2) const;

};

#endif // SHAPE_H
