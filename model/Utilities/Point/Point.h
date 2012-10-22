
#ifndef POINT_H
#define POINT_H


/**
  * class Point
  * 
  */

class Point
{
public:

	// Constructors/Destructors
	//  

    /**
     * @brief Empty constructor
     */
    Point () {}

	/**
     * @brief Point constructor
	 */
    Point (double x, double y );

	/**
	 * Empty Destructor
	 */
    ~Point ( );

    /**
     *  @brief Compute distance to another point
     *  @param point another point
     *  @return distance
     */
    double getDistance(Point point);

    /// Compare two points
    bool equals(Point point);

    // Operators

    /**
     *  @brief Operator +
     */
    Point operator + (Point);

    /**
     *  @brief Operator -
     */
    Point operator - (Point);

    /**
     *  @brief Operator -
     */
    Point& operator -= (Point);

    /**
     *  @brief Operator -
     */
    Point& operator += (Point);

    /**
     *  @brief Operator ==
     */
    bool operator == (Point);

    /**
     * @brief Operator !=
     */
    bool operator != (Point);

    // Accessors methods
    //

    // Getters
    //

    /**
     *  @brief Get X
     */
    double getX();

    /**
     *  @brief Get Y
     */
    double getY();

    // Setters
    //

    /**
     *  @brief Set X
     */
    void setX(double x);

    /**
     *  @brief Set Y
     */
    void setY(double y);

private:

    // Private attributes

    // Coordinate X
    double x;
    // Coordinate Y
    double y;
};

#endif // POINT_H
