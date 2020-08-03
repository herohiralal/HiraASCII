#pragma once
#include "../HiraASCII/Headers/Behaviour.h"
#include "../HiraASCII/Interfaces/IRequestCollisionCallback.h"

class World;

class Apple : public Behaviour, public IRequestCollisionCallback
{
public:
    explicit Apple(GameObject& InGo);
    static GameObject* Initialize(World& InWorld);
    void HandleCollisionWith(GameObject& InOther) override;
    void PostCollisionTick() override;

private:
    bool ScheduledToTeleport = false;
};
