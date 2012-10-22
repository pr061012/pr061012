/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef POINT_H
#define POINT_H


/**
  * @class Point
  * @brief Point class
  */

class Point
{
public:

    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

	/**
     * @brief Empty Constructor
	 */
    Point (double x, double y );

	/**
     * @brief Empty Destructor
	 */
    ~Point ( );

    /**
     *  @brief Compute distance to another point
     */
    double getDistance(Point point);

    //******************************************************************************
    // ACCESSORS.
    //******************************************************************************

    /**
     *  @brief Get X
     */
    double getX();

    /**
     *  @brief Set X
     */
    void setX(double x);

    /**
     *  @brief Get Y
     */
    double getY();

    /**
     *  @brief Set Y
     */
    void setY(double y);

private:

    /// Coordinate X
    double x;
    /// Coordinate Y
    double y;
};

#endif // POINT_H
