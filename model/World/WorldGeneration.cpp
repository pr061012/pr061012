#include "World.h"

#define GEN_OCTAVES 10
#define GEN_PERSISTENCE 1/4

// Perlin 2d noise.
// Code from:
// http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
double noise1(double x, double y)
{
    seed = x + y * 57;
    seed = (seed << 13) ^ seed;
    return ( 1.0 - ( (seed * (seed * seed * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double smoothNoise1(double x, double y)
{
    double corners = (noise1(x - 1, y - 1) + noise1(x + 1, y - 1) + 
                      noise1(x - 1, y + 1) + noise1(x + 1, y + 1)) / 16;
    double sides   = (noise1(x - 1, y) + noise1(x + 1, y) +
                      noise1(x, y - 1) + noise1(x, y + 1)) /  8;
    double center  =  noise1(x, y) / 4;
    return corners + sides + center;
}

// Cosine interpolation.
double interpolate(double a, double b, double x)
{
    double ft = x * M_PI;
    double f = (1 - cos(ft)) * .5

    return  a * (1 - f) + b * f
}

double interpolateNoise1(double x, double y)
{

    double int_x    = floor(x);
    double frac_x   = x - int_x;

    double int_y    = floor(y);
    double frac_y   = y - int_y;

    double v1 = smoothNoise1(int_x,     int_y);
    double v2 = smoothNoise1(int_x + 1, int_y)
    double v3 = smoothNoise1(int_x,     int_y + 1)
    double v4 = smoothNoise1(int_x + 1, int_y + 1)

    double i1 = interpolate(v1 , v2 , fractional_X)
    double i2 = interpolate(v3 , v4 , fractional_X)

    return interpolate(i1 , i2 , fractional_Y)
}

double perlinNoise2D(double x, double y)
{
    double total = 0

    for (int i = 0; i < GEN_OCTAVES; i++)
    {
        frequency = power(2, i);
        amplitude = power(GEN_PERSISTENCE, i);
        total = total + interpolatNoise1(x * frequency, y * frequency) * amplitude;
    }

    return total;
}

void World::generateWorld()
{
    for (double x = 0.5; x < size; x++)
    {
        for (double y = 0.5; y < size; y++)
        {
            double value = perlinNoise2D(x, y);
            if (value > 0.95)
        }
    }
}
