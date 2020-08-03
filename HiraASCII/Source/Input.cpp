#include "../Headers/Input.h"

#include <conio.h>

Input::Input() : ButtonsPressed(new bool[26])
{
}

Input::~Input()
{
    delete[] ButtonsPressed;
}

void Input::AcceptInput() const
{
    if (_kbhit())
    {
        const auto Input = _getch();

        if (Input > 64 && Input < 91) // capital letters
            ButtonsPressed[Input - 65] = true;

        if (Input > 96 && Input < 123) // small letters
            ButtonsPressed[Input - 97] = true;
    }
}

void Input::ClearInput() const
{
    for (auto I = 0; I < 26; I++)
        ButtonsPressed[I] = false;
}

bool Input::IsButtonPressed(const char InLetter) const
{
    const int Input = InLetter;

    if (Input > 64 && Input < 91) // capital letters
        return ButtonsPressed[Input - 65];
    if (Input > 96 && Input < 123) // small letters
        return ButtonsPressed[Input - 97];

    return false;
}
