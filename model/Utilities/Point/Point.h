
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
	 * Empty Constructor
	 */
    Point (double x, double y );

	/**
	 * Empty Destructor
	 */
    ~Point ( );

    /**
     *  @brief Compute distance to another point
     */
    double getDistance(Point point);

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
