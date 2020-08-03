#pragma once

#include "GameManager.h"
#include "../HiraASCII/Headers/Camera.h"
#include "../HiraASCII/Headers/GameObject.h"
#include "../HiraASCII/Headers/World.h"

int main(int InArgc, char* InArgv[])
{
    const auto CurrentWorld = new World();
    CurrentWorld->GetCamera()->SetHalfHeight(11);
    CurrentWorld->GetCamera()->SetHalfWidth(30);

    const auto CurrentGameManager = CurrentWorld->SpawnGameObject("Game Manager")->AddComponent<GameManager>();

    while (CurrentWorld->IsRunning())
    {
        CurrentWorld->Run(1);
        std::cout << "Current Score: " << CurrentGameManager->GetScore() << std::endl;
        if (CurrentGameManager->IsGameRunning()) std::cout << "Press Q to Quit." << std::endl;
    }

    delete CurrentWorld;

    return 0;
}
