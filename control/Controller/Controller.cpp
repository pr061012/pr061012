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

void Controller::destroy(Object * object)
{
    object -> markAsDestroyed();
    world -> getIndexator() -> removeObject(object);

    if (object -> getType() == CREATURE)
    {
        // Drop all belongings to the ground.
        ObjectHeap * inventory = 
            dynamic_cast<Creature*>(object) -> getInventory();

        for (ObjectHeap::iterator i = inventory -> begin();
             i != inventory -> end(); i++)
        {
            hiddenToVisible.push(*i);
            (*i) -> setCoords(object -> getCoords());
        }

    }
}

void Controller::step()
{
    
    // clear buffers
    hiddenToVisible.clear();
    visibleToHidden.clear();
    actions.clear();

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
        ObjectHeap::iterator end = objects -> end();
        for (ObjectHeap::iterator i = objects -> begin(); i != end; i++)
        {
            // check objects health
            if ((*i) -> getHealthPoints() <= 0 && !(*i) -> isDestroyed())
            {
                destroy(*i);
            }

            // don't do anything with destored objects
            if ((*i) -> isDestroyed())
            {
                continue;
            }
            
            // get actions to the buffer
            std::vector<Action>* buf = (*i) -> getActions();

            // creatures are special
            if ((*i) -> getType() == CREATURE)
            {
                // place view_area at the object
                Shape view_area = dynamic_cast<Creature*>(*i) -> getViewArea();
                view_area.setCenter((*i) -> getCoords());

                // show creature objects around it
                dynamic_cast<Creature*>(*i) -> setObjectsAround(
                    world -> getIndexator() -> getAreaContents(view_area));

                // check age
                if (dynamic_cast<Creature*>(*i) -> getAge() >=
                    dynamic_cast<Creature*>(*i) -> getMaxAge())
                {
                    destroy(*i);
                    continue;
                }
                // creatures can't do more than one action
                if (buf -> size())
                {
                    actions.push_back(&(buf -> at(0)));
                }
            }
            else 
            {
                // show weather what's under it
                if ((*i) -> getType() == WEATHER)
                {
                    dynamic_cast<Weather*>(*i) -> setCoveredObjects(
                            world -> getIndexator() -> getAreaContents(
                                dynamic_cast<Weather*>(*i) -> getShape()));
                }
                // collect all actions
                for (uint j = 0; j < buf -> size(); j++)
                {
                    actions.push_back(&(buf -> at(j)));
                }
            }
        }
    }

    // Swap buffers
    for (ObjectHeap::iterator i = hiddenToVisible.begin();
         i != hiddenToVisible.end(); i++)
    {
        world -> getHiddenObjects() -> remove(*i);
        world -> getVisibleObjects() -> push(*i);
        world -> getIndexator() -> addObject(*i);
    }

    for (ObjectHeap::iterator i = visibleToHidden.begin();
         i != visibleToHidden.end(); i++)
    {
        world -> getHiddenObjects() -> push(*i);
        world -> getVisibleObjects() -> remove(*i);
        world -> getIndexator() -> removeObject(*i);
    }

    // Execute actions
    for (uint i = 0; i < actions.size(); i++)
    {
        performers[actions[i] -> getType()] -> perform(*actions[i]);
    }
}
