/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <vector>
#include <map>

// NOTE: In Object.h this file is included. To prevent compiler crash we need to
//       declare Object and Action first. Maybe not a good solution.
class Object;
class Action;

#include "../ParamArray/ParamArray.h"
#include "../Object/Object.h"
#include "../../BasicTypes.h"

/**
 * @brief Action contains information about object's pending action.
 */
class Action
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR
    //**************************************************************************

    /**
     * @brief Constructor.
     * @param type          action's type
     * @param actor         action's actor
     */
    Action(const ActionType type, const Object * actor);

    /**
     * @brief Destructor,
     */
    ~Action();

    //**************************************************************************
    // STATE'S CHECKERS
    //**************************************************************************

    /**
     * @brief  Gets current state of action.
     * @return current state of action
     */
    ActionState getState() const;

    /**
     * @brief  Pending state checker.
     * @return true, if action is pending
     */
    bool isPending() const;

    /**
     * @brief  Failed state checker.
     * @return true, if action is failed
     */
    bool isFailed() const;

    /**
     * @brief  Succeed state checker.
     * @return true, if action is succeed
     */
    bool isSucceed() const;

    //**************************************************************************
    // STATE'S CHANGERS.
    //**************************************************************************

    /**
     * @brief Marks action as failed.
     */
    void markAsFailed();

    /**
     * @brief Marks action as succeed.
     */
    void markAsSucceed();

    //**************************************************************************
    // ACCESSING PARAMS/PARTICIPANTS.
    //**************************************************************************

    /**
     * @brief Adds action participant.
     * @param obj   participant
     */
    void addParticipant(Object * obj);

    /**
     * @brief Adds param.
     * @param param param name
     * @param value param value
     */
    void addParam(std::string param, int value);

    /**
     * @brief  Gets value of param.
     * @param  param    param name
     * @return value of param
     */
    // TODO: Throw an exception when param isn't specified.
    int getParam(std::string param) const;

private:
    /// Action type.
    const ActionType type;

    /// Action's actor.
    const Object * actor;

    /// Action's participants (without actor).
    std::vector <const Object *> participants;

    /// Parameters.
    ParamArray params;

    /// Result type.
    ActionState state;
};

#endif // ACTION_H
