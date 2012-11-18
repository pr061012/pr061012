/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
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

#include "../Object/Object.h"
#include "../../../common/BasicTypes.h"
#include "../../../common/ParamArray/ParamArray.h"
#include "../../../common/Log/Log.h"

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
    Action(const ActionType type, Object* actor);

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
     * @brief  Succeeded state checker.
     * @return true, if action is succeeded
     */
    bool isSucceeded() const;

    /**
     * @brief  Succeeded with errors state checker.
     * @return true, if action is succeeded (but with few errors)
     */
    bool isSucceededWithErrors() const;

    //**************************************************************************
    // STATE'S CHANGERS.
    //**************************************************************************

    /**
     * @brief Marks action as pending.
     */
    void markAsPending();

    /**
     * @brief Marks action as failed.
     */
    void markAsFailed();

    /**
     * @brief Marks action as succeeded.
     */
    void markAsSucceeded();

    /**
     * @brief Marks action as succeeded with errors.
     */
    void markAsSucceededWithErrors();

    //**************************************************************************
    // ACCESSING PARAMS/PARTICIPANTS.
    //**************************************************************************

    /**
     * @brief Adds action participant.
     * @param obj   participant
     */
    void addParticipant(Object* obj);

    /**
     * @brief  Gets action participants.
     * @return array with object's pointers
     */
    std::vector <Object*> getParticipants();

    /**
     * @brief Adds param.
     * @param param param name
     * @param value param value
     */
    template <class Type> void addParam(std::string param, Type value)
    {
        this -> params.addKey<Type>(param, value);
        getParam<Type>(param);
    }

    /**
     * @brief  Gets value of param.
     * @param  param    param name
     * @return value of param
     */
    template <class Type> Type getParam(std::string param) const throw(EParamArrayInvalidKey)
    {
        try
        {
            return this -> params.getValue<Type>(param);
        }
        catch(EParamArrayInvalidKey& exc)
        {
            Log::WARN(std::string("Tried to get param by key, which doesn't ") +
                      std::string("seem to be existed (key is '") + param +
                      "').");
            throw;
        }
    }

    /**
     * @brief  Gets actor
     * @return action actor
     */
    Object* getActor();

    /**
     * @brief  Gets type of action
     * @return type of action
     */
    ActionType getType() const;

    /**
     * @brief  Gets action's error.
     * @return type of error
     */
    ActionError getError() const;

    /**
     * @brief Sets action's error.
     * @param error action's error
     */
    void setError(ActionError error);

private:
    /// Action type.
    const ActionType type;

    /// Action's actor.
    Object* actor;

    /// Action's participants (without actor).
    std::vector <Object*> participants;

    /// Parameters.
    ParamArray params;

    /// Result type.
    ActionState state;

    /// Action error (for actions with state FAILED or SUCCEEDED_WITH_ERRORS).
    ActionError error;
};

#endif // ACTION_H
