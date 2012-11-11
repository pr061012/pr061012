/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "../Performer/MovementPerformer/MovementPerformer.h"
#include "../Performer/CreationPerformer/CreationPerformer.h"
#include "../Performer/HarmPerformer/HarmPerformer.h"
#include "../Performer/RepairingPerformer/RepairingPerformer.h"
#include "../Performer/MiningPerformer/MiningPerformer.h"
#include "../Performer/DroppingPerformer/DroppingPerformer.h"
#include "../Performer/PickupMaster/PickupMaster.h"
#include "Controller.h"

Controller::Controller(World * world) :
    world(world)
{
    // FIXME: Dirty workaround.
    performers.resize(200);
    performers[GO] = (Performer *) new MovementPerformer(world -> getSize(), 
                                                         world -> getIndexator());
    performers[CREATE_OBJ] = (Performer *) new CreationPerformer(*world -> getIndexator(), world);
    performers[MINE_OBJ] = (Performer *) new MiningPerformer(*world -> getIndexator());
    performers[HARM_OBJS] = (Performer *) new HarmPerformer(*world -> getIndexator());
    performers[REPAIR_OBJ] = (Performer *) new RepairingPerformer();
    performers[DROP_OBJS] = (Performer *) new DroppingPerformer(world);
    performers[PICK_UP_OBJS] = (Performer *) new PickupMaster(world);
}

Controller::~Controller()
{
}

void Controller::step()
{
    for (int i = 0; i < 2; i++) 
    {
        // first look for visible objects, then for hidden
        ObjectHeap * objects= world -> getVisibleObjects();
        if (!i)
        {
            objects = world -> getVisibleObjects();
        }
        else
        {
            objects = world -> getHiddenObjects();
        }

        for (ObjectHeap::iterator i = objects -> begin(); i != objects -> end(); i++)
        {
            // check objects health
            /*
            if (!(*i) -> getHealth())
            {
                (*i) -> markAsDestroyed();
            }
            */

            // perform object's actions
            std::vector<Action> * actions = (*i) -> getActions();

            for (std::vector<Action>::iterator j = actions -> begin(); 
                    j != actions -> end(); j++)
            {
                performers[(*j).getType()] -> perform(*j);
            }
        }
    }
}
