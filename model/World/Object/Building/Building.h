/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/
#ifndef BUILDING_H
#define BUILDING_H
#include "../Object.h"
#include "../Tool/Tool.h"
#include "../../ObjectHeap/ObjectHeap.h"

/**
  * @class Building
  * @brief Building Class
  */

class Building : public Object
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    Building();

    ~Building();

	/**
	 * Возвращает успешность операции.
	 * @return bool
	 * @param  object
	 */
    bool putInside(Object * object);

	/**
	 * Возвращает успешность операции.
	 * @return bool
	 * @param  object
	 */
    bool takeOut(Object * object);

	/**
     * Ремонт/постройка. Должен вызывать tool.use();
	 * @param  tool
	 */
    void maintain(Tool tool);


    //******************************************************************************
    // ACCESSORS.
    //******************************************************************************

	/**
	 * Set the value of contents
	 * Содержимое дома.
	 * @param new_var the new value of contents
	 */
    void setContents(ObjectHeap new_var);

	/**
	 * Get the value of contents
	 * Содержимое дома.
	 * @return the value of contents
	 */
    ObjectHeap getContents();

	/**
	 * Set the value of free_space
	 * @param new_var the new value of free_space
	 */
    void setFreeSpace ( int new_var );

	/**
	 * Get the value of free_space
	 * @return the value of free_space
	 */
    int getFreeSpace();

	/**
	 * Set the value of max_space
	 * @param new_var the new value of max_space
	 */
    void setMaxSpace(int new_var);

	/**
	 * Get the value of max_space
	 * @return the value of max_space
	 */
    int getMaxSpace();

	/**
	 * Set the value of isFinished
	 * Построен/нет
	 * @param new_var the new value of isFinished
	 */
    void setIsFinished(bool new_var);

	/**
	 * Get the value of isFinished
	 * Построен/нет
	 * @return the value of isFinished
	 */
    bool getIsFinished();

private:
    /// Содержимое дома.
    ObjectHeap contents;
    int free_space;
    int max_space;
    /// Построен/нет
    bool isFinished;

};

#endif // BUILDING_H
