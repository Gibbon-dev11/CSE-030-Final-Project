#ifndef AGENT_H
#define AGENT_H

#include "GameState.h"
#include "Vertex.h"



class Agent {
    static int getReward(Vertex<GameState>* start, int player);
public:
    static Vec play(GameState state);
};

#endif