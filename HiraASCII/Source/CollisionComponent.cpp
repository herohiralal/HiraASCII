#include "../Headers/CollisionComponent.h"
#include "../Headers/GameObject.h"
#include "../Headers/TransformComponent.h"
#include "../Headers/World.h"
#include "../Headers/CollisionWorld.h"

CollisionComponent::CollisionComponent(GameObject& InGo): Component(InGo)
{
    GetOwner()->GetWorld()->GetCollisionWorld()->RegisterCollider(*this);
}

CollisionComponent::~CollisionComponent()
{
    GetOwner()->GetWorld()->GetCollisionWorld()->DeregisterCollider(*this);
    delete[] CollisionOffsets;
}

void CollisionComponent::SetCollision(Vector2* InCollisions, const unsigned InSize)
{
    if (CollisionOffsets != nullptr)
    {
        delete[] CollisionOffsets;
        Size = 0;
    }

    CollisionOffsets = InCollisions;
    Size = InSize;
}

unsigned CollisionComponent::GetSize() const
{
    return Size;
}

Vector2 CollisionComponent::GetCollisionData(const unsigned InIndex) const
{
    if (InIndex >= Size) return Vector2();
    return CollisionOffsets[InIndex] + GetOwner()->GetTransform()->GetPosition();
}

Bounds CollisionComponent::GetColliderBounds() const
{
    auto RendererBounds = Bounds();

    const auto GameObjectPosition = GetOwner()->GetTransform()->GetPosition();

    for (unsigned I = 0; I < Size; I++)
    {
        RendererBounds.IncorporateIntoBoundsHorizontally(CollisionOffsets[I].X + GameObjectPosition.X);
        RendererBounds.IncorporateIntoBoundsVertically(CollisionOffsets[I].Y + GameObjectPosition.Y);
    }

    return RendererBounds;
}
