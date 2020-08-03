#include "../Headers/Behaviour.h"

Behaviour::Behaviour(GameObject& InGo) : Component(InGo)
{
}

bool Behaviour::IsComponentABehaviour() const
{
    return true;
}

Behaviour* Behaviour::AsBehaviour()
{
    return this;
}

bool Behaviour::IsActivated() const
{
    return Activated;
}

void Behaviour::SetActivation(const bool InValue)
{
    if (!Activated && InValue)
    {
        Activated = true;
        Activate();
    }
    else if (Activated && !InValue)
    {
        Activated = false;
        Deactivate();
    }
    else Activated = InValue;
}

void Behaviour::Activate()
{
}

void Behaviour::Deactivate()
{
}

void Behaviour::PreCollisionTick()
{
}

void Behaviour::PostCollisionTick()
{
}
