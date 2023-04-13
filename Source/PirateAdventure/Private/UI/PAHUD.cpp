// Pirate Adventure Game Vietokhin AD211

#include "UI/PAHUD.h"
#include "Engine/Canvas.h"

void APAHUD::DrawHUD() 
{
    Super::DrawHUD();

    DrawCrosshair();

}

void APAHUD::DrawCrosshair()
{
    // Получаем размер экрана
    FVector2D ScreenSize = FVector2D(Canvas->SizeX, Canvas->SizeY);

    // Вычисляем координаты центра экрана
    FVector2D Center = ScreenSize / 2.f;

    // Вычисляем размер прицела
    float CrosshairSize = 1.0f;

    //Вертикальная линия прицела
    FVector2D StartVertical = Center + FVector2D(0.0f, CrosshairSize);
    FVector2D EndVertical = Center - FVector2D(0.0f, CrosshairSize);
    Canvas->K2_DrawLine(StartVertical, EndVertical, 1.0f, FLinearColor::White);

    //Горизонтальная линия прицела
    FVector2D StartHorizontal = Center + FVector2D(CrosshairSize, 0.0f);
    FVector2D EndHorizontal = Center - FVector2D(CrosshairSize, 0.0f);
    Canvas->K2_DrawLine(StartHorizontal, EndHorizontal, 1.0f, FLinearColor::White);
}