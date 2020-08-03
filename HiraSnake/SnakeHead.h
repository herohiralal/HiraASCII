#pragma once

#include <vector>

#include "../HiraASCII/Headers/Behaviour.h"
#include "../HiraASCII/Headers/Vector2.h"
#include "../HiraASCII/Interfaces/IRequestCollisionCallback.h"

class World;

class SnakeHead : public Behaviour, public IRequestCollisionCallback
{
public:
    explicit SnakeHead(GameObject& InGo);
    static GameObject* Initialize(World& InWorld);
    void Establish() override;
    void Decommission() override;
    void PreCollisionTick() override;

private:
    Vector2 Direction;
    std::vector<GameObject*> BodyParts;
    std::vector<Vector2> EmptyPositions;
    bool ScheduledToExtend = false;

private:
    GameObject* CreateBodyPart();
    void Occupy(int InX, int InY);

public:
    void HandleCollisionWith(GameObject& InOther) override;
    Vector2 GetEmptyPosition() const;
};
