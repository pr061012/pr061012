#include "TextureManager.h"
#include "../../common/Log/Log.h"

TextureManager::TextureManager(const std::string file)
{
    std::fstream config(file);

    Json::Value json_data;

    json_reader = new Json::Reader();
    json_reader -> parse(config, json_data);

    if (json_data.isMember("textures"))
    {
        Json::Value textures = json_data.get("textures", 0);

        if (textures.isArray())
        {
            uint size = textures.size();

            for (uint i = 0; i < size; ++i)
            {
                const Json::Value& tex = textures[i];
                std::string name = tex.get("name", "default").asString();
                std::string path = "res/images/" + tex.get("file", "").asString();

                uint flags = SOIL_FLAG_INVERT_Y;

                if (tex.get("alpha", false).asBool())
                {
                    flags |= SOIL_FLAG_MULTIPLY_ALPHA;
                }
                if (tex.get("repeatable", false).asBool())
                {
                    flags |= SOIL_FLAG_TEXTURE_REPEATS;
                }

                Texture* view_tex = new Texture(path.c_str(), flags,
                                                tex.get("x0",     0.0).asDouble(),
                                                tex.get("y0",     0.0).asDouble(),
                                                tex.get("width",  1.0).asDouble(),
                                                tex.get("height", 1.0).asDouble());

                Log::NOTE("Loaded texture '" + name + "' at " + path + ".");

                if (texture_num.find(name) == texture_num.end())
                {
                    texture_num[name] = 0;
                }

                texture_num[name]++;

                name += "_" + std::to_string(texture_num[name] - 1);
                texture_buf[name] = view_tex;

                xparts[name] = tex.get("xparts", 1).asInt();
                yparts[name] = tex.get("yparts", 1).asInt();
            }
        }
    }
}

TextureManager::~TextureManager()
{
    std::map<std::string, Texture*>::const_iterator iter;
    for (iter = texture_buf.begin(); iter != texture_buf.end(); iter++)
    {
        delete iter -> second;
    }

    delete json_reader;
}

Texture* TextureManager::getTexture(std::string name, Rotation rotation, int index, int step)
{
    std::map<std::string, int>::const_iterator len_iter = texture_num.find(name);

    int len;
    if(len_iter == texture_num.end())
    {
        Log::ERROR("Texture " + name + " is not loaded.");
        return NULL;
    }

    len = len_iter -> second;
    index = index % len;

//    if(name == "Human")std::cout << len << "||" << index << std::endl;
    name += "_" + std::to_string(index);

    Texture* tex = texture_buf.find(name) -> second;

    tex -> resetTextureDimensions();

    step    %= xparts[name];
    rotation = (Rotation)((int)rotation % yparts[name]);

    double width  = tex -> getWidth()  / xparts[name];
    double height = tex -> getHeight() / yparts[name];
    double x = tex -> getX() + width * step;
    double y = tex -> getY() + height * rotation;

    tex -> setTextureDimensions(x, y, width, height);


    return tex;
}
