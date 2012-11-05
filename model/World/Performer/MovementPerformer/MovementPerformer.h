#include "../Performer.h"
#include "../../Indexator/Indexator.h"

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
    MovementPerformer(const double world_size,
                      Indexator& indexator);

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
    const double world_size;
    
    /// The reference to worlds indexator
    Indexator& indexator;
};
