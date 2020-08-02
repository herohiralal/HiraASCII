#include "../Headers/RendererComponent.h"
#include "../Headers/GameObject.h"
#include "../Headers/TransformComponent.h"
#include "../Headers/World.h"
#include "../Headers/RendererWorld.h"

RendererComponent::RendererComponent(GameObject& InGo): Component(InGo)
{
    GetOwner()->GetWorld()->GetRendererWorld()->RegisterRenderer(*this);
}

RendererComponent::~RendererComponent()
{
    GetOwner()->GetWorld()->GetRendererWorld()->DeregisterRenderer(*this);
    delete[] Data;
}

void RendererComponent::SetRenderData(RenderData* InRenderData, const unsigned InSize)
{
    if (Data != nullptr)
    {
        delete[] Data;
        Size = 0;
    }

    Data = InRenderData;
    Size = InSize;
}

unsigned RendererComponent::GetSize() const
{
    return Size;
}

Vector2 RendererComponent::GetRenderPosition(const unsigned InIndex) const
{
    if (InIndex >= Size) return Vector2();
    return Data[InIndex].Position + GetOwner()->GetTransform()->GetPosition();
}

char RendererComponent::GetRenderData(const unsigned InIndex) const
{
    if (InIndex >= Size) return ' ';
    return Data[InIndex].Denotation;
}

Bounds RendererComponent::GetRendererBounds() const
{
    auto RendererBounds = Bounds();

    const auto GameObjectPosition = GetOwner()->GetTransform()->GetPosition();

    for (unsigned I = 0; I < Size; I++)
    {
        RendererBounds.IncorporateIntoBoundsHorizontally(Data[I].Position.X + GameObjectPosition.X);
        RendererBounds.IncorporateIntoBoundsVertically(Data[I].Position.Y + GameObjectPosition.Y);
    }

    return RendererBounds;
}
