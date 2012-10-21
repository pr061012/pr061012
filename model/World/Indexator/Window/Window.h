
#ifndef WINDOW_H
#define WINDOW_H

#include "../../Object/Object.h"
#include "../../ObjectHeap/ObjectHeap.h"



/**
  * class Window
  * 
  */

class Window
{
public:

	// Constructors/Destructors
	//  


	/**
	 * Empty Constructor
	 */
	Window ( );

	/**
	 * Empty Destructor
	 */
	virtual ~Window ( );

	// Static Public attributes
	//  

	// Public attributes
	//  


	// Public attribute accessor methods
	//  


	// Public attribute accessor methods
	//  


protected:

	// Static Protected attributes
	//  

	// Protected attributes
	//  

public:


	// Protected attribute accessor methods
	//  

protected:

public:


	// Protected attribute accessor methods
	//  

protected:


private:

	// Static Private attributes
	//  

	// Private attributes
	//  

	// Объект - родитель окна.
	Object * parent;
	// "Вид из окна"
	ObjectHeap contents;
public:


	// Private attribute accessor methods
	//  

private:

public:


	// Private attribute accessor methods
	//  


	/**
	 * Set the value of parent
	 * Объект - родитель окна.
	 * @param new_var the new value of parent
	 */
	void setParent ( Object * new_var )	 {
			parent = new_var;
	}

	/**
	 * Get the value of parent
	 * Объект - родитель окна.
	 * @return the value of parent
	 */
	Object * getParent ( )	 {
		return parent;
	}

	/**
	 * Set the value of contents
	 * "Вид из окна"
	 * @param new_var the new value of contents
	 */
	void setContents ( ObjectHeap new_var )	 {
			contents = new_var;
	}

	/**
	 * Get the value of contents
	 * "Вид из окна"
	 * @return the value of contents
	 */
	ObjectHeap getContents ( )	 {
		return contents;
	}
private:


	void initAttributes ( ) ;

};

#endif // WINDOW_H
