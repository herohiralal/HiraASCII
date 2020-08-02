#pragma once

struct Vector2
{
public:
    explicit Vector2(int InX = 0, int InY = 0);

    int X;
    int Y;

    void Set(int InX, int InY);
    bool IsEqualTo(const Vector2& InOther) const;

    Vector2 operator +(const Vector2& InRhs) const;
};