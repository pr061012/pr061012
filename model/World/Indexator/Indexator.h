
#ifndef INDEXATOR_H
#define INDEXATOR_H

#include <string>
#include <vector>
#include "Window/Window.h"
#include "../Object/Object.h"
#include "../ObjectHeap/ObjectHeap.h"


/**
  * class Indexator
  * 
  */

class Indexator
{
public:

	// Constructors/Destructors
	//  


    /**
	 * Empty Constructor
	 */
	Indexator ( );

	/**
	 * Empty Destructor
	 */
	virtual ~Indexator ( );


	/**
	 * Создаёт сетку и индексирует по ней объекты.
	 * @param  list
	 */
	 Indexator (ObjectHeap * list )
	{
	}


	/**
	 * Даёт объекты в заданной рамке.
	 * @return ObjectHeap *
	 * @param  frame
	 */
    ObjectHeap * getFrameContents (Frame frame );


	/**
	 * Переиндексирует объекты, меняет содержимое окон.
	 */
    void step ( );


	/**
	 * Создает в windows окно для данного объекта и возвращает указатель "вид из окна".
	 * Объект должен иметь view_area : Frame.
	 * @return ObjectHeap *
	 * @param  object
	 */
    ObjectHeap * createWindow (Object * object );

private:

	// Private attributes
	//  

	// Список всех окон.
    std::vector<Window> windows;

public:


	// Private attribute accessor methods
	//  


	/**
	 * Set the value of windows
	 * Список всех окон.
	 * @param new_var the new value of windows
	 */
    void setWindows ( std::vector<Window> new_var )	 {
			windows = new_var;
	}

	/**
	 * Get the value of windows
	 * Список всех окон.
	 * @return the value of windows
     */
    std::vector<Window> getWindows ( )	 {
		return windows;
	}
private:


	void initAttributes ( ) ;

};

#endif // INDEXATOR_H
