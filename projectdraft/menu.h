#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include <string>

// Define custom colors
#define CUSTOM_RED Color{ 200, 0, 0, 255 } // Adjust RGB values as needed
#define CUSTOM_WHITE Color{ 230, 230, 230, 255 } // Adjust RGB values as needed

struct Button {
    Rectangle rect;
    Color baseColor;
    Color hoverColor;
    Color textColor;
    std::string text;
    bool clicked;

    Button(Rectangle r, Color bc, Color hc, Color tc, std::string t)
        : rect(r), baseColor(bc), hoverColor(hc), textColor(tc), text(t), clicked(false) {}

    void Draw() {
        Color currentColor = baseColor;
        Vector2 mousePos = GetMousePosition();

        if (CheckCollisionPointRec(mousePos, rect)) {
            currentColor = hoverColor;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                clicked = true;
            }
        }

        DrawRectangleRounded(rect, 0.2, 0, currentColor);
        DrawText(TextFormat("%s", text.c_str()), rect.x + rect.width / 2 - MeasureText(text.c_str(), 30) / 2, rect.y + rect.height / 2 - 15, 30, textColor);
    }

    bool CheckCollision(Vector2 mousePos) {
        return CheckCollisionPointRec(mousePos, rect);
    }
};

class Menu {
public:
    Menu(Rectangle rect);
    ~Menu();
    void Draw();
    bool CheckResumeButtonClick();
    bool CheckExitButtonClick();
    void ResetButtons(); // Add this method

private:
    Button resumeButton;
    Button exitButton;
};

#endif // MENU_H
