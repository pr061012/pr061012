#include "World.h"
#include "../Utilities/Vector/Vector.h"
#include "Object/Resource/Resource.h"
#include "../../common/Math/Random.h"
#include "../../common/BasicTypes.h"
#include <cmath>

#define GEN_OCTAVES             6
#define GEN_PERSISTENCE         1/4
#define GEN_RESOURCE_DENSITY    0.75
#define GEN_LIFE_DENSITY        0.5

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

void World::generateWorld()
{
    uint analysis[10];
    double seed = Random::double_num(2 * size) - size;
    for (uint i = 0; i < 10; i++)
    {
        analysis[i] = 0;
    }

    uint total = 0, max = 0, min = 1000, sum = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // FRACTAL PERLIN NOISE!!!
            double a = i + 0.5;
            double b = j + 0.5;
            int k = 0;
            double value = 0;
            while (k < 4)
            {
                value += perlinNoise2D(a, b, seed) / pow(2, k);
                a *= 2;
                b *= 2;
                if (a > size)
                {
                    a -= size;
                }
                if (b > size)
                {
                    b -= size;
                }
                k++;
            }

            value = value* 50 + 50;
            double x = i + 0.5;
            double y = j + 0.5;

            /*Object * obj = createObject(RESOURCE, TREE, false, Vector(x, y));
            if (obj != nullptr)
            {
                dynamic_cast<Resource*>(obj) -> setMaxAmount(100);
                dynamic_cast<Resource*>(obj) -> damage(10000);
                dynamic_cast<Resource*>(obj) -> heal(value);
            }*/

            if (40 > value)
            {
                createObject(RESOURCE, TREE, false, Vector(x, y));
            }
            else if (value > 60)
            {
                createObject(RESOURCE, GRASS, false, Vector(x, y));
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
