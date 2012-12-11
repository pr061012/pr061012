/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <jsoncpp/json/json.h>

#include "Texture/Texture.h"

class TextureManager
{
    Json::Reader* json_reader;

    std::map<std::string, Texture*> texture_buf;
    std::map<std::string, int> texture_num;
    std::map<std::string, int> xparts;
    std::map<std::string, int> yparts;

public:
    enum Rotation{UP, RIGHT, LEFT, DOWN};

    TextureManager(const std::string file);

    ~TextureManager();

    Texture* getTexture(std::string name, Rotation rotation = UP, int index = 0, int step = 0);
    Texture* getTexture(std::string name, double angle, int index = 0, int step = 0);
};

#endif // TEXTURE_MANAGER_H
