#include "../Headers/Component.h"
#include "../Headers/GameObject.h"

Component::Component(GameObject& InGo) : Owner(InGo)
{
}

void Component::Establish()
{
}

void Component::Decommission()
{
}

GameObject* Component::GetOwner() const
{
    return &Owner;
}

TransformComponent* Component::GetTransform() const
{
    return Owner.GetTransform();
}

bool Component::IsComponentABehaviour() const
{
    return false;
}

Behaviour* Component::AsBehaviour()
{
    return nullptr;
}

void Component::Destroy()
{
    MarkedForDestruction = true;
}

bool Component::IsMarkedForDestruction() const
{
    return MarkedForDestruction;
}
