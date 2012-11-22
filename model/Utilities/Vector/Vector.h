/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef VECTOR_H
#define VECTOR_H

/**
 * @class Vector
 * @brief Vector class
 */
class Vector
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
    Vector(double x, double y);

    /**
     * @brief Constructor.
     */
    Vector();

    /**
     * @brief Destructor.
     */
    ~Vector();

    //**************************************************************************
    // DISTANCE.
    //**************************************************************************

    /**
     *  @brief  Compute distance to another vector
     *  @param  vector   another vector
     *  @return distance
     */
    double getDistance(Vector vector = Vector(0,0)) const;

    /**
     *  @brief  Compute distance to a line formed by two vectors
     *  @param  line_start  first vector of the line
     *  @param  line_end    second vector of the line
     *  @return distance
     */

    double getDistanceToLine(const Vector& line_start,
                                const Vector& line_end) const;

    /**
     *  @brief  Get projection of the vector on the line
     *  @param  pt1 first vector of the line
     *  @param  pt2 second vector of the line
     *  @return projection of the vector on the line
     */

    Vector project(Vector pt1, Vector pt2) const;

    /**
     *    @brief    Get scalar product of two vectors
     *    @param    pt1 first vector
     *    @param    pt2 second vector
     *    @return   Scalar product.
     */

    static double scalarProduct(Vector vec1, Vector vec2);

    /**
     * @brief Get angle to next point
     * @param angle angle
     */

    double getAngle(Vector vec);

    /**
     * @brief  Compares two vectors.
     * @param  vector    vector to compare with
     * @return true or false
     */
    bool equals(const Vector &vector) const;

    //**************************************************************************
    // OPERATORS.
    //**************************************************************************

    /**
     * @brief Operator +.
     */
    Vector operator+(Vector) const;

    /**
     * @brief Operator -.
     */
    Vector operator-(Vector) const;

    /**
     *  @brief Operator -=.
     */
    Vector& operator-=(Vector);

    /**
     * @brief Operator +=.
     */
    Vector& operator+=(Vector);

    /**
     *  @brief Operator unary -
     */
    Vector operator-() const;

    /**
     * @brief Operator ==.
     */
    bool operator==(Vector) const;

    /**
     * @brief Operator !=.
     */
    bool operator!=(Vector) const;

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

#endif // VECTOR_H
