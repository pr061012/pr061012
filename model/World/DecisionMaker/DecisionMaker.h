/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef DECISION_MAKER_H
#define DECISION_MAKER_H

#define ATR_CONST_HUM 9
#define ACT_CONST_HUM 9
#define ATR_CONST_NON_HUM 5
#define ACT_CONST_NON_HUM 5
#define PATH_TO_HUM_MATRIX "/../../../res/humanoid_matrix_decision.txt"
#define PATH_TO_NON_HUM_MATRIX "/../../../res/non_humanoid_matrix_decision.txt"

// Temporary workaround.

#include <armadillo>
#include<fstream>
#include "../../BasicTypes.h"
#include<vector>
#include <stdlib.h>


using namespace std;
using namespace arma;


/**
 * @class DecisionMaker
 * @brief Makes a prediction about next creature's action.
 */
class DecisionMaker
{
public:

    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    DecisionMaker(CreatureType type);

    /**
     * @brief Destructor.
     */
    ~DecisionMaker();

    //**************************************************************************
    // PREDICTION.
    //**************************************************************************

    /**
     * @brief  Makes a creature's decision about next action.
     * @param  attrs    vector of creature's attributes
     * @return int      next action
     */
    // TODO: Add enum for creatures's actions.
    int makeDecision(mat attrs);

private:
    /// @brief Matrix for decision making. In the nutshell, it's a SM or
    /// no-hidden-layer NN matrix.
    // TODO: Move here and in constructo Matrix by own or armadillo type.
    mat theta;

};

#endif // DECISION_MAKER_H
