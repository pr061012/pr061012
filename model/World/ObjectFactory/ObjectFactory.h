/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <string>
#include <map>

#include "../ParamArray/ParamArray.h"
#include "../Object/Object.h"
#include "../ObjectHeap/ObjectHeap.h"

/**
 * @class ObjectFactory
 * @brief Object factory allows to creates any objects (you need to provide
 *        ParamArray with parameters to do this).
 *
 *        To create object with type T first of all you need to provide
 *        parameter `obj_type`. Value of this param is ObjectType (converted to
 *        int). For each object type a few parameters more are needed.
 *
 *        **Common params**:
 *          * *x* -- x coordinate (double).
 *          * *y* -- y coordinate (double).
 *
 *        **Creature**
 *          * *creat_type* -- CreatureType.
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
 *        **Note**: * -- leave 0 to pick random value.
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
    ObjectFactory();

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

};

#endif // OBJECT_FACTORY_H
