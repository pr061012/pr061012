#include "../Performer.h"

/*
 * @class MovementPerformer
 * @brief Performs a move if it is possible
 */

class MovementPerformer : public Performer
{
public:
    
    //*************************************************************************
    //  CONSTRUCTOR/DESTRUCTOR
    //*************************************************************************

    /**
     * @brief Constructor for a particular world
     * @param world_size size of the world
     */
    MovementPerformer(double world_size);

    /**
     * @brief Destructor
     */
    ~MovementPerformer();

    //*************************************************************************
    //  PERFORM
    //*************************************************************************
    
    /**
     * @brief Check if an object can move and move it
     * @param action a request for moving
     */
    void perform(Action& action);

private:

    //*************************************************************************
    //  ATTRIBUTES
    //*************************************************************************
    
    /// Size of the world
    double world_size;
};
