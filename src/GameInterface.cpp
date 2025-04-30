#include <FL/Fl_Window.H>
#include <GameInterface.h>
#include <Agent.h>
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/textbox.h>

using namespace std;
using namespace bobcat;

GameInterface::GameInterface(int x, int y, int w, int h, GameState initialState){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    
    state = initialState;

    string message = "Player vs Player";
    if (state.getEnabledAI()){
        message = "Player vs AI";
    }

    statusBar = new TextBox(0, 375, 400, 25, message);

    initButtons();
    showButtons();
}

void GameInterface::handleClick(Widget *sender){
    for (int i = 0; i < state.gridSize(); i++){
        for (int j = 0; j < state.gridSize(); j++){
            if (sender == buttons[i][j]){
                state.play(i, j);
                updateButtons();

                bool done = checkWinningConditions();
            
                if (!done){
                    if (state.getEnabledAI()){
                        Vec move = Agent::play(state);
                        state.play(move.x, move.y);
                        updateButtons();
                        checkWinningConditions();
                    }
                }

                return;
            }
        }
    }
    
}

bool GameInterface::checkWinningConditions(){
    bool result = state.gameOver();
    if (state.gameOver()){
        if (state.hasWon(0)){
            showMessage("Player X has won.\nClick Close to start a new game.", "Game Over");
        }
        else if (state.hasWon(1)){
            showMessage("Player O has won.\nClick Close to start a new game.", "Game Over");
        }
        else{
            showMessage("It is a tie.\nClick Close to start a new game.", "Game Over");
        }
        reset();
    }
    return result;
}

void GameInterface::initButtons(){

    for (int i = 0; i < 5; i++){
        ArrayList<Button*> row;
        for (int j = 0; j < 5; j++){
            Button* curr = new Button(0, 0, 1, 1);
            row.append(curr);
        }
        buttons.append(row);
    }

    for (int i = 0; i < buttons.size(); i++){
        for (int j = 0; j < buttons[i].size(); j++){
            buttons[i][j]->labelsize(32);
            ON_CLICK(buttons[i][j], GameInterface::handleClick);
        }
    }
}

void GameInterface::showButtons(){
    int btnW = w / state.gridSize();
    int btnH = h / state.gridSize();
    for (int i = 0; i < state.gridSize(); i++){
        int btnY = y + btnH * i;
        for (int j = 0; j < state.gridSize(); j++){
            int btnX = x + btnW * j;

            buttons[i][j]->resize(btnX, btnY, btnW, btnH);
            buttons[i][j]->label(state.squareState(i, j));
            buttons[i][j]->show();
        }
    }
}

void GameInterface::hideButtons(){
    for (int i = 0; i < state.gridSize(); i++){
        for (int j = 0; j < state.gridSize(); j++){
            buttons[i][j]->hide();
        }
    }
}

void GameInterface::updateButtons(){
    for (int i = 0; i < state.gridSize(); i++){
        for (int j = 0; j < state.gridSize(); j++){
            buttons[i][j]->label(state.squareState(i, j));
        }
    }
}

void GameInterface::show() {
    showButtons();
    statusBar->show();
}

void GameInterface::hide() {
    hideButtons();
    statusBar->hide();
}

void GameInterface::reset() {
    state.reset();
    updateButtons();
}

GameState GameInterface::getState() const{
    return state;
}

void GameInterface::setState(GameState state){
    this->state = state;
    string message = "Player vs Player";
    if (state.getEnabledAI()){
        message = "Player vs AI";
    }
    statusBar->label(message);
}
