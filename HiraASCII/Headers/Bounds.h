#pragma once
#include <climits>
#include <string>

struct Vector2;

struct Bounds
{
public:
   explicit Bounds(const int& InMinX = INT_MAX, const int& InMinY = INT_MAX, const int& InMaxX = INT_MIN, const int& InMaxY = INT_MIN);

    int MinX;
    int MinY;
    int MaxX;
    int MaxY;

    void Set(const int& InMinX, const int& InMinY, const int& InMaxX, const int& InMaxY);
    void SetHorizontal(const int& InMinX, const int& InMaxX);
    void SetVertical(const int& InMinY, const int& InMaxY);

    void IncorporateIntoBounds(const Vector2& InVector2);
    void IncorporateIntoBoundsHorizontally(int InX);
    void IncorporateIntoBoundsVertically(int InY);

    bool DoesNotIntersectWith(const Bounds& InOther) const;
    bool DoesNotIntersectHorizontallyWith(const Bounds& InOther) const;
    bool DoesNotIntersectVerticallyWith(const Bounds& InOther) const;
    
    bool IsVectorOutsideBounds(const Vector2& InVector2) const;
    bool IsVectorOutsideHorizontalBounds(const Vector2& InVector2) const;
    bool IsVectorOutsideVerticalBounds(const Vector2& InVector2) const;

    void PrintValue() const;
};
