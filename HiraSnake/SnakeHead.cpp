#include "SnakeHead.h"


#include "GameManager.h"
#include "../HiraASCII/Headers/CollisionComponent.h"
#include "../HiraASCII/Headers/GameObject.h"
#include "../HiraASCII/Headers/RendererComponent.h"
#include "../HiraASCII/Headers/TransformComponent.h"
#include "../HiraASCII/Headers/World.h"

SnakeHead::SnakeHead(GameObject& InGo): Behaviour(InGo)
{
}

GameObject* SnakeHead::Initialize(World& InWorld)
{
    auto SpawnedGameObject = InWorld.SpawnGameObject("Snake Head");
    SpawnedGameObject->AddComponent<RendererComponent>()->SetRenderData("H", 0, 0);
    SpawnedGameObject->AddComponent<CollisionComponent>()->SetCollision("+", 0, 0);
    auto Head = SpawnedGameObject->AddComponent<SnakeHead>();
    const auto FirstBodyPart = Head->CreateBodyPart();
    FirstBodyPart->GetTransform()->SetPosition(0, -1);
    Head->EmptyPositions.resize(1239);
    for (auto X = -29; X < 30; X++)
        for (auto Y = 10; Y > -11; Y--)
            Head->EmptyPositions.push_back(Vector2(X, Y));
    Head->Occupy(0, 0);
    Head->Occupy(0, -1);
    return SpawnedGameObject;
}

void SnakeHead::Establish()
{
    Direction.Set(0, 1);
}

void SnakeHead::Decommission()
{
    for (const auto BodyPart : BodyParts)
        BodyPart->Destroy();
}

void SnakeHead::PreCollisionTick()
{
    if (Direction.X && GetOwner()->GetWorld()->IsButtonPressed('W'))
        Direction.Set(0, 1);
    else if (Direction.Y && GetOwner()->GetWorld()->IsButtonPressed('A'))
        Direction.Set(-1, 0);
    else if (Direction.X && GetOwner()->GetWorld()->IsButtonPressed('S'))
        Direction.Set(0, -1);
    else if (Direction.Y && GetOwner()->GetWorld()->IsButtonPressed('D'))
        Direction.Set(1, 0);

    // if (GetOwner()->GetWorld()->IsButtonPressed('G'))
    //     CreateBodyPart();

    auto Position = GetTransform()->GetPosition();
    const auto NewPosition = Position + Direction;
    GetTransform()->SetPosition(NewPosition);
    Occupy(NewPosition.X, NewPosition.Y);

    for (auto BodyPart : BodyParts)
    {
        const auto OriginalPosition = BodyPart->GetTransform()->GetPosition();
        BodyPart->GetTransform()->SetPosition(Position);
        Position.Set(OriginalPosition.X, OriginalPosition.Y);
    }

    if (ScheduledToExtend)
    {
        const auto CreatedPart = CreateBodyPart();
        CreatedPart->GetTransform()->SetPosition(Position);
        ScheduledToExtend = false;
    }
    else
    {
        EmptyPositions.push_back(Position);
    }
}

GameObject* SnakeHead::CreateBodyPart()
{
    auto BodyPart = GetOwner()->GetWorld()->SpawnGameObject("Snake Body");
    BodyPart->AddComponent<RendererComponent>()->SetRenderData("S", 0, 0);
    BodyPart->AddComponent<CollisionComponent>()->SetCollision("+", 0, 0);
    BodyParts.push_back(BodyPart);
    return BodyPart;
}

void SnakeHead::Occupy(const int InX, const int InY)
{
    for (auto Iterator = EmptyPositions.begin(); Iterator != EmptyPositions.end();)
    {
        if ((*Iterator).X == InX && (*Iterator).Y == InY)
        {
            Iterator = EmptyPositions.erase(Iterator);
            return;
        }
        else ++Iterator;
    }
}

void SnakeHead::HandleCollisionWith(GameObject& InOther)
{
    if (InOther.GetName() == "Border" || InOther.GetName() == "Snake Body")
    {
        GetOwner()->GetWorld()->GetGameObject("Game Manager")->GetComponent<GameManager>()->DeclareGameOver();
        return;
    }

    if(InOther.GetName() == "Apple")
        ScheduledToExtend = true;
}

Vector2 SnakeHead::GetEmptyPosition() const
{
    return EmptyPositions[(rand() % EmptyPositions.size())];
}
