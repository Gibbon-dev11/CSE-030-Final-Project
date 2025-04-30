#include "Application.h"
#include "SettingsInterface.h"
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <cstdlib>

using namespace bobcat;
using namespace std;

Application::Application(){
    window = new Window(100, 100, 400, 400, "Tic-Tac-Toe");

    state = GameState();
    state.enableAI();

    gameInterface = new GameInterface(30, 35, 340, 340, state);
    settingsInterface = new SettingsInterface(30, 40, 340, 340, state);

    cancelButton = new Button(30, 360, 155, 25, "Cancel");
    applyButton = new Button(215, 360, 155, 25, "Apply");

    settingsInterface->hide();
    cancelButton->hide();
    applyButton->hide();

    menu = new Menu();
    newGame = new MenuItem("File/New Game");
    settings = new MenuItem("File/Settings");
    quit = new MenuItem("File/Exit");
    menu->addItem(newGame);
    menu->addItem(settings);
    menu->addItemSep(quit);

    ON_CLICK(newGame, Application::handleNewGameMenuClick);
    ON_CLICK(settings, Application::handleSettingsMenuClick);
    ON_CLICK(quit, Application::handleQuitMenuClick);
    ON_CLICK(cancelButton, Application::handleCancelBtnClick);
    ON_CLICK(applyButton, Application::handleApplyBtnClick);

    window->show();
}

void Application::handleNewGameMenuClick(Widget *sender){
    gameInterface->reset();
}

void Application::handleSettingsMenuClick(Widget *sender){
    gameInterface->hide();
    settingsInterface->show();
    applyButton->show();
    cancelButton->show();
}

void Application::handleCancelBtnClick(Widget *sender){
    settingsInterface->hide();
    applyButton->hide();
    cancelButton->hide();
    gameInterface->show();
}

void Application::handleApplyBtnClick(Widget* sender){
    settingsInterface->applyUpdates();

    state = settingsInterface->getState();

    gameInterface->setState(state);

    settingsInterface->hide();
    applyButton->hide();
    cancelButton->hide();

    gameInterface->show();
}

void Application::handleQuitMenuClick(Widget *sender){
    exit(0);
}
