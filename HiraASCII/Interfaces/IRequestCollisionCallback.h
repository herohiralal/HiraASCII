#pragma once

class GameObject;

class IRequestCollisionCallback
{
protected:
    ~IRequestCollisionCallback() = default;
public:
    virtual void HandleCollisionWith(GameObject& InOther) = 0;
};