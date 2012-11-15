/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <assert.h>
#include "../../model/World/DecisionMaker/DecisionMaker.h"
#include "../../model/BasicTypes.h"

using namespace arma;
using namespace std;

int main()
{
    mat a(ATR_CONST,1);
    int c;

    DecisionMaker* b = new DecisionMaker(HUMANOID);

    ifstream test_hunger1;
    test_hunger1.open("test_hunger1.txt");
    if(test_hunger1 == 0)
    {
        cout<<"error!";
        return 0;
    }

    for(int k=0; k < 9; k++)
        {
            test_hunger1 >> c;
            a(k,0) = c;
        }

    cout << b->makeDecision(a);
    delete b;
    return 0;
}
