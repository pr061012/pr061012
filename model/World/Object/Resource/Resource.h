/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef RESOURCE_H
#define RESOURCE_H
#include "../Object.h"
#include "../Tool/Tool.h"

/**
  * @class Resource
  * @brief Resourse class
  */

class Resource : virtual public Object
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

	Resource ( );

    ~Resource ( );

	/**
	 * Добыча ресурса. Возвращает кол-во добытого ресурса. Должен вызывать tool.use()
	 * @return int
	 * @param  tool
	 */
    int gather(Tool tool);

	/**
	 * Мб регенерация?
	 */
    void step();


    //******************************************************************************
    // ACCESSORS.
    //******************************************************************************

	/**
	 * Set the value of progress
	 * Отображает прогресс добычи ресурса, ибо у нас дерево не одним ударом топора
	 * рубится (сколько ударов осталось).
	 * @param new_var the new value of progress
	 */
    void setProgress(int new_var);

	/**
	 * Get the value of progress
	 * Отображает прогресс добычи ресурса, ибо у нас дерево не одним ударом топора
	 * рубится (сколько ударов осталось).
	 * @return the value of progress
	 */
    int getProgress();

	/**
	 * Set the value of subtype
	 * @param new_var the new value of subtype
	 */
    void setSubtype(ResourceType new_var);

	/**
	 * Get the value of subtype
	 * @return the value of subtype
	 */
    ResourceType getSubtype();

	/**
	 * Set the value of regeneration_rate
	 * Скорость регенерации ресурса (либо кол-во шагов на восстановление 1 ресурса,
	 * либо кол-во шагов полного восстановления, либо ещё чё-нибудь.
	 * @param new_var the new value of regeneration_rate
	 */
    void setRegenerationRate(int new_var);

	/**
	 * Get the value of regeneration_rate
	 * Скорость регенерации ресурса (либо кол-во шагов на восстановление 1 ресурса,
	 * либо кол-во шагов полного восстановления, либо ещё чё-нибудь.
	 * @return the value of regeneration_rate
	 */
    int getRegenerationRate();

	/**
	 * Set the value of gathered
	 * ИМХО должны быть ресурсы добываемые (деревья, шахты, кусты, горы) и добытые
	 * (готовые брёвна, камни, руда, корзина с ягодой).
	 * Затем и нужен этот флаг.
	 * @param new_var the new value of gathered
	 */
    void setGathered(bool new_var);

	/**
	 * Get the value of gathered
	 * ИМХО должны быть ресурсы добываемые (деревья, шахты, кусты, горы) и добытые
	 * (готовые брёвна, камни, руда, корзина с ягодой).
	 * Затем и нужен этот флаг.
	 * @return the value of gathered
	 */
    bool getGathered();

	/**
	 * Set the value of difficulty
	 * Кол-во ходов на добычу ресурса.
	 * @param new_var the new value of difficulty
	 */
    void setDifficulty(int new_var);

	/**
	 * Get the value of difficulty
	 * Кол-во ходов на добычу ресурса.
	 * @return the value of difficulty
	 */
    int getDifficulty();

	/**
	 * Set the value of amount_per_gather
	 * Кол-во получаемого ресурса при добыче.
	 * @param new_var the new value of amount_per_gather
	 */
    void setAmountPerGather(int new_var);

	/**
	 * Get the value of amount_per_gather
	 * Кол-во получаемого ресурса при добыче.
	 * @return the value of amount_per_gather
	 */
    int getAmountPerGather();

private:
    /// Отображает прогресс добычи ресурса, ибо у нас дерево не одним ударом топора рубится (сколько ударов осталось).
    int progress;
    /// Type of resource
    ResourceType subtype;
    /// Скорость регенерации ресурса (либо кол-во шагов на восстановление 1 ресурса, либо кол-во шагов полного восстановления, либо ещё чё-нибудь.
    int regeneration_rate;
    /// ИМХО должны быть ресурсы добываемые (деревья, шахты, кусты, горы) и добытые (готовые брёвна, камни, руда, корзина с ягодой).
    bool gathered;
    /// Кол-во ходов на добычу ресурса.
    int difficulty;
    /// Кол-во получаемого ресурса при добыче.
    int amount_per_gather;

};

#endif // RESOURCE_H
