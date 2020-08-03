#include "GameManager.h"


#include "Apple.h"
#include "Border.h"
#include "GameOver.h"
#include "SnakeHead.h"
#include "Welcome.h"
#include "../HiraASCII/Headers/GameObject.h"
#include "../HiraASCII/Headers/World.h"

GameManager::GameManager(GameObject& InGo): Behaviour(InGo), CurrentState(Null)
{
}

void GameManager::Establish()
{
    GoToState(Opening);
}

void GameManager::PreCollisionTick()
{
    switch (CurrentState)
    {
    case Null: break;
    case Opening:
        if (GetOwner()->GetWorld()->IsButtonPressed('P'))
        {
            GoToState(Playing);
            return;
        }
        if (GetOwner()->GetWorld()->IsButtonPressed('Q'))
        {
            GetOwner()->GetWorld()->Quit();
            return;
        }
        break;
    case Playing:
        if (GetOwner()->GetWorld()->IsButtonPressed('Q'))
        {
            GoToState(Ended);
            return;
        }
        break;
    case Ended:
        if (GetOwner()->GetWorld()->IsButtonPressed('R'))
        {
            GoToState(Playing);
            return;
        }
        if (GetOwner()->GetWorld()->IsButtonPressed('Q'))
        {
            GetOwner()->GetWorld()->Quit();
            return;
        }
        break;
    default: ;
    }
}

void GameManager::GoToState(const EGameManagerStates InTargetState)
{
    switch (CurrentState)
    {
    case Null:
        break;
    case Opening:
        GetOwner()->GetWorld()->GetGameObject("Welcome")->Destroy();
        break;
    case Playing:
        GetOwner()->GetWorld()->GetGameObject("Snake Head")->Destroy();
        GetOwner()->GetWorld()->GetGameObject("Apple")->Destroy();
        break;
    case Ended:
        GetOwner()->GetWorld()->GetGameObject("GameOver")->Destroy();
        break;
    default: ;
    }

    switch (InTargetState)
    {
    case Null:
        break;
    case Opening:
        Border::Initialize(*GetOwner()->GetWorld());
        Welcome::Initialize(*GetOwner()->GetWorld());
        break;
    case Playing:
        Score = 0;
        SnakeHead::Initialize(*GetOwner()->GetWorld());
        Apple::Initialize(*GetOwner()->GetWorld());
        break;
    case Ended:
        GameOver::Initialize(*GetOwner()->GetWorld());
        break;
    default: ;
    }

    CurrentState = InTargetState;
}

void GameManager::DeclareGameOver()
{
    GoToState(Ended);
}

int GameManager::GetScore() const
{
    return Score;
}

void GameManager::ReportAppleEaten()
{
    Score++;
}

bool GameManager::IsGameRunning() const
{
    return CurrentState == Playing;
}
