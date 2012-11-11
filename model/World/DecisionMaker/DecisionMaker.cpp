/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "DecisionMaker.h"
#include "../../BasicDefines.h"
  	
using namespace std;
using namespace arma;

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

DecisionMaker::DecisionMaker(CreatureType type)
{
    ifstream some_matrix;
    int a;
    int i, j;
    theta = arma::mat(ACT_CONST, ATR_CONST);

    if (type == HUMANOID)
    {
        some_matrix.open (PATH_TO_HUM_MATRIX);
        if (some_matrix == NULL)
        {
            cerr << "[ERROR] DecisionMaker: cannot open file 'humanoid_decision_matrix.txt'" << endl;
        }

        for (i = 0; i < ATR_CONST; i++)
            for (j = 0; j < ACT_CONST; j++)
            {
                some_matrix >> a;
                this->theta(i,j) = a;
            }
    }

    if (type == NON_HUMANOID)
    {
        some_matrix.open (PATH_TO_NON_HUM_MATRIX);
        if (some_matrix == NULL)
        {
            cerr << "[ERROR] DecisionMaker: cannot open file 'non_humanoid_decision_matrix.txt'" << endl;
        }

        for (i = 0; i < ATR_CONST; i++)
            for (j = 0; j < ACT_CONST; j++ )
            {
                some_matrix >> a;
                this->theta(i,j) = a;
            }
    }
    some_matrix.close();
}

DecisionMaker::~DecisionMaker()
{

}

//******************************************************************************
// PREDICTION.
//******************************************************************************

bool DecisionMaker::isDecisionActual(arma::mat attrs, CreatureAction current_decision) const
{
    mat act(ACT_CONST,1);
    unsigned int index;
    act = this -> theta * attrs;

    switch(current_decision)
    {
    case SLEEP:           index = 0; break;
    case BUILD:           index = 1; break;
    case WORK:            index = 2; break;
    case EAT:             index = 3; break;
    case RELAX:           index = 4; break;
    case COMMUNICATE:     index = 5; break;
    case ESCAPE:          index = 6; break;
    case REALIZE_DREAM:   index = 7; break;
    case CONTINUE_GENDER: index = 8; break;
    default: ;
    }

    for (int i = 0; i < ACT_CONST; i++)
    {
        if(act(i,0) - act(index,i) > CREAT_CRIT_CONST)
        {
            return false;
        }
    }

    return true;
}

CreatureAction DecisionMaker::makeDecision(mat attrs) const
{
    vector <int> vect_of_actions;
    int max = -1000;
    CreatureAction decision = NONE;
    int numb_of_decision;
    mat act(ACT_CONST,1);
    act = this -> theta * attrs;
    act(7,0) += 550;

    for(int i = 0; i < ACT_CONST; i++)
    {
        if (act(i,0) == max)
        {
            vect_of_actions.push_back(i);
        }

        if(act(i,0) > max)
        {
            max = act(i,0);
            vect_of_actions.clear();
            vect_of_actions.push_back(i);
        }

    }
    numb_of_decision = vect_of_actions[rand() % vect_of_actions.size()];
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
    case 8: decision = CONTINUE_GENDER;
    }

    return decision;
}

