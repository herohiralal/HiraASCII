#pragma once

#include "Vector2.h"
#include "Bounds.h"

class World;
class RendererComponent;

class Camera
{
public:
    explicit Camera(int InHorizontalCenter = 0, int InVerticalCenter = 0, unsigned InHalfWidth = 20, unsigned InHalfHeight = 11);
    ~Camera();
private:
    Vector2 Center;

    unsigned HalfWidth;
    unsigned HalfHeight;
    
    Bounds Scope;

    char** Buffer;

public:
    // Commands
    void SetCenter(int InHorizontalCenter, int InVerticalCenter);
    void SetHalfWidth(unsigned InHalfWidth);
    void SetHalfHeight(unsigned InHalfHeight);
    void Render(const World& InWorld) const;

    // Queries
    bool IntersectsWith(const Bounds& InTarget) const;
    bool IsPointInScope(const Vector2& InTarget) const;

private:
    // Internal calculations
    void CalculateHorizontalPoints();
    void CalculateVerticalPoints();
    void DrawRenderer(const RendererComponent& InRenderer) const;
    void RecalculateBuffer();
    void DestroyBuffer() const;
    void DrawBuffer() const;
    void ClearBuffer() const;
};
