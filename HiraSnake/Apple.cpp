#include "Apple.h"


#include "GameManager.h"
#include "SnakeHead.h"
#include "../HiraASCII/Headers/CollisionComponent.h"
#include "../HiraASCII/Headers/GameObject.h"
#include "../HiraASCII/Headers/RendererComponent.h"
#include "../HiraASCII/Headers/TransformComponent.h"
#include "../HiraASCII/Headers/World.h"

Apple::Apple(GameObject& InGo): Behaviour(InGo)
{
}

GameObject* Apple::Initialize(World& InWorld)
{
    auto AppleGameObject = InWorld.SpawnGameObject("Apple");
    AppleGameObject->AddComponent<RendererComponent>()->SetRenderData(
        "O", 0, 0);
    AppleGameObject->AddComponent<CollisionComponent>()->SetCollision(
        "+", 0, 0);
    AppleGameObject->AddComponent<Apple>();
    AppleGameObject->GetTransform()->SetPosition(0, 5);
    return AppleGameObject;
}

void Apple::HandleCollisionWith(GameObject& InOther)
{
    if (InOther.GetName() == "Snake Head")
    {
        GetOwner()->GetWorld()->GetGameObject("Game Manager")->GetComponent<GameManager>()->ReportAppleEaten();
        ScheduledToTeleport = true;
    }
}

void Apple::PostCollisionTick()
{
    if (ScheduledToTeleport)
    {
        GetOwner()->GetTransform()->SetPosition(
            GetOwner()->GetWorld()->GetGameObject("Snake Head")->GetComponent<SnakeHead>()->GetEmptyPosition());
        ScheduledToTeleport = false;
    }
}
