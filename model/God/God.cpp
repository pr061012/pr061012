/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include "God.h"
#include "../World/Action/Action.h"
#include "../../common/BasicDefines.h"
#include "../../common/BasicTypes.h"
#include "../../common/Math/Random.h"

//******************************************************************************
// CONSTRUCTOR/DESTRUCTOR.
//******************************************************************************

God::God(World& world):
    world(world)
{

}

God::~God()
{

}

void God::setWeatherAt(Vector x, WeatherType type)
{
    actions.clear();

    Action act(CREATE_OBJ, nullptr);
    act.addParam<Vector>("coord", x);
    act.addParam<WeatherType>("weat_type", type);
    uint weat_steps = Random::double_num(WEAT_STEPS_MIN, WEAT_STEPS_MAX);
    act.addParam<uint>("weat_steps", weat_steps);

    actions.push_back(act);
}
