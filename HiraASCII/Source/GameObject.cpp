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
        if (Component->IsComponentABehaviour())
            static_cast<Behaviour*>(Component)->Deactivate();
        Component->Decommission();
        delete Component;
    }
}

void GameObject::PreCollisionTick()
{
    for (auto Component : Components)
        if (Component->IsComponentABehaviour())
            if (Component->AsBehaviour()->IsActivated())
                Component->AsBehaviour()->PreCollisionTick();
}

void GameObject::PostCollisionTick()
{
    for (auto Component : Components)
        if (Component->IsComponentABehaviour())
            if (Component->AsBehaviour()->IsActivated())
                Component->AsBehaviour()->PostCollisionTick();
}

void GameObject::Destroy()
{
    MarkedForDestruction = true;
}

void GameObject::GarbageCollect()
{
    for(auto Iterator = Components.begin();Iterator!=Components.end();)
    {
        if((*Iterator)->IsMarkedForDestruction())
        {
            if ((*Iterator)->IsComponentABehaviour())
                (*Iterator)->AsBehaviour()->Deactivate();
            
            (*Iterator)->Decommission();
            
            delete *Iterator;
            
            Iterator = Components.erase(Iterator);
        }
        else ++Iterator;
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

bool GameObject::IsMarkedForDestruction() const
{
    return MarkedForDestruction;
}
