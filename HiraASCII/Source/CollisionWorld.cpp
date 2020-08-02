#include "../Headers/CollisionWorld.h"
#include "../Headers/CollisionComponent.h"
#include "../Headers/GameObject.h"
#include "../Interfaces/IRequestCollisionCallback.h"

void CollisionWorld::RegisterCollider(CollisionComponent& InComponent)
{
    Colliders.push_back(&InComponent);
}

void CollisionWorld::DeregisterCollider(CollisionComponent& InComponent)
{
    for (auto I = Colliders.begin(); I != Colliders.end(); ++I)
    {
        if (*I == &InComponent)
        {
            Colliders.erase(I);
            return;
        }
    }
}

void CollisionWorld::Run() const
{
    const auto NumberOfColliders = static_cast<int>(Colliders.size());

    const auto ColliderBounds = new Bounds[NumberOfColliders];

    for (auto Index = 0; Index < NumberOfColliders; Index++)
        ColliderBounds[Index] = Colliders[Index]->GetColliderBounds();

    for (auto TargetIndex = 0; TargetIndex < NumberOfColliders; TargetIndex++)
        for (auto QueryIndex = TargetIndex + 1; QueryIndex < NumberOfColliders; QueryIndex++)
        {
            if (!ColliderBounds[TargetIndex].DoesNotIntersectHorizontallyWith(ColliderBounds[QueryIndex]))
            {
                if (AreCollidersColliding(*Colliders[TargetIndex], *Colliders[QueryIndex]))
                    HandleCollisionsBetween(*Colliders[TargetIndex], *Colliders[QueryIndex]);
            }
        }

    delete[] ColliderBounds;
}

void CollisionWorld::HandleCollisionsBetween(const CollisionComponent& InComponentFirst,
                                             const CollisionComponent& InComponentSecond)
{
    // For first
    const auto FirstGameObjectsCollisionCallbackRequesters =
        InComponentFirst.GetOwner()->GetComponents<IRequestCollisionCallback>();

    for (auto CallbackRequester : FirstGameObjectsCollisionCallbackRequesters)
        CallbackRequester->HandleCollisionWith(*InComponentSecond.GetOwner());

    // For second
    const auto SecondGameObjectsCollisionCallbackRequesters =
        InComponentSecond.GetOwner()->GetComponents<IRequestCollisionCallback>();

    for (auto CallbackRequester : SecondGameObjectsCollisionCallbackRequesters)
        CallbackRequester->HandleCollisionWith(*InComponentFirst.GetOwner());
}

bool CollisionWorld::AreCollidersColliding(const CollisionComponent& InComponentFirst,
                                           const CollisionComponent& InComponentSecond)
{
    const auto FirstComponentSize = InComponentFirst.GetSize();
    const auto SecondComponentSize = InComponentSecond.GetSize();

    const auto SecondCollider = new Vector2[SecondComponentSize];

    for (unsigned Index = 0; Index < SecondComponentSize; Index++)
        SecondCollider[Index] = InComponentSecond.GetCollisionData(Index);

    for (unsigned FirstIndex = 0; FirstIndex < FirstComponentSize; FirstIndex++)
    {
        for (auto SecondIndex = FirstIndex + 1; SecondIndex < SecondComponentSize; SecondIndex++)
        {
            if (InComponentFirst.GetCollisionData(FirstIndex).IsEqualTo(SecondCollider[SecondIndex]))
            {
                delete[] SecondCollider;
                return true;
            }
        }
    }

    delete[] SecondCollider;
    return false;
}
