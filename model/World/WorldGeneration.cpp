#include "World.h"
#include "../Utilities/Vector/Vector.h"
#include "Object/Resource/Resource.h"
#include "../../common/Math/Random.h"
#include "../../common/BasicTypes.h"
#include <cmath>

#define GEN_OCTAVES                 6
#define GEN_PERSISTENCE             1/4
#define GEN_AVERAGE_NOISE           50
#define GEN_FIVE_SIGMA              50
#define GEN_FRACTAL_POWER           4
#define GEN_MAP_RESOLUTION          0.5

#define GEN_TREE_INSIDE_BOUNDS      
#define GEN_TREE_LOWER_BOUND        65
#define GEN_TREE_UPPER_BOUND        100
#define GEN_TREE_DENSITY            0.5
#define GEN_TREE_INTERVAL           0.25

#define GEN_GRASS_INSIDE_BOUNDS     
#define GEN_GRASS_LOWER_BOUND       0
#define GEN_GRASS_UPPER_BOUND       35
#define GEN_GRASS_DENSITY           0.1
#define GEN_GRASS_INTERVAL          0.25

#define GEN_COW_INSIDE_BOUNDS       
#define GEN_COW_LOWER_BOUND         0
#define GEN_COW_UPPER_BOUND         35
#define GEN_COW_DENSITY             0.1
#define GEN_COW_INTERVAL            0.25

#define GEN_HUMAN_INSIDE_BOUNDS    
#define GEN_HUMAN_LOWER_BOUND       0
#define GEN_HUMAN_UPPER_BOUND       35
#define GEN_HUMAN_DENSITY           0.1
#define GEN_HUMAN_INTERVAL          0.25

