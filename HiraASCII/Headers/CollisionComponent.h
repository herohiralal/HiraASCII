#pragma once

#include "Bounds.h"
#include "Vector2.h"
#include "Component.h"

class CollisionComponent final : public Component
{
public:
    explicit CollisionComponent(GameObject& InGo);
    ~CollisionComponent();

private:
    Vector2* CollisionOffsets = nullptr;
    unsigned Size = 0;

public:
    // Commands
    void SetCollision(Vector2* InCollisions, unsigned InSize);

    // Queries
    unsigned GetSize() const;
    Vector2 GetCollisionData(unsigned InIndex) const;
    Bounds GetColliderBounds() const;
};