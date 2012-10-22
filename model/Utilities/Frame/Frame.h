
#ifndef FRAME_H
#define FRAME_H

#include "../Point/Point.h"



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
	 * Empty Constructor
	 */
	Frame ( );

	/**
	 * Empty Destructor
	 */
	virtual ~Frame ( );


	/**
	 * Проверка пересечеия с точкой.
	 * @return bool
	 * @param  point
	 */
    bool hitTest (Point point );


	/**
	 * Проверка пересечения с рамкой.
	 * @return bool
	 * @param  frame
	 */
    bool hitTest (Frame frame );

private:

	// Координаты рамки.
	Point center;

public:


	// Private attribute accessor methods
	//  


	/**
	 * Set the value of center
	 * Координаты рамки.
	 * @param new_var the new value of center
	 */
	void setCenter ( Point new_var )	 {
			center = new_var;
	}

	/**
	 * Get the value of center
	 * Координаты рамки.
	 * @return the value of center
	 */
	Point getCenter ( )	 {
		return center;
	}
private:


	void initAttributes ( ) ;

};

#endif // FRAME_H
