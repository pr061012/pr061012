/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef DECISION_MAKER_H
#define DECISION_MAKER_H

/**
  * @class DecisionMaker
  * @brief Makes a prediction about next creature's action.
  */
class DecisionMaker
{
public:
    /**
     * @brief Constructor.
     */
    DecisionMaker(Matrix m);

    /**
     * @brief Destructor.
     */
    ~DecisionMaker();

	/**
     * @brief  Makes a creature's decision about next action.
     * @param  attrs    vector of creature's attributes
     * @return int      next action
	 */
    // TODO: Add enum for creatures's actions.
    int makeDecision(Vector attrs);

private:
    /// @brief Matrix for decision making. In the nutshell, it's a SM or
    /// no-hidden-layer NN matrix.
    // TODO: Move here and in constructo Matrix by own or armadillo type.
    Matrix theta;
};

#endif // DECISION_MAKER_H
