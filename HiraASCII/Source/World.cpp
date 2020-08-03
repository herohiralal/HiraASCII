#include "../Headers/World.h"



#include <conio.h>
#include <ctime>
#include <windows.h>

#include "../Headers/Camera.h"
#include "../Headers/CollisionWorld.h"
#include "../Headers/GameObject.h"
#include "../Headers/Input.h"
#include "../Headers/RendererWorld.h"

World::World() : CollisionWorldComponent(*new CollisionWorld()), RendererWorldComponent(*new RendererWorld()),
                 CameraComponent(*new Camera()), InputComponent(*new Input())
{
}

World::~World()
{
    for (auto I = 0; I < GameObjects.size(); I++)
        delete GameObjects[I];

    delete &CollisionWorldComponent;
    delete &RendererWorldComponent;
    delete &CameraComponent;
    delete &InputComponent;
}

GameObject* World::SpawnGameObject(const std::string InName)
{
    const auto SpawnedGameObject = new GameObject(*this, InName);
    GameObjects.push_back(SpawnedGameObject);
    NumberOfGameObjects++;
    return SpawnedGameObject;
}

void World::Quit()
{
    Running = false;
}

void World::PreCollisionTick() const
{
    for(unsigned I = 0; I < NumberOfGameObjects; I++)
        GameObjects[I]->PreCollisionTick();
}

void World::PostCollisionTick() const
{
    for(unsigned I = 0; I < NumberOfGameObjects; I++)
        GameObjects[I]->PostCollisionTick();
}

void World::GarbageCollect()
{
    for(auto Iterator = GameObjects.begin(); Iterator != GameObjects.end();)
    {
        (*Iterator)->GarbageCollect();
        if((*Iterator)->IsMarkedForDestruction())
        {
            delete *Iterator;
            Iterator = GameObjects.erase(Iterator);
            NumberOfGameObjects--;
        }
        else ++Iterator;
    }
}

void World::Run(const int InFrameRate)
{
    InputComponent.ClearInput();
    const auto Delay = 1000.0 / static_cast<double>(InFrameRate);
    const auto Start = time(nullptr);

    Sleep(Delay);
    do InputComponent.AcceptInput();
    while (_kbhit());

    PreCollisionTick();
    CollisionWorldComponent.Run();
    PostCollisionTick();
    GarbageCollect();
    CameraComponent.Render(*this);
}

GameObject* World::GetGameObject(const std::string InName) const
{
    for (auto GameObject : GameObjects)
        if (GameObject->GetName() == InName)
            return GameObject;

    return nullptr;
}

std::vector<GameObject*> World::GetGameObjects(std::string InName) const
{
    auto TargetGameObjects = std::vector<GameObject*>();

    for (auto GameObject : GameObjects)
        if (GameObject->GetName() == InName)
            TargetGameObjects.push_back(GameObject);

    return TargetGameObjects;
}

CollisionWorld* World::GetCollisionWorld() const
{
    return &CollisionWorldComponent;
}

RendererWorld* World::GetRendererWorld() const
{
    return &RendererWorldComponent;
}

Camera* World::GetCamera() const
{
    return &CameraComponent;
}

bool World::IsButtonPressed(const char InLetter) const
{
    return InputComponent.IsButtonPressed(InLetter);
}

bool World::IsRunning() const
{
    return Running;
}
