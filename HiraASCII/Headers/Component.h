#pragma once

class GameObject;
class Behaviour;
class TransformComponent;

class Component
{
public:
    explicit Component(GameObject& InGo);

    virtual ~Component() = default;
    
private:
    GameObject& Owner;
    bool MarkedForDestruction = false;
    
public:
    virtual void Establish();

    virtual void Decommission();
    
    GameObject* GetOwner() const;

    TransformComponent* GetTransform() const;
    
    inline virtual bool IsComponentABehaviour() const;

    inline virtual Behaviour* AsBehaviour();
    inline void Destroy();
    bool IsMarkedForDestruction() const;
};
