/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <string>
#include <map>

#include "../DecisionMaker/DecisionMaker.h"
#include "../Object/Object.h"
#include "../ObjectHeap/ObjectHeap.h"
#include "../../../common/ParamArray/ParamArray.h"

/**
 * @class ObjectFactory
 * @brief Object factory allows to creates any objects (you need to provide
 *        ParamArray with parameters to do this).
 *
 *        To create object with type T first of all you need to provide
 *        parameter `obj_type`. Value of this param is ObjectType (converted to
 *        int). For each object type a few parameters more are needed.
 *
 *        **Creature**
 *          * *creat_type* -- CreatureType.
 *          * *nhum_type* -- NonHumanoidType (only for NonHumanoid).
 *
 *        **Building**
 *          * *max_health* -- Building health (uint).
 *          * *max_space* -- Building space (uint).
 *
 *        **Resource**
 *          * *res_type* -- ResourceType.
 *          * *res_amount* -- amount of resource (uint) (*).
 *
 *        **Tool**
 *          * *tool_type* -- ToolType.
 *          * *mat_type* -- ResourceType of material.
 *          * *tool_str* -- Tool's strength (uint) (*).
 *
 *        **Weather**
 *          * *weat_type* -- WeatherType.
 *          * *weat_steps* -- amount of steps that Weather will live (uint) (*).
 *
 *        **Note**: * -- optional fields, don't add them to pick random value.
 */
class ObjectFactory
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    ObjectFactory(const DecisionMaker& hum_dmaker,
                  const DecisionMaker& nhum_dmaker);

    /**
     * @brief Destructor.
     */
    ~ObjectFactory();

    //**************************************************************************
    // OBJECTS CREATION.
    //**************************************************************************

    /**
     * @brief  Creates new object.
     * @param  type     object type
     * @param  params   map with object params
     * @return pointer to created object
     */
    Object * createObject(ObjectType type, const ParamArray & params);

private:
    //**************************************************************************
    // OBJECTS CREATION (INNER METHODS).
    //**************************************************************************

    /**
     * @brief  Creates building.
     * @param  params  map with object params
     * @return pointer to created building
     */
    Object * createBuilding(const ParamArray & params);

    /**
     * @brief  Creates creature.
     * @param  params  map with object params
     * @return pointer to created creature
     */
    Object * createCreature(const ParamArray & params);

    /**
     * @brief  Creates resource.
     * @param  params  map with object params
     * @return pointer to created resource
     */
    Object * createResource(const ParamArray & params);

    /**
     * @brief  Creates tool.
     * @param  params  map with object params
     * @return pointer to created tool
     */
    Object * createTool(const ParamArray & params);

    /**
     * @brief  Creates weather.
     * @param  params  map with object params
     * @return pointer to created weather
     */
    Object * createWeather(const ParamArray & params);

    //**************************************************************************
    // DECISION MAKERS.
    //**************************************************************************

    /// Humanoid decision maker.
    const DecisionMaker& hum_dmaker;

    /// NonHumanoid decision maker.
    const DecisionMaker& nhum_dmaker;
};

#endif // OBJECT_FACTORY_H
