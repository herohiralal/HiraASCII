#include "Welcome.h"


#include "../HiraASCII/Headers/GameObject.h"
#include "../HiraASCII/Headers/RendererComponent.h"
#include "../HiraASCII/Headers/World.h"

GameObject* Welcome::Initialize(World& InWorld)
{
    auto SpawnedGameObject = InWorld.SpawnGameObject("Welcome");
    SpawnedGameObject->AddComponent<RendererComponent>()->SetRenderData(
        ""
        "   HiraSnake   \n"
        "\n"
        "\n"
        "Press P to Play\n"
        "Press Q to Quit", 7, 2);
    return SpawnedGameObject;
}
