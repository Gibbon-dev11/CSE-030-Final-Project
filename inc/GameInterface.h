#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/textbox.h>

#include <ArrayList.h>
#include <GameState.h>
#include <string>

class GameInterface{
    int x;
    int y;
    int w;
    int h;

    GameState state;

    bobcat::TextBox *statusBar;

    ArrayList<ArrayList<bobcat::Button*>> buttons;

    void handleClick(bobcat::Widget *sender);

    void initButtons();
    void updateButtons();
    void showButtons();
    void hideButtons();

    bool checkWinningConditions();

public:

    GameInterface(int x, int y, int w, int h, GameState initialState);

    void reset();
    void hide();
    void show();

    GameState getState() const;
    void setState(GameState state);

};

#endif