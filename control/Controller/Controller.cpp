/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "../Performer/TravelingPerformer/TravelingPerformer.h"
#include "../Performer/CreationPerformer/CreationPerformer.h"
#include "../Performer/HarmPerformer/HarmPerformer.h"
#include "../Performer/RegenerationPerformer/RegenerationPerformer.h"
#include "../Performer/MiningPerformer/MiningPerformer.h"
#include "../Performer/DroppingPerformer/DroppingPerformer.h"
#include "../Performer/EatingPerformer/EatingPerformer.h"
#include "../Performer/MovementPerformer/MovementPerformer.h"
#include "../Performer/PickupMaster/PickupMaster.h"
#include "../../model/World/Action/Action.h"
#include "Controller.h"
#include "../../model/World/Object/Object.h"

Controller::Controller(World * world) :
    world(world)
{
    // FIXME: Dirty workaround.
    performers.resize(200);

    performers[GO] = (Performer *) new TravelingPerformer(world -> getSize(), 
                                                         world -> getIndexator());
    performers[CREATE_OBJ] = (Performer *) new CreationPerformer(*world -> getIndexator(), world);
    performers[MINE_OBJ] = (Performer *) new MiningPerformer(*world -> getIndexator());
    performers[HARM_OBJS] = (Performer *) new HarmPerformer(*world -> getIndexator());
    performers[REPAIR_OBJ] = (Performer *) new RegenerationPerformer();
    performers[DROP_OBJS] = (Performer *) new DroppingPerformer(world);
    performers[PICK_UP_OBJS] = (Performer *) new PickupMaster(world);
    performers[EAT_OBJ] = (Performer *) new EatingPerformer(world);
    performers[MOVE] = new MovementPerformer(world);
}

Controller::~Controller()
{
    for(uint i = 0; i < this -> performers.size(); i++)
    {
        delete this -> performers[i];
    }
}

void Controller::step()
{
    for (int k = 0; k < 2; k++)
    {
        // first look for visible objects, then for hidden
        ObjectHeap* objects;
        if (!k)
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
            
            if (!(*i) -> getHealthPoints())
            {
                (*i) -> markAsDestroyed();
            }
            

            // perform object's actions
            Object* object = (*i);
            if (!object -> isDestroyed())
            {
                std::vector<Action> * actions = object -> getActions();

                for (uint j = 0; j < actions -> size(); j++)
                {
                    performers[(actions->at(j)).getType()] -> perform(actions->at(j));
                }
            }
        }
    }
}
