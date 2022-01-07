#include "Vector.h"

Vec2 Vec2_Set(float x, float y)
{
    Vec2 v = { .x = x, .y = y };
    return v;
}

Vec2 Vec2_Perp(Vec2 v)
{
    return Vec2_Set(v.y, -v.x);
}

// TODO - Complétez le fichier

Vec2 Vec2_Add(Vec2 v1, Vec2 v2)
{
    return v1;
}

Vec2 Vec2_Sub(Vec2 v1, Vec2 v2)
{
    return v1;
}

Vec2 Vec2_Scale(Vec2 v, float s)
{
    return v;
}

float Vec2_Length(Vec2 v)
{
    return 0.0f;
}

Vec2 Vec2_Normalize(Vec2 v)
{
    return v;
}

float Vec2_Distance(Vec2 v1, Vec2 v2)
{
    return 0.0f;
}
