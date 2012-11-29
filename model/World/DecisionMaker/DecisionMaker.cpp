/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "DecisionMaker.h"
#include "../../../common/BasicDefines.h"
#include "../../../common/Log/Log.h"
#include "../../../common/Exceptions/EInvalidResPath.h"
#include "../../../common/Math/DoubleComparison.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

DecisionMaker::DecisionMaker(CreatureType type)
{
    std::string matrix_path;

    // Choosing matrix path.
    switch (type)
    {
        case HUMANOID:     matrix_path = DM_PATH_TO_HUM_MATRIX;  break;
        case NON_HUMANOID: matrix_path = DM_PATH_TO_NHUM_MATRIX; break;
    }

    // Trying to open file with matrix.
    std::ifstream some_matrix(matrix_path);

    if (!some_matrix)
    {
        Log::ERROR("Cannot open file '" + matrix_path + "'.");
        throw EInvalidResPath(matrix_path);
    }

    // Reading matrix from file.
    int a;
    theta = arma::mat(DM_ACT_CONST, DM_ATR_CONST);
    for (uint i = 0; i < DM_ATR_CONST; i++)
    {
        for (uint j = 0; j < DM_ACT_CONST; j++)
        {
            some_matrix >> a;
            this -> theta(i, j) = a;
        }
    }
}

DecisionMaker::~DecisionMaker()
{
}

//******************************************************************************
// PREDICTION.
//******************************************************************************

bool DecisionMaker::isDecisionActual(arma::mat attrs, CreatureAction current_decision) const
{
    arma::mat act = this -> theta * attrs;
    uint index = -1;

    switch (current_decision)
    {
        case SLEEP:           index = 0;    break;
        case BUILD:           index = 1;    break;
        case WORK:            index = 2;    break;
        case EAT:             index = 3;    break;
        case RELAX:           index = 4;    break;
        case COMMUNICATE:     index = 5;    break;
        case ESCAPE:          index = 6;    break;
        case REALIZE_DREAM:   index = 7;    break;
        case REPRODUCE:       index = 8;    break;
        default:              return false; break;
    }

    for (int i = 0; i < DM_ACT_CONST; i++)
    {
        if (act(i, 0) - act(index, 0) > CREAT_CRIT_CONST)
        {
            return false;
        }
    }

    return true;
}

CreatureAction DecisionMaker::makeDecision(arma::mat attrs) const
{
    std::vector <int> vect_of_actions;
    double max = -1000;

    arma::mat act = this -> theta * attrs;
    act(7, 0) = -200;//+= 550;

    for(uint i = 0; i < act.size(); i++)
    {
        if (DoubleComparison::areEqual(act(i, 0), max)
        {
            vect_of_actions.push_back(i);
        }

        if (DoubleComparison::isGreater(act(i, 0), max))
        {
            max = act(i, 0);
            vect_of_actions.clear();
            vect_of_actions.push_back(i);
        }

    }

    int numb_of_decision;
    if (vect_of_actions.size())
    {
        numb_of_decision = vect_of_actions[rand() % vect_of_actions.size()];
    }
    else 
    {
        numb_of_decision = 0;
    }

    CreatureAction decision = NONE;
    switch(numb_of_decision)
    {
    case 0: decision = SLEEP; break;
    case 1: decision = BUILD; break;
    case 2: decision = WORK; break;
    case 3: decision = EAT; break;
    case 4: decision = RELAX; break;
    case 5: decision = COMMUNICATE; break;
    case 6: decision = ESCAPE; break;
    case 7: decision = REALIZE_DREAM; break;
    case 8: decision = REPRODUCE;
    }

    return decision;
}

// BAD
arma::mat DecisionMaker::getActMatrix(arma::mat attrs) const
{
    return this -> theta * attrs;
}
