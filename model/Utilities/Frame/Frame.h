
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

	// Constructors/Destructors
	//  

	/**
     *  @brief Frame constructor
     *  @param type type of the shape
     *  @param center center of the frame
     *  @param size size of the frame
	 */
    Frame (Point center, int type, double size );

	/**
	 * Empty Destructor
	 */
    ~Frame ( );

    // Private attribute accessor methods
    //

    /**
     * @brief Set the value of center
     * Координаты рамки.
     * @param new_var the new value of center
     */

    void setCenter ( Point new_var );

    /**
     * @brief Get the value of center
     * Координаты рамки.
     * @return the value of center
     */

    Point getCenter ( );

    /**
     * @brief Get type of the shape
     * @return type of the shape
     */

    int getType();

    /**
     * @brief Set type
     * @param type new type
     */

    void setType(int type);

    /**
     * @brief Get size (edge length for polygons, radius for circle)
     * @return size
     */

    double getSize();

    /**
     * @brief Set size (edge length for polygons, radius for circle)
     * @param size new size
     */

    void setSize(double size);

    // Other methods
    //

	/**
     * @brief Проверка пересечеия с точкой.
	 * @return bool
	 * @param  point
	 */
    bool hitTest (Point point );

	/**
     * @brief Проверка пересечения с рамкой.
	 * @return bool
	 * @param  frame
	 */
    bool hitTest (Frame frame );

    /**
     * @brief Get the left bottom point of the shape
     */
    Point getLeftBottom();

    /**
     * @brief Get the right top point of the shape
     */
    Point getRightTop();

    /**
     * @brief Get intersections with another frame
     * @param frame another frame
     * @return flags of intersections
     */
    int intersect(Frame frame);

private:

    /// Координаты рамки.
    Point center;
    /// Type of shape
    ShapeType type;
    /// Size of shape
    double size;
    /// Left bottom point related to center
    Point left_bottom;
    /// Right top point relatef to center
    Point right_top;
    /// Last coordinates
    Point last_center;


};

#endif // FRAME_H
