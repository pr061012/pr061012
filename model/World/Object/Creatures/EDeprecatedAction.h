/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#ifndef E_DEPRECATED_ACTION_H
#define E_DEPRECATED_ACTION_H

#include <exception>

#include "../../../../common/BasicTypes.h"

class EDeprecatedAction : public std::exception
{
public:
    /**
     * @brief Constructor.
     * @param type      type of creature
     * @param action    deprecated action
     */
    EDeprecatedAction(CreatureType type, CreatureAction action);

    virtual const char* what() const throw();

private:
    /// Creature type.
    const CreatureType type;

    /// Creature action.
    const CreatureAction action;
};

#endif // E_DEPRECATED_ACTION_H
