#include "../Headers/GameObject.h"
#include "../Headers/Behaviour.h"
#include "../Headers/TransformComponent.h"

GameObject::GameObject(::World& InWorld, const std::string InName) : World(InWorld),
                                                                     Name(InName),
                                                                     Transform(*AddComponent<TransformComponent>(true))
{
}

GameObject::~GameObject()
{
    for (auto Component : Components)
    {
        if(Component->IsComponentABehaviour())
            static_cast<Behaviour*>(Component)->Deactivate();
        Component->Decommission();
        delete Component;
    }
}

::World* GameObject::GetWorld() const
{
    return &World;
}

std::string GameObject::GetName() const
{
    return Name;
}

TransformComponent* GameObject::GetTransform() const
{
    return &Transform;
}
