#include "Queue.h"
#include "Vertex.h"
#include "Graph.h"
#include <iostream>
#include <Agent.h>

using namespace std;

struct GameTreeNode{
    Vertex<GameState>* vertex;
    int depth;

    GameTreeNode(Vertex<GameState>* vertex = nullptr, int depth = 0){
        this->vertex = vertex;
        this->depth = depth;
    }
};

Vec findFirstAvailable(GameState state){
    for (int i = 0; i < state.gridSize(); i++){
        for (int j = 0; j < state.gridSize(); j++){
            if (state.squareState(i, j) == ""){
                return Vec(i, j);
            }
        }
    }

    return Vec(0, 0);
}

ArrayList<Vec> openSquares(GameState state){
    ArrayList<Vec> result;
    if (!state.gameOver()){
        for (int i = 0; i < state.gridSize(); i++){
            for (int j = 0; j < state.gridSize(); j++){
                if (state.squareState(i, j) == ""){
                    result.append(Vec(i,j));
                }
            }
        }
    }
    return result;
}

int Agent::getReward(Vertex<GameState>* start, int player){
    // Evaluate a particular vertex in the state space
    // from the point of view of player

    // If it is a terminal state, evaluate it directly
    if (start->neighbors.size() == 0){
        // If we won, maximum reward
        if (start->data.hasWon(player)){
            return 100;
        }
        // if we lost maximum penalty
        else if (start->data.hasWon(!player)){
            return -100;
        }
        // otherwise somewhere in-between
        else{
            return 50;
        }
    }
    // If it is not a terminal state (it has children),
    // we evaluate each child and pick the maximum or the minimum child
    // depending on whose turn it is
    else{
        int reward = getReward(start->neighbors[0]->location, player);
        for (int i = 1; i < start->neighbors.size(); i++){
            int curr = getReward(start->neighbors[i]->location, player);
            if (start->data.getCurrentTurn() == player){
                if (curr > reward){
                    reward = curr;
                }
            }
            else{
                if (curr < reward){
                    reward = curr;
                }
            }
        }
        return reward;
    }
}

Vec Agent::play(GameState state){
    Vertex<GameState>* root = new Vertex<GameState>(state);
    Graph<GameState> gameSpace;
    gameSpace.addVertex(root);

    Queue<GameTreeNode> frontier;
    frontier.enqueue(GameTreeNode(root, 0));

    int limit = 3;
    while (!frontier.isEmpty()){
        GameTreeNode gtn = frontier.dequeue();
        Vertex<GameState>* node = gtn.vertex;
        int depth = gtn.depth;
        ArrayList<Vec> moves = openSquares(node->data);

        if (state.gridSize() == 3){
            limit = 6;
        }
        else{
            if (moves.size() < 15){
                limit = 5;
            }
        }
        if (depth < limit){
            for (int i = 0; i < moves.size(); i++){
                GameState currentState = node->data;
                currentState.play(moves[i].x, moves[i].y);
                Vertex<GameState>* child = new Vertex<GameState>(currentState);
                gameSpace.addVertex(child);
                gameSpace.addDirectedEdge(node, child, 1);
                frontier.enqueue(GameTreeNode(child, depth + 1));
            }
        }
    }

    int reward = getReward(root->neighbors[0]->location, 1);
    int pos = 0;
    for (int i = 1; i < root->neighbors.size(); i++){
        int curr = getReward(root->neighbors[i]->location, 1);
        if (curr > reward){
            reward = curr;
            pos = i;
        }
        else if (curr == reward && root->neighbors[i]->location->data.hasWon(1)){
            reward = curr;
            pos = i;
        }
    }

    return root->neighbors[pos]->location->data.getLastMove();
}