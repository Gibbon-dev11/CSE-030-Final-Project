#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/textbox.h>
#include <bobcat_ui/window.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/menu.h>

#include "ArrayList.h"
#include "GameState.h"
#include "GameInterface.h"
#include "SettingsInterface.h"

class Application: public bobcat::Application_ {
    bobcat::Window *window;
    
    bobcat::Menu *menu;
    bobcat::MenuItem *newGame;
    bobcat::MenuItem *settings;
    bobcat::MenuItem *quit;
    
    bobcat::Button *applyButton;
    bobcat::Button *cancelButton;

    GameInterface *gameInterface;
    SettingsInterface *settingsInterface;

    GameState state;

    void handleNewGameMenuClick(bobcat::Widget *sender);
    void handleSettingsMenuClick(bobcat::Widget *sender);
    void handleCancelBtnClick(bobcat::Widget *sender);
    void handleApplyBtnClick(bobcat::Widget *sender);
    void handleQuitMenuClick(bobcat::Widget *sender);

public:
    Application();
};

#endif