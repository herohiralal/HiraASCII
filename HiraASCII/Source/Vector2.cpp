#include "../Headers/Vector2.h"

Vector2::Vector2(const int InX, const int InY) : X(InX), Y(InY)
{
}

void Vector2::Set(const int InX, const int InY)
{
    X = InX;
    Y = InY;
}

bool Vector2::IsEqualTo(const Vector2& InOther) const
{
    return X == InOther.X && Y == InOther.Y;
}

Vector2 Vector2::operator+(const Vector2& InRhs) const
{
    return Vector2(X + InRhs.X, Y + InRhs.Y);
}
