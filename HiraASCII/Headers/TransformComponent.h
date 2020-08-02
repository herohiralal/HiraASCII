#pragma once

#include "Component.h"
#include "Vector2.h"

class TransformComponent : public Component
{
public:
    explicit TransformComponent(GameObject& InGo);
    virtual ~TransformComponent() = default;
private:
    Vector2 Position;
public:
    // Commands
    void SetPosition(Vector2 InPosition);
    void SetPosition(int InX, int InY);
    void Modify2D(int InX, int InY);
    void ModifyHorizontally(int InX);
    void ModifyVertically(int InY);

    // Queries
    Vector2 GetPosition() const;
};
