#include "../Headers/TransformComponent.h"
#include "../Headers/Vector2.h"

TransformComponent::TransformComponent(GameObject& InGo): Component(InGo), Position(Vector2(0, 0))
{
}

Vector2 TransformComponent::GetPosition() const
{
    return Position;
}

void TransformComponent::SetPosition(const Vector2 InPosition)
{
    Position.X = InPosition.X;
    Position.Y = InPosition.Y;
}

void TransformComponent::SetPosition(const int InX, const int InY)
{
    Position.X = InX;
    Position.Y = InY;
}

void TransformComponent::Modify2D(const int InX, const int InY)
{
    Position.X += InX;
    Position.Y += InY;
}

void TransformComponent::ModifyHorizontally(const int InX)
{
    Position.X += InX;
}

void TransformComponent::ModifyVertically(const int InY)
{
    Position.Y += InY;
}