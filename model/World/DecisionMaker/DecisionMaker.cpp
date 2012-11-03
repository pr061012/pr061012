/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "DecisionMaker.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

DecisionMaker::DecisionMaker(CreatureType type)
{
    ifstream some_matrix;
    int a;
    int i, j;
    theta = arma::mat(ACT_CONST, ATR_CONST);

    if (type == HUMANOIDS)
    {
        some_matrix.open ("humanoid_decision_matrix.txt");
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
        some_matrix.open ("non_humanoid_decision_matrix.txt");
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

int DecisionMaker::makeDecision (mat attrs)
{
    vector <int> vect_of_actions;
    int max = -1000;
    int decision;
    mat act(ACT_CONST,1);
    act = this->theta*attrs;

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
    decision = vect_of_actions[rand() % vect_of_actions.size()];

    return decision;
}

