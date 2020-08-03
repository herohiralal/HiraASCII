#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Behaviour.h"

class Component;
class Behaviour;
class TransformComponent;
class World;

class GameObject
{
public:
    explicit GameObject(World& InWorld, std::string InName = "New GameObject");
    ~GameObject();

private:
    World& World;
    std::string Name;
    std::vector<Component*> Components;
    TransformComponent& Transform;

public:
    // Commands
    template <typename T>
    T* AddComponent(bool InAutoActivate = true);
    template <typename T>
    void RemoveComponent(bool InAll = false);
    void PreCollisionTick();
    void PostCollisionTick();

    // Queries
    ::World* GetWorld() const;
    std::string GetName() const;
    TransformComponent* GetTransform() const;
    template <typename T>
    T* GetComponent() const;
    template <typename T>
    std::vector<T*> GetComponents() const;
};

template <typename T>
T* GameObject::GetComponent() const
{
    for (auto I = 0; I != Components.size(); I++)
    {
        T* PotentialReturn = dynamic_cast<T*>(Components[I]);
        if (PotentialReturn != nullptr)
        {
            return PotentialReturn;
        }
    }

    return nullptr;
}

template <typename T>
std::vector<T*> GameObject::GetComponents() const
{
    auto TargetComponents = std::vector<T*>();

    for (auto I = 0; I != Components.size(); I++)
    {
        T* PotentialComponent = dynamic_cast<T*>(Components[I]);
        if (PotentialComponent != nullptr) TargetComponents.push_back(PotentialComponent);
    }

    return TargetComponents;
}

template <typename T>
T* GameObject::AddComponent(const bool InAutoActivate)
{
    T* PotentialComponent = new T(*this);
    auto NewComponent = dynamic_cast<Component*>(PotentialComponent);
    if (NewComponent != nullptr)
    {
        Components.push_back(NewComponent);

        NewComponent->Establish();

        if (NewComponent->IsComponentABehaviour())
            NewComponent->AsBehaviour()->SetActivation(InAutoActivate);

        return PotentialComponent;
    }

    delete PotentialComponent;
    return nullptr;
}

template <typename T>
void GameObject::RemoveComponent(const bool InAll)
{
    for (auto Current = Components.begin() + 1; Current != Components.end(); ++Current)
    {
        T* PotentialObject = dynamic_cast<T*>(*Current);

        if (PotentialObject != nullptr)
        {
            if ((*Current)->IsComponentABehaviour())
                (*Current)->AsBehaviour()->Deactivate();

            (*Current)->Decommission();

            delete *Current;

            Components.erase(Current--);

            if (!InAll) return;
        }
    }
}