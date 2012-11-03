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
     * @brief Constructor.
     * @param x X-coordinate
     * @param y Y-coordinate
     */
    Point(double x, double y);

    /**
     * @brief Constructor.
     */
    Point();

    /**
     * @brief Destructor.
     */
    ~Point();

    //**************************************************************************
    // DISTANCE.
    //**************************************************************************

    /**
     *  @brief  Compute distance to another point
     *  @param  point   another point
     *  @return distance
     */
    double getDistance(const Point& point) const;

    /**
     * @brief  Compares two points.
     * @param  point    point to compare with
     * @return true or false
     */
    bool equals(const Point &point) const;

    //**************************************************************************
    // OPERATORS.
    //**************************************************************************

    /**
     * @brief Operator +.
     */
    Point operator+(Point) const;

    /**
     * @brief Operator -.
     */
    Point operator-(Point) const;

    /**
     *  @brief Operator -=.
     */
    Point& operator-=(Point);

    /**
     * @brief Operator +=.
     */
    Point& operator+=(Point);

    /**
     *  @brief Operator unary -
     */
    Point operator-() const;

    /**
     * @brief Operator ==.
     */
    bool operator==(Point) const;

    /**
     * @brief Operator !=.
     */
    bool operator!=(Point) const;

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Get X.
     */
    double getX() const;

    /**
     * @brief Set X.
     */
    void setX(double x);

    /**
     * @brief Get Y.
     */
    double getY() const;

    /**
     * @brief Set Y.
     */
    void setY(double y);

private:
    /// Coordinate X.
    double x;

    /// Coordinate Y.
    double y;
};

#endif // POINT_H
