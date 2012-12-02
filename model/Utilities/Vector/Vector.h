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
     *  @brief  Get projection of the point on the line
     *  @param  pt1 first point of the line
     *  @param  pt2 second point of the line
     *  @return projection of the point on the line
     */

    Vector project(const Vector& pt1, const Vector& pt2) const;

    /**
     *    @brief    Get scalar product of two vectors
     *    @param    vec1 first vector
     *    @param    vec2 second vector
     *    @return   Scalar product.
     */

    static double scalarProduct(const Vector& vec1, const Vector& vec2);

    /**
     *    @brief    Get vector product of two vectors
     *    @param    vec1 first vector
     *    @param    vec2 second vector
     *    @return   Vector product.
     */
    static double vectorProduct(const Vector& vec1, const Vector& vec2);

    /**
     * @brief   Gets the point's projection's parameter on the line, formed
     *          by given 2 points.
     * @param   zero point of the line for t = 0
     * @param   one  point of the line for t = 1
     * @return  parameter:
     *          0 < t < 1   point lies between given points
     *          t < 0       point lies outside closer to zero
     *          t > 1       poimt lies outside closer to one
     */
    double getLineParameter(const Vector& zero, const Vector& one) const;

    /**
     * @brief  Gets the intersection of given two lines.
     * @param  first_start  first point of the first line
     * @param  first_end    second point of the first line
     * @param  second_start first point of the second line
     * @param  second_end   second point of the second line
     * @return point of intersection. X == NaN if there is no intersection
     *         or the lines are equal.
     */
    static Vector getLinesIntersection(const Vector& first_start, 
                                        const Vector& first_end,
                                        const Vector& second_start, 
                                        const Vector& second_end);

    /**
     * @brief  Get angle to next point
     * @param  vec point
     * @return an angle to the point
     */

    double getAngle(const Vector& vec) const;

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
     *  @brief Operator unary -.
     */
    Vector operator-() const;

    /**
     * @brief Operator *.
     */
    Vector operator*(double) const;

    /**
     * @brief Operator /.
     */
    Vector operator/(double) const;

    /**
     * @brief Operator *=.
     */
    Vector& operator*=(double);

    /**
     * @brief Operator /=.
     */
    Vector& operator/=(double);

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
