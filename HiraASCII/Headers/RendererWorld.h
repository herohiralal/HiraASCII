#pragma once
#include <vector>

class RendererComponent;
class Camera;

class RendererWorld
{
private:
    std::vector<RendererComponent*> Renderers;

public:
    // Commands
    void RegisterRenderer(RendererComponent& InComponent);
    void DeregisterRenderer(RendererComponent& InComponent);

    // Queries
    std::vector<RendererComponent*> GetRenderersOnCamera(const Camera& InCamera) const;
};
