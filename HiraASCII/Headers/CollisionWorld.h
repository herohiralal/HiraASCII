#pragma once
#include <vector>

class CollisionComponent;

class CollisionWorld
{
private:
    std::vector<CollisionComponent*> Colliders;

public:
    //Commands
    void RegisterCollider(CollisionComponent& InComponent);
    void DeregisterCollider(CollisionComponent& InComponent);

    void Run() const;

    //Queries

private:
    static void HandleCollisionsBetween(const CollisionComponent& InComponentFirst, const CollisionComponent& InComponentSecond);
    static bool AreCollidersColliding(const CollisionComponent& InComponentFirst, const CollisionComponent& InComponentSecond);
};
