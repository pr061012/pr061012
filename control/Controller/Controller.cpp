/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "Controller.h"

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
#include "../../model/World/Object/Object.h"
#include "../../model/World/Object/Weather/Weather.h"
#include "../../model/World/Object/Creatures/Creature.h"
#include "../../common/BasicDefines.h"
#include "../../common/Log/Log.h"

Controller::Controller(World * world) :
    world(world)
{
    performers.resize(AMNT_ACTION_TYPES);

    performers[GO] = new TravelingPerformer(world);
    performers[CREATE_OBJ] = new CreationPerformer(world);
    performers[MINE_OBJ] = new MiningPerformer(world);
    performers[HARM_OBJS] = new HarmPerformer(world);
    performers[REGENERATE_OBJ] = new RegenerationPerformer(world);
    performers[DROP_OBJS] = new DroppingPerformer(world);
    performers[PICK_UP_OBJS] = new PickupMaster(world);
    performers[EAT_OBJ] = new EatingPerformer(world);
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
            
            if ((*i) -> getHealthPoints() <= 0 && !(*i) -> isDestroyed())
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

            // give weather and creatures objects to view
            if (object -> getType() == CREATURE)
            {
                dynamic_cast<Creature*>(object) -> setObjectsAround(
                    world -> getIndexator() -> getAreaContents(
                        dynamic_cast<Creature*>(object) -> getViewArea()));
                // check age
                if (dynamic_cast<Creature*>(object) -> getAge() >=
                    dynamic_cast<Creature*>(object) -> getMaxAge())
                {
                    object -> markAsDestroyed();
                }
            }
            else if (object -> getType() == WEATHER)
            {
                dynamic_cast<Weather*>(object) -> setCoveredObjects(
                    world -> getIndexator() -> getAreaContents(
                        dynamic_cast<Weather*>(object) -> getShape()));
            }

        }
    }
}
