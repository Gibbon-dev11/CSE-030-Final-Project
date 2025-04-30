#include <GameState.h>

using namespace std;
GameState::GameState(int size){
    this->size = size;
    currentTurn = 0;
    turnCount = 0;
    done = false;

    enabledAI = false;

    lastMove.set(-1, -1);

    grid = new int*[size];

    for (int i = 0; i < size; i++){
        grid[i] = new int[size];
        for (int j = 0; j < size; j++){
            grid[i][j] = -1;
        }
    }
}

GameState::GameState(const GameState& other){
    size = other.size;
    currentTurn = other.currentTurn;
    turnCount = other.turnCount;
    done = other.done;
    lastMove = other.lastMove;
    enabledAI = other.enabledAI;

    grid = new int*[size];

    for (int i = 0; i < size; i++){
        grid[i] = new int[size];
        for (int j = 0; j < size; j++){
            grid[i][j] = other.grid[i][j];
        }
    }
}

bool GameState::operator==(const GameState& other){
    bool sizeMatch = size == other.size;
    bool currentTurnMatch = currentTurn == other.currentTurn;
    bool turnCountMatch = turnCount == other.turnCount;
    bool doneMatch = done == other.done;
    bool aiMatch = enabledAI == other.enabledAI;
    bool lastMoveMatch = lastMove.x == other.lastMove.x && lastMove.y == other.lastMove.y;
    if (sizeMatch && currentTurnMatch && turnCountMatch && doneMatch && aiMatch && lastMoveMatch){

        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (grid[i][j] != other.grid[i][j]){
                    return false;
                }
            }
        }

        return true;
    }
    else{
        return false;
    }
}

GameState& GameState::operator=(const GameState& other){
    currentTurn = other.currentTurn;
    turnCount = other.turnCount;
    done = other.done;
    lastMove = other.lastMove;
    enabledAI = other.enabledAI;
    if (size == other.size){
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                grid[i][j] = other.grid[i][j];
            }
        }
    }
    else{
        for (int i = 0; i < size; i++){
            delete[] grid[i];
        }
        delete[] grid;

        size = other.size;

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = other.grid[i][j];
            }
        }
    }

    return *this;
}

bool GameState::hasWon(int player){
    for (int i = 0; i < size; i++){
        bool winRow = true;
        for (int j = 0; j < size; j++){
            if (grid[i][j] != player){
                winRow = false;
                break;
            }
        }
        if (winRow){
            return true;
        }
    }
    for (int i = 0; i < size; i++){
        bool winCol = true;
        for (int j = 0; j < size; j++){
            if (grid[j][i] != player){
                winCol = false;
                break;
            }
        }
        if (winCol){
            return true;
        }
    }

    bool winDiag = true;
    for (int i = 0; i < size; i++){
        if (grid[i][i] != player){
            winDiag = false;
            break;
        }
    }
    if (winDiag){
        return true;
    }
    
    bool winAntiDiag = true;
    for (int i = 0; i < size; i++){
        if (grid[i][size-1-i] != player){
            winAntiDiag = false;
            break;
        }
    }
    if (winAntiDiag){
        return true;
    }

    return false;
}


bool GameState::play(int x, int y){
    if (grid[x][y] != -1){
        return false;
    }

    grid[x][y] = currentTurn;
    currentTurn = !currentTurn;
    turnCount++;
    lastMove.set(x, y);

    if (turnCount == size * size){
        done = true;
    }
    else if (hasWon(0) || hasWon(1)){
        done = true;
    }

    return true;
}

int GameState::gridSize() const {
    return size;
}


int GameState::getCurrentTurn() const {
    return currentTurn;
}


bool GameState::gameOver() const {
    return done;
}

string GameState::squareState(int i, int j) const {
    if (grid[i][j] == 0){
        return "X";
    }
    else if (grid[i][j] == 1){
        return "O";
    }
    
    return "";
}

Vec GameState::getLastMove() const {
    return lastMove;
}


void GameState::reset(){
    currentTurn = 0;
    turnCount = 0;
    done = false;

    lastMove.set(-1, -1);

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            grid[i][j] = -1;
        }
    }
}

void GameState::enableAI(){
    enabledAI = true;
}

void GameState::disableAI(){
    enabledAI = false;
}

bool GameState::getEnabledAI() const{
    return enabledAI;
}

GameState::~GameState(){
    for (int i = 0; i < size; i++){
        delete[] grid[i];
    }
    delete[] grid;
}


