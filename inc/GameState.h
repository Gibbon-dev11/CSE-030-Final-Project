#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>

struct Vec{
    int x;
    int y;

    Vec(){
        x = 0;
        y = 0;
    }

    Vec(int x, int y){
        this->x = x;
        this->y = y;
    }

    void set(int x, int y){
        this->x = x;
        this->y = y;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Vec& v){
    os << "(" << v.x << ", " << v.y << ")";

    return os;
}

class GameState{
    int** grid;
    bool currentTurn;
    int size;
    int turnCount;

    bool enabledAI;
    bool done;
    Vec lastMove;

public:
    GameState(int size = 3);

    GameState(const GameState& other);

    bool operator==(const GameState& other);

    GameState& operator=(const GameState& other);

    bool hasWon(int player);

    bool gameOver() const;

    bool play(int x, int y);

    int gridSize() const;

    std::string squareState(int i, int j) const;

    void enableAI();

    void disableAI();

    bool getEnabledAI() const;

    int getCurrentTurn() const;

    Vec getLastMove() const;

    void reset();

    ~GameState();

    friend std::ostream& operator<<(std::ostream& os, const GameState& state);
};

inline std::ostream& operator<<(std::ostream& os, const GameState& state){
    os << "   ";
    for (int j = 0; j < state.size; j++){
        os << " " << j << "  ";
    }
    os << std::endl;
    os << "   ";
    for (int j = 0; j < state.size; j++){
        os << "--- ";
    }
    os << std::endl;
    for (int i = 0; i < state.size; i++){
        os << i << " ";
        for (int j = 0; j < state.size; j++){
            char c = ' ';
            if (state.grid[i][j] == 0){
                c = 'X';
            }
            else if (state.grid[i][j] == 1){
                c = 'O';
            }
            os << "| " << c << " ";
            if (j == state.size - 1) os << "|";
        }
        os << std::endl << "   ";
        for (int j = 0; j < state.size; j++){
            os << "--- ";
        }
        os << std::endl;
    }

    return os;
}

#endif