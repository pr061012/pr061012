/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "DecisionMaker.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

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
    int i,j;

    if(type==HUMANOID)
    {
        some_matrix.open("humanoid_decision_matrix.txt");
        if (some_matrix==NULL)
        {
            cout<<"error! can not open the file" << endl;
            return 0;
        }

        for(i=0; i<ATR_CONST_HUM; i++)
            for (j=0; j<ACT_CONST_HUM; j++ )
            {
                some_matrix>>a;
                this->theta(i,j)=a;
            }
    }

    if(type==NON_HUMANOID)
    {
        some_matrix.open("non_humanoid_decision_matrix.txt");
        if (some_matrix==NULL)
        {
            cout<<"error! can not open the file" << endl;
            return 0;
        }

        for(i=0; i<ATR_CONST_NON_HUM; i++)
            for (j=0; j<ACT_CONST_NON_HUM; j++ )
            {
                some_matrix>>a;
                this->theta(i,j)=a;
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

int DecisionMaker::makeDecision(mat attrs)
{
    mat act;
    vector <int> vect_of_actions;
    int max=-1000;
    int decision;
    act=this->theta*attrs;
    for(int i=0; i<act.size(); i++)///////////////////////стопроцентная ошибка. нужен размер строк
    {
        if(act(i,1)==max)
        {
            vect_of_actions.push_back(i);
            count++;
        }

        if(act(i,1)>max)
        {
            max=act(i,1);
            vect_of_actions.clear();
            vect_of_actions.push_back(i);

        }

    }
    decision=vect_of_action[rand()%vect_of_actions.size()];
    return decision;
}





