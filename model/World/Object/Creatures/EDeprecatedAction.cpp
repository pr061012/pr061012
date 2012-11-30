/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include <sstream>

#include "EDeprecatedAction.h"

EDeprecatedAction::EDeprecatedAction(CreatureType type, CreatureAction action) :
    type(type),
    action(action)
{
}

const char* EDeprecatedAction::what() const throw()
{
    std::stringstream ss;
    ss << "Action ";

    switch (this -> action)
    {
        case NONE:          ss << "NONE";          break;
        case SLEEP:         ss << "SLEEP";         break;
        case EAT:           ss << "EAT";           break;
        case BUILD:         ss << "BUILD";         break;
        case GATHER:        ss << "GATHER";        break;
        case RELAX:         ss << "RELAX";         break;
        case EXPLORE:       ss << "EXPLORE";       break;
        case COMMUNICATE:   ss << "COMMUNICATE";   break;
        case WORK:          ss << "WORK";          break;
        case REALIZE_DREAM: ss << "REALIZE_DREAM"; break;
        case ESCAPE:        ss << "ESCAPE";        break;
        case REPRODUCE:     ss << "REPRODUCE";     break;
        case DO_NOTHING:    ss << "DO_NOTHING";    break;
    }

    ss << " is deprecated for ";

    switch (this -> type)
    {
        case HUMANOID:     ss << "Humanoid";    break;
        case NON_HUMANOID: ss << "NonHumanoid"; break;
    }

    ss << ".";

    return ss.str().c_str();
}
