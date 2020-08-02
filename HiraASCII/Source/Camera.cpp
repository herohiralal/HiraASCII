#include "../Headers/Camera.h"
#include "../Headers/Vector2.h"
#include "../Headers/Bounds.h"

Camera::Camera() :
    Center(*new Vector2(0, 0)),
    Scope(*new Bounds())
{
    HalfWidth = 20;
    HalfHeight = 11;
    CalculateHorizontalPoints();
    CalculateVerticalPoints();
}

Camera::Camera(const int InHorizontalCenter, const int InVerticalCenter, const unsigned InHalfWidth,
               const unsigned InHalfHeight) :
    Center(*new Vector2(InHorizontalCenter, InVerticalCenter)),
    HalfWidth(InHalfWidth),
    HalfHeight(InHalfHeight),
    Scope(*new Bounds())
{
    CalculateHorizontalPoints();
    CalculateVerticalPoints();
}

Camera::~Camera()
{
    delete &Center;
    delete &Scope;
}

void Camera::SetCenter(const int InHorizontalCenter, const int InVerticalCenter)
{
    Center.Set(InHorizontalCenter, InVerticalCenter);
    CalculateHorizontalPoints();
    CalculateVerticalPoints();
}

void Camera::SetHalfWidth(const unsigned InHalfWidth)
{
    HalfWidth = InHalfWidth;
    CalculateHorizontalPoints();
}

void Camera::SetHalfHeight(const unsigned InHalfHeight)
{
    HalfHeight = InHalfHeight;
    CalculateVerticalPoints();
}

bool Camera::IntersectsWith(const Bounds InTarget) const
{
    return !Scope.DoesNotIntersectWith(InTarget);
}

bool Camera::IsPointInScope(const Vector2 InTarget) const
{
    return !Scope.IsVectorOutsideBounds(InTarget);
}

void Camera::CalculateHorizontalPoints()
{
    Scope.SetHorizontal(Center.X - HalfWidth, Center.X + HalfWidth);
}

void Camera::CalculateVerticalPoints()
{
    Scope.SetVertical(Center.Y - HalfHeight, Center.Y + HalfHeight);
}