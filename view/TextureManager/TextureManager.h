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
#include <jsoncpp/json/json.h>

#include "Texture/Texture.h"

class TextureManager
{
    Json::Reader* json_reader;

    std::map<std::string, Texture*> texture_buf;
    std::map<std::string, int> texture_num;

public:
    TextureManager(const std::string file);

    ~TextureManager();

    Texture* getTexture(std::string name, int index = 0, int step = 0) const;

};

#endif // TEXTURE_MANAGER_H
