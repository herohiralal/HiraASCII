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
    bool Running = true;
    std::vector<GameObject*> GameObjects;
    unsigned NumberOfGameObjects = 0;
    CollisionWorld& CollisionWorldComponent;
    RendererWorld& RendererWorldComponent;
    bool* Input = new bool[26];

public:
    //Commands
    GameObject* SpawnGameObject(std::string InName = "New GameObject");
    void DespawnGameObject(GameObject& InTarget);
    void DespawnGameObject(std::string InName, bool InAll = false);
    void Quit();
    void PreCollisionTick() const;
    void PostCollisionTick() const;
    void Run();

    //Queries
    GameObject* GetGameObject(std::string InName) const;
    std::vector<GameObject*> GetGameObjects(std::string InName) const;
    CollisionWorld* GetCollisionWorld() const;
    RendererWorld* GetRendererWorld() const;
    bool IsRunning() const;
};
