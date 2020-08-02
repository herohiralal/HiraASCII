#include "../Headers/RendererWorld.h"

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
            Renderers.erase(I--);
            return;
        }
    }
}

std::vector<RendererComponent*> RendererWorld::GetRenderersOnCamera(const Camera& InCamera) const
{
    
}
