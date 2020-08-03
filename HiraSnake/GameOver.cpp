#include "GameOver.h"


#include "../HiraASCII/Headers/GameObject.h"
#include "../HiraASCII/Headers/RendererComponent.h"
#include "../HiraASCII/Headers/World.h"

GameObject* GameOver::Initialize(World& InWorld)
{
    auto SpawnedGameObject = InWorld.SpawnGameObject("GameOver");
    SpawnedGameObject->AddComponent<RendererComponent>()->SetRenderData(
        ""
        " Game Over \n"
        "R - Restart\n"
        "Q - Quit :(", 5, 1);
    return SpawnedGameObject;
}
