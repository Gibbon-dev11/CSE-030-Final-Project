
// #include <FL/Enumerations.H>
#include <SettingsInterface.h>

using namespace std;
using namespace bobcat;

SettingsInterface::SettingsInterface(int x, int y, int w, int h, GameState state){
    visible = true;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    this->state = state;

    pageHeading = new TextBox(x, y, w, 25, "Settings");
    pageHeading->labelsize(24);
    pageHeading->labelfont(FL_BOLD);

    gridSizeSelector = new Dropdown(x, y + 50, w, 25, "Board size");
    gridSizeSelector->add("3 x 3");
    gridSizeSelector->add("4 x 4");
    gridSizeSelector->add("5 x 5");

    enableAISelector = new Dropdown(x, y + 100, w, 25, "AI Player");
    enableAISelector->add("Enabled");
    enableAISelector->add("Disabled");
    if (state.getEnabledAI()) {
        enableAISelector->value(0);
    }
    else {
        enableAISelector->value(1);
    }
}

void SettingsInterface::applyUpdates(){
    int newSize = 0;
    bool shouldEnableAI = false;

    if (gridSizeSelector->value() == 0){
        newSize = 3;
    }
    else if (gridSizeSelector->value() == 1){
        newSize = 4;
    }
    else if (gridSizeSelector->value() == 2){
        newSize = 5;
    }

    if (enableAISelector->value() == 0){
        shouldEnableAI = true;
    }
    else if (enableAISelector->value() == 1){
        shouldEnableAI = false;
    }
    
    if (newSize != state.gridSize()){
        state = GameState(newSize);
    }

    if (shouldEnableAI){
        state.enableAI();
    }
    else{
        state.disableAI();
    }

}

void SettingsInterface::hide(){
    visible = false;
    pageHeading->hide();
    gridSizeSelector->hide();
    enableAISelector->hide();
}

void SettingsInterface::show(){
    visible = true;
    pageHeading->show();
    gridSizeSelector->show();
    enableAISelector->show();
}

GameState SettingsInterface::getState() const{
    return state;
}

void SettingsInterface::setState(GameState state){
    this->state = state;
}
