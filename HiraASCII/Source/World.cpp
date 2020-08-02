#include "../Headers/World.h"
#include "../Headers/CollisionWorld.h"
#include "../Headers/GameObject.h"
#include "../Headers/RendererWorld.h"

World::World() : CollisionWorldComponent(*new CollisionWorld()), RendererWorldComponent(*new RendererWorld())
{
}

World::~World()
{
    delete &CollisionWorldComponent;
    delete &RendererWorldComponent;

    for (auto I = 0; I < GameObjects.size(); I++)
        delete GameObjects[I];
}

GameObject* World::SpawnGameObject(const std::string InName)
{
    const auto SpawnedGameObject = new GameObject(*this, InName);
    GameObjects.push_back(SpawnedGameObject);
    NumberOfGameObjects++;
    return SpawnedGameObject;
}

void World::DespawnGameObject(GameObject& InTarget)
{
    for (auto Current = GameObjects.begin(); Current != GameObjects.end(); ++Current)
    {
        if (*Current == &InTarget)
        {
            delete *Current;
            GameObjects.erase(Current);
            NumberOfGameObjects--;
            return;
        }
    }
}

void World::DespawnGameObject(const std::string InName, bool InAll)
{
    for (auto Current = GameObjects.begin(); Current != GameObjects.end(); ++Current)
    {
        if ((*Current)->GetName() == InName)
        {
            delete *Current;
            GameObjects.erase(Current);
            NumberOfGameObjects--;
            return;
        }
    }
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
