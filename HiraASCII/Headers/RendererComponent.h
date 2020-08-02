#pragma once

#include "Bounds.h"
#include "Component.h"
#include "RenderData.h"

class RendererComponent final : public Component
{
public:
    explicit RendererComponent(GameObject& InGo);
    ~RendererComponent();

private:
    RenderData* Data = nullptr;
    unsigned Size = 0;

public:
    // Commands
    void SetRenderData(RenderData* InRenderData, unsigned InSize);

    // Queries
    unsigned GetSize() const;
    Vector2 GetRenderPosition(unsigned InIndex) const;
    char GetRenderData(unsigned InIndex) const;
    Bounds GetRendererBounds() const;
};