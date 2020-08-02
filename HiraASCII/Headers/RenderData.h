#pragma once

#include "Vector2.h"

struct RenderData
{
public:
    explicit RenderData(Vector2 InPosition = Vector2(0, 0), char InDenotation = ' ');
    Vector2 Position;
    char Denotation;
};