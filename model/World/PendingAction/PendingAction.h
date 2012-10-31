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
    PendingAction();

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
    PendingActionResultType result;
};

#endif // PENDINGACTION_H
