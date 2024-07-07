#include "Menu.h"

Menu::Menu(Rectangle rect)
    : resumeButton({ rect.x, rect.y, rect.width, rect.height }, Fade(WHITE, 0.6), Fade(CUSTOM_RED, 0.8), BLACK, "RESUME"),
    exitButton({ rect.x, rect.y + 60, rect.width, rect.height }, Fade(WHITE, 0.6), Fade(CUSTOM_RED, 0.8), BLACK, "EXIT") {}

Menu::~Menu() {}

void Menu::Draw() {
    resumeButton.Draw();
    exitButton.Draw();
}

bool Menu::CheckResumeButtonClick() {
    return resumeButton.clicked;
}

bool Menu::CheckExitButtonClick() {
    return exitButton.clicked;
}





