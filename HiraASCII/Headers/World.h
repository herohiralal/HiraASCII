#pragma once
#include <string>
#include <vector>

class GameObject;
class CollisionWorld;
class RendererWorld;
class Camera;
class Input;

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
    Camera& CameraComponent;
    Input& InputComponent;

public:
    //Commands
    GameObject* SpawnGameObject(std::string InName = "New GameObject");
    void Quit();
    void PreCollisionTick() const;
    void PostCollisionTick() const;
    void GarbageCollect();
    void Run(int InFrameRate);

    //Queries
    GameObject* GetGameObject(std::string InName) const;
    std::vector<GameObject*> GetGameObjects(std::string InName) const;
    CollisionWorld* GetCollisionWorld() const;
    RendererWorld* GetRendererWorld() const;
    Camera* GetCamera() const;
    bool IsButtonPressed(char InLetter) const;
    bool IsRunning() const;
};
