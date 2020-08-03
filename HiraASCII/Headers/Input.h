#pragma once

class Input
{
public:
    Input();
    ~Input();
private:
    bool* ButtonsPressed = nullptr;

public:
    void AcceptInput() const;
    void ClearInput() const;
    bool IsButtonPressed(char InLetter) const;
};