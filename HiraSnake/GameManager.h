#pragma once
#include "../HiraASCII/Headers/Behaviour.h"

enum EGameManagerStates
{
    Null, Opening, Playing, Ended
};

class GameManager : public Behaviour
{
public:
    explicit GameManager(GameObject& InGo);
    void Establish() override;
    void PreCollisionTick() override;

private:
    int Score = 0;
    EGameManagerStates CurrentState;
    void GoToState(EGameManagerStates InTargetState);

public:
    void DeclareGameOver();
    int GetScore() const;
    void ReportAppleEaten();
    bool IsGameRunning() const;
};
