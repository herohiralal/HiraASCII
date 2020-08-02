#include "../Headers/Bounds.h"
#include "../Headers/Vector2.h"

Bounds::Bounds() : MinX(0), MinY(0), MaxX(0), MaxY(0)
{
}

Bounds::Bounds(const int& InMinX, const int& InMinY, const int& InMaxX, const int& InMaxY) : MinX(InMinX), MinY(InMinY),
    MaxX(InMaxX), MaxY(InMaxY)
{
}

void Bounds::Set(const int& InMinX, const int& InMinY, const int& InMaxX, const int& InMaxY)
{
    MinX = InMinX;
    MinY = InMinY;
    MaxX = InMaxX;
    MaxY = InMaxY;
}

void Bounds::SetHorizontal(const int& InMinX, const int& InMaxX)
{
    MinX = InMinX;
    MaxX = InMaxX;
}

void Bounds::SetVertical(const int& InMinY, const int& InMaxY)
{
    MinY = InMinY;
    MaxY = InMaxY;
}

void Bounds::IncorporateIntoBounds(const Vector2& InVector2)
{
    IncorporateIntoBoundsHorizontally(InVector2.X);
    IncorporateIntoBoundsVertically(InVector2.Y);
}

void Bounds::IncorporateIntoBoundsHorizontally(const int InX)
{
    if(InX < MinX) MinX = InX;
    else if (InX > MaxX) MaxX = InX;
}

void Bounds::IncorporateIntoBoundsVertically(const int InY)
{
    if (InY < MinY) MinY = InY;
    else if (InY > MaxY) MaxY = InY;
}

bool Bounds::DoesNotIntersectWith(const Bounds& InOther) const
{
    return DoesNotIntersectHorizontallyWith(InOther) || DoesNotIntersectVerticallyWith(InOther);
}

bool Bounds::DoesNotIntersectHorizontallyWith(const Bounds& InOther) const
{
    return InOther.MaxX < MinX || InOther.MinX > MaxX;
}

bool Bounds::DoesNotIntersectVerticallyWith(const Bounds& InOther) const
{
    return InOther.MaxY < MinY || InOther.MinY > MaxY;
}

bool Bounds::IsVectorOutsideBounds(const Vector2& InVector2) const
{
    return IsVectorOutsideHorizontalBounds(InVector2) || IsVectorOutsideVerticalBounds(InVector2);
}

bool Bounds::IsVectorOutsideHorizontalBounds(const Vector2& InVector2) const
{
    return InVector2.X > MaxX || InVector2.X < MinX;
}

bool Bounds::IsVectorOutsideVerticalBounds(const Vector2& InVector2) const
{
    return InVector2.Y > MaxY || InVector2.Y < MinY;
}
