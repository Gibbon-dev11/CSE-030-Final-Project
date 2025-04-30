#ifndef SETTINGS_INTERFACE_H
#define SETTINGS_INTERFACE_H

#include <bobcat_ui/textbox.h>
#include <bobcat_ui/dropdown.h>

#include "GameState.h"


class SettingsInterface {
    bobcat::TextBox *pageHeading;
    bobcat::Dropdown *gridSizeSelector;
    bobcat::Dropdown *enableAISelector;

    int x;
    int y;
    int w;
    int h;

    bool visible;

    GameState state;

public:
    SettingsInterface(int x, int y, int w, int h, GameState state);

    void applyUpdates();
    void hide();
    void show();

    GameState getState() const;
    void setState(GameState state);
};

#endif