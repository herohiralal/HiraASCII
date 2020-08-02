#include "../Headers/Camera.h"

#include <iostream>

#include "../Headers/Vector2.h"
#include "../Headers/Bounds.h"
#include "../Headers/World.h"
#include "../Headers/RendererWorld.h"
#include "../Headers/RendererComponent.h"

Camera::Camera(const int InHorizontalCenter, const int InVerticalCenter, const unsigned InHalfWidth,
               const unsigned InHalfHeight) :
    Center(*new Vector2(InHorizontalCenter, InVerticalCenter)),
    HalfWidth(InHalfWidth),
    HalfHeight(InHalfHeight),
    Scope(*new Bounds())
{
    CalculateHorizontalPoints();
    CalculateVerticalPoints();

    RecalculateBuffer();
}

Camera::~Camera()
{
    DestroyBuffer();
}

void Camera::SetCenter(const int InHorizontalCenter, const int InVerticalCenter)
{
    Center.Set(InHorizontalCenter, InVerticalCenter);
    CalculateHorizontalPoints();
    CalculateVerticalPoints();
}

void Camera::SetHalfWidth(const unsigned InHalfWidth)
{
    DestroyBuffer();
    HalfWidth = InHalfWidth;
    CalculateHorizontalPoints();
    RecalculateBuffer();
}

void Camera::SetHalfHeight(const unsigned InHalfHeight)
{
    DestroyBuffer();
    HalfHeight = InHalfHeight;
    CalculateVerticalPoints();
    RecalculateBuffer();
}

void Camera::Render(const World& InWorld) const
{
    ClearBuffer();

    system("cls");

    auto RenderersOnCamera = InWorld.GetRendererWorld()->GetRenderersOnCamera(*this);

    for (auto Renderer : RenderersOnCamera)
        DrawRenderer(*Renderer);

    DrawBuffer();
}

bool Camera::IntersectsWith(const Bounds& InTarget) const
{
    return !Scope.DoesNotIntersectWith(InTarget);
}

bool Camera::IsPointInScope(const Vector2& InTarget) const
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

void Camera::DrawRenderer(const RendererComponent& InRenderer) const
{
    const auto RendererSize = InRenderer.GetSize();

    for (unsigned I = 0; I < RendererSize; I++)
    {
        const auto Position = InRenderer.GetRenderPosition(I);
        if (!Scope.IsVectorOutsideBounds(Position))
            Buffer[Position.Y - Center.Y + HalfHeight][Position.X - Center.X + HalfWidth] = InRenderer.GetRenderData(I);
    }
}

void Camera::RecalculateBuffer()
{
    auto const RendererHeight = 1 + 2 * HalfHeight;
    auto const RendererWidth = 1 + 2 * HalfWidth;

    Buffer = new char*[RendererHeight];

    for (unsigned H = 0; H < RendererHeight; H++)
    {
        Buffer[H] = new char[RendererWidth];
        for (unsigned W = 0; W < RendererWidth; W++)
        {
            Buffer[H][W] = ' ';
        }
    }
}

void Camera::DestroyBuffer() const
{
    auto const RendererHeight = 1 + 2 * HalfHeight;

    for (unsigned H = 0; H < RendererHeight; H++)
        delete[] Buffer[H];

    delete[] Buffer;
}

void Camera::DrawBuffer() const
{
    auto const Height = 1 + 2 * HalfHeight;
    auto const Width = 1 + 2 * HalfWidth;


    for (auto H = Height - 1; H < Height; H--)
    {
        for (unsigned W = 0; W < Width; W++)
            std::cout << Buffer[H][W];

        std::cout << std::endl;
    }
}

void Camera::ClearBuffer() const
{
    auto const RendererHeight = 1 + 2 * HalfHeight;
    auto const RendererWidth = 1 + 2 * HalfWidth;

    for (unsigned H = 0; H < RendererHeight; H++)
        for (unsigned W = 0; W < RendererWidth; W++)
            Buffer[H][W] = ' ';
}
