#include "../Headers/RendererWorld.h"
#include "../Headers/Camera.h"
#include "../Headers/RendererComponent.h"

void RendererWorld::RegisterRenderer(RendererComponent& InComponent)
{
    Renderers.push_back(&InComponent);
}

void RendererWorld::DeregisterRenderer(RendererComponent& InComponent)
{
    for (auto I = Renderers.begin(); I != Renderers.end(); ++I)
    {
        if (*I == &InComponent)
        {
            Renderers.erase(I);
            return;
        }
    }
}

std::vector<RendererComponent*> RendererWorld::GetRenderersOnCamera(const Camera& InCamera) const
{
    auto RenderersOnCamera = std::vector<RendererComponent*>();

    for (auto Renderer : Renderers)
        if (InCamera.IntersectsWith(Renderer->GetRendererBounds()))
            RenderersOnCamera.push_back(Renderer);

    return RenderersOnCamera;
}
