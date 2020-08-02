#pragma once

#include "Component.h"

class GameObject;

class Behaviour : public Component
{
public:
    explicit Behaviour(GameObject& InGo);
    
    virtual ~Behaviour() = default;
    
private:
    bool Activated = false;
    
public:
    inline bool IsComponentABehaviour() const final;

    inline Behaviour* AsBehaviour() final;

    inline bool IsActivated() const;
    
    void SetActivation(bool InValue);

    virtual void Activate();

    virtual void Deactivate();

    virtual void PreCollisionCallbackTick();

    virtual void PostCollisionCallbackTick();
};