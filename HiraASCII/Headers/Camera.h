#pragma once

#include "Vector2.h"
#include "Bounds.h"

class Camera
{
public:
    Camera();
    Camera(int InHorizontalCenter, int InVerticalCenter, unsigned InHalfWidth, unsigned InHalfHeight);
    ~Camera();
private:
    Vector2 Center;

    unsigned HalfWidth;
    unsigned HalfHeight;
    
    Bounds Scope;

public:
    // Commands
    void SetCenter(int InHorizontalCenter, int InVerticalCenter);
    void SetHalfWidth(unsigned InHalfWidth);
    void SetHalfHeight(unsigned InHalfHeight);

    // Queries
    bool IntersectsWith(Bounds InTarget) const;
    bool IsPointInScope(Vector2 InTarget) const;

private:
    // Internal calculations
    void CalculateHorizontalPoints();
    void CalculateVerticalPoints();
};
