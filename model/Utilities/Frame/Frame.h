
#ifndef FRAME_H
#define FRAME_H

#include "../Point/Point.h"

/// Shape types
enum ShapeType {CIRCLE, SQUARE};

/// Intersection flags
enum IntersectionFlags {LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8};

/**
  * class Frame
  * Рамка. Используется для задания размеров и координат объектов, а также для
  * областей просмотра и воздействия.
  */

class Frame
{
public:

    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

	/**
     *  @brief Constructor
     *  @param type type of the shape
     *  @param center center of the frame
     *  @param size size of the frame
	 */
    Frame(Point center, int type, double size);

    /**
     *  @brief Constructor
     */
    Frame();

	/**
     *  @brief Destructor
	 */
    ~Frame();

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
     * @brief Get size (edge length for polygons, radius for circle).
     * @return size
     */

    double getSize();

    /**
     * @brief Set size (edge length for polygons, radius for circle).
     * @param size new size
     */

    void setSize(double size);

    //**************************************************************************
    // HIT-TEST METHODS.
    //**************************************************************************

	/**
     * @brief   Tests if a frame includes a point.
     * @return  true or false
     * @param   point    point to test
	 */
    bool hitTest (Point point );

	/**
     * @brief   Tests if a frame intersects with another frame.
     * @return  true or false
     * @param   frame   frame to test
	 */
    bool hitTest (Frame frame );

    /**
     * @brief Gets the left bottom point of the shape.
     */
    Point getLeftBottom();

    /**
     * @brief Gets the right top point of the shape.
     */
    Point getRightTop();

    /**
     * @brief   Get intersections of minimal bounding boxes with another frame.
     * @param   frame   another frame
     * @return  flags of intersections
     */
    int intersect(Frame frame);

private:
    /// Coordinates of the center of the frame.
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


};

#endif // FRAME_H