#define GEN_DRAGON_INSIDE_BOUNDS    !
#define GEN_DRAGON_LOWER_BOUND      0
#define GEN_DRAGON_UPPER_BOUND      35
#define GEN_DRAGON_DENSITY          0.1
#define GEN_DRAGON_INTERVAL         0.25
// Perlin 2d noise.
// Code from:
// http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
double noise1(double x, double y, double s)
{
    int seed = x + y * 57 + s;
    seed = (seed << 13) ^ seed;
    return (1.0 -( (seed * (seed * seed * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double smoothNoise1(double x, double y, double s)
{
    double corners = (noise1(x - 1, y - 1, s) + noise1(x + 1, y - 1, s) + 
                      noise1(x - 1, y + 1, s) + noise1(x + 1, y + 1, s)) / 16;
    double sides   = (noise1(x - 1, y, s) + noise1(x + 1, y, s) +
                      noise1(x, y - 1, s) + noise1(x, y + 1, s)) /  8;
    double center  =  noise1(x, y, s) / 4;
    return corners + sides + center;
}

// Cosine interpolation.
double interpolate(double a, double b, double x)
{
    double ft = x * M_PI;
    double f = (1 - cos(ft)) * .5;

    return  a * (1 - f) + b * f;
}

double interpolateNoise1(double x, double y, double s)
{

    double int_x    = floor(x);
    double frac_x   = x - int_x;

    double int_y    = floor(y);
    double frac_y   = y - int_y;

    double v1 = smoothNoise1(int_x,     int_y,      s);
    double v2 = smoothNoise1(int_x + 1, int_y,      s);
    double v3 = smoothNoise1(int_x,     int_y + 1,  s);
    double v4 = smoothNoise1(int_x + 1, int_y + 1,  s);

    double i1 = interpolate(v1 , v2 , frac_x);
    double i2 = interpolate(v3 , v4 , frac_x);

    return interpolate(i1 , i2 , frac_y);
}

double perlinNoise2D(double x, double y, double seed)
{
    double total = 0;

    for (int i = 0; i < GEN_OCTAVES; i++)
    {
        double frequency = pow(2, i);
        double amplitude = pow(GEN_PERSISTENCE, i);
        total = total + interpolateNoise1(x * frequency, y * frequency, seed) * amplitude;
    }

    return total;
}

// Makes fractal map.
// Idea from here:
// http://freespace.virgin.net/hugo.elias/models/m_clouds.htm
double World::fractalPerlinNoise2D(double x, double y, double power, double seed)
{
    int k = 0;
    double value = 0;
    while (k < power)
    {
        value += perlinNoise2D(x, y, seed) / pow(2, k);
        x *= 2;
        y *= 2;
        if (x > size)
        {
            x -= size;
        }
        if (y > size)
        {
            y -= size;
        }
        k++;
    }
    return value;
}

void World::generateWorld()
{
    // Make worlds different
    double seed = Random::double_num(2 * size) - size;

    // Init analysis data
    uint analysis[10];
    for (uint i = 0; i < 10; i++)
    {
        analysis[i] = 0;
    }
    uint total = 0, max = 0, min = 1000, sum = 0;

    // Create resources.
    for (double x = GEN_MAP_RESOLUTION; x < size; x += GEN_MAP_RESOLUTION)
    {
        for (double y = GEN_MAP_RESOLUTION; y < size; y += GEN_MAP_RESOLUTION)
        {
            // Normalize.
            double value = fractalPerlinNoise2D(x, y, seed, GEN_FRACTAL_POWER) * 
                                        GEN_FIVE_SIGMA + GEN_AVERAGE_NOISE;

            if (GEN_TREE_INSIDE_BOUNDS(value > GEN_TREE_LOWER_BOUND && 
                                       value < GEN_TREE_UPPER_BOUND))
            {
                genObjectAt(Vector(x, y), GEN_TREE_INTERVAL, GEN_TREE_DENSITY,
                            RESOURCE, object_parameters[RESOURCE][TREE]);
            }
            else if (GEN_GRASS_INSIDE_BOUNDS(value > GEN_GRASS_LOWER_BOUND && 
                                             value < GEN_GRASS_UPPER_BOUND))
            {
                genObjectAt(Vector(x, y), GEN_GRASS_INTERVAL, GEN_GRASS_DENSITY,
                            RESOURCE, object_parameters[RESOURCE][GRASS]);
            }

            // Analize
            total++;
            sum += value;
            if (value < 100)
            {
                analysis[uint(value) / 10]++;
            }
            if (value > max)
            {
                max = value;
            }
            if (value < min)
            {
                min = value;
            }
        }
    }

    seed = Random::double_num(size * 2) - size;
    // Create creatures.
    for (double x = GEN_MAP_RESOLUTION; x < size; x += GEN_MAP_RESOLUTION)
    {
        for (double y = GEN_MAP_RESOLUTION; y < size; y += GEN_MAP_RESOLUTION)
        {
            double value = fractalPerlinNoise2D(x, y, seed, GEN_FRACTAL_POWER) * 
                                        GEN_FIVE_SIGMA + GEN_AVERAGE_NOISE;

            if (GEN_COW_INSIDE_BOUNDS(value > GEN_COW_LOWER_BOUND && 
                                      value < GEN_COW_UPPER_BOUND))
            {
                genObjectAt(Vector(x, y), GEN_COW_INTERVAL, GEN_COW_DENSITY,
                            CREATURE, object_parameters[CREATURE][COW], false);
            }
            else if (GEN_HUMAN_INSIDE_BOUNDS(value > GEN_HUMAN_LOWER_BOUND && 
                                             value < GEN_HUMAN_UPPER_BOUND))
            {
                genObjectAt(Vector(x, y), GEN_HUMAN_INTERVAL, GEN_HUMAN_DENSITY,
                            CREATURE, 
                            object_parameters[CREATURE][AMNT_NONHUMANOID_TYPES], false);
            }
            else if (GEN_DRAGON_INSIDE_BOUNDS(value > GEN_DRAGON_LOWER_BOUND &&
                                              value < GEN_DRAGON_UPPER_BOUND))
            {
                genObjectAt(Vector(x, y), GEN_DRAGON_INTERVAL, GEN_DRAGON_DENSITY,
                            CREATURE, object_parameters[CREATURE][DRAGON], false);
            }
        }
    }

    // Print analysis
    std::cout << "Analysis: Puasson ditribution. Total:" << total << std::endl;
    for (uint i = 0; i < 10; i++)
    {
        std::cout << i * 10 << '-' << (i + 1) * 10 << '\t' << analysis[i] << std::endl;
    }
    std::cout << "Max value: " << max << std::endl;
    std::cout << "Min value: " << min << std::endl;
    std::cout << "Average:"    << double(sum) / total << std::endl;
}
