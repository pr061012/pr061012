/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef PENDING_ACTION_H
#define PENDING_ACTION_H

#include <vector>
#include <map>

#include "../Object/Object.h"
#include "../../BasicTypes.h"

/**
 * @brief PendingAction contains information about object's pending action.
 */
class PendingAction
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR
    //**************************************************************************

    /**
     * @brief Constructor.
     * @param actor action's actor
     * @param type  action type
     */
    PendingAction(const Object * actor, const PendingActionType type);

    /**
     * @brief Destructor,
     */
    ~PendingAction();

    //**************************************************************************
    // STATE'S CHECKERS
    //**************************************************************************

    /**
     * @brief  Gets current state of action.
     * @return current state of action
     */
    PendingActionStateType getState();

    /**
     * @brief  Pending state checker.
     * @return true, if action is pending
     */
    bool isPending();

    /**
     * @brief  Failed state checker.
     * @return true, if action is failed
     */
    bool isFailed();

    /**
     * @brief  Succeed state checker.
     * @return true, if action is succeed
     */
    bool isSucceed();

private:
    /// Action's actor.
    const Object * actor;

    /// Action's participants (without actor).
    std::vector <const Object *> participants;

    /// Parameters.
    std::map <std::string, int> params;

    /// Action type.
    const PendingActionType type;

    /// Result type.
    PendingActionStateType state;
};

#endif // PENDINGACTION_H
