#pragma once
#include <string>
#include <vector>

class GameObject;
class CollisionWorld;
class RendererWorld;

class World
{
public:
    World();
    ~World();
    
private:
    std::vector<GameObject*> GameObjects;
    unsigned NumberOfGameObjects = 0;
    CollisionWorld& CollisionWorldComponent;
    RendererWorld& RendererWorldComponent;

public:
    //Commands
    GameObject* SpawnGameObject(std::string InName = "New GameObject");
    void DespawnGameObject(GameObject& InTarget);
    void DespawnGameObject(std::string InName, bool InAll = false);

    //Queries
    GameObject* GetGameObject(std::string InName) const;
    std::vector<GameObject*> GetGameObjects(std::string InName) const;
    CollisionWorld* GetCollisionWorld() const;
    RendererWorld* GetRendererWorld() const;
};
