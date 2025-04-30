#ifndef GRAPH_H
#define GRAPH_H

#include <ostream>
#include "ArrayList.h"
#include "Vertex.h"
#include "Queue.h"
#include "Stack.h"
#include "HashTable.h"

template <class T>
struct Waypoint{
    Waypoint<T>* parent;
    int weight;
    int partialCost;
    Vertex<T>* vertex;
    ArrayList<Waypoint<T>*> children;

    Waypoint(Vertex<T>* vertex, Waypoint<T>* parent){
        this->vertex = vertex;
        this->parent = parent;
        partialCost = 0;
    }

    Waypoint(Vertex<T>* vertex, Waypoint<T>* parent, int weight){
        this->vertex = vertex;
        this->parent = parent;
        this->weight = weight;
        partialCost = 0;
    }

    void addToCost(int val){
        partialCost += val;
    }

    void expand(){
        for (int i = 0; i < vertex->degree; i++){
            Neighbor<T>* neighbor = vertex->neighbors[i];
            Waypoint<T>* temp = new Waypoint(neighbor->location, this, neighbor->weight);
            temp->addToCost(partialCost + neighbor->weight);
            children.append(temp);
        }
    }
};

template <class T>
struct Frontier{
    ArrayList<Waypoint<T>*> list;

    void addToFront(Waypoint<T>* wp){
        list.prepend(wp);
    }

    void addToBack(Waypoint<T>* wp){
        list.append(wp);
    }

    void addSorted(Waypoint<T>* wp){
        list.append(wp);
        int j = list.size() - 1;
        while (j > 0 && list[j]->partialCost < list[j-1]->partialCost){
            Waypoint<T>* temp = list[j];
            list[j] = list[j-1];
            list[j-1] = temp;
            j--;
        }
    }

    int getCumulativeCost(Vertex<T>* v){
        for (int i = 0; i < list.size(); i++){
            if (list[i]->vertex == v){
                return list[i]->partialCost;
            }
        }
        return -1;
    }

    void remove(Vertex<T>* v){
        for (int i = 0; i < list.size(); i++){
            if (list[i]->vertex == v){
                list.remove(i);
                break;
            }
        }
    }

    Waypoint<T>* removeFront(){
        return list.removeFirst();
    }

    Waypoint<T>* removeBack(){
        return list.removeLast();
    }

    int length(){
        return list.size();
    }
};

template<class T>
std::ostream& operator<<(std::ostream& os, const Frontier<T> &frontier){
    for (int i = 0; i < frontier.list.size(); i++){
        os << frontier.list[i]->vertex->data << " ";
    }
    return os;
}

template <class T>
struct Graph{

    ArrayList<Vertex<T>*> vertices;

    void addVertex(Vertex<T>* v){
        vertices.append(v);
    }

    void addEdge(Vertex<T>* u, Vertex<T>* v, int label){
        u->addNeighbor(v, label);
        v->addNeighbor(u, label);
    }

    void addDirectedEdge(Vertex<T>* u, Vertex<T>* v, int label = 0){
        u->addNeighbor(v, label);
    }

    Waypoint<T>* bfs(Vertex<T>* start, Vertex<T>* end){
        Frontier<T> frontier;

        Waypoint<T>* initialNode = new Waypoint<T>(start, nullptr);
        frontier.addToBack(initialNode);

        HashTable<T> seen;
        seen.insert(start->data);

        Waypoint<T>* node = nullptr;

        while(frontier.length() > 0){

            node = frontier.removeFront();

            if (node->vertex == end){
                return node;
            }

            node->expand();
 
            for (int i = 0; i < node->children.size(); i++){
                Waypoint<T>* neighbor = node->children[i];

                if (!seen.search(neighbor->vertex->data)){
                    frontier.addToBack(neighbor);
                    seen.insert(neighbor->vertex->data);
                }
            }
        }
        return nullptr;
    }

    Waypoint<T>* dfs(Vertex<T>* start,  Vertex<T>* end, bool repStateCheck=true){
        Frontier<T> frontier;

        Waypoint<T>* initialNode = new Waypoint<T>(start, nullptr);
        frontier.addToBack(initialNode);

        ArrayList<Vertex<T>*> seen;
        if (repStateCheck){
            seen.append(start);
        }

        Waypoint<T>* node = nullptr;

        while(frontier.length() > 0){

            node = frontier.removeFront();

            if (node->vertex == end){
                return node;
            }

            node->expand();
 
            for (int i = 0; i < node->children.size(); i++){
                Waypoint<T>* neighbor = node->children[i];
                if (!repStateCheck){
                    frontier.addToFront(neighbor);
                }
                else{
                    if (!seen.search(neighbor->vertex)){
                        frontier.addToFront(neighbor);
                        seen.append(neighbor->vertex);
                    }
                }
            }
        }
        return initialNode;
    }

    Waypoint<T>* shortestPath(Vertex<T>* start, Vertex<T>* end){
        Frontier<T> frontier;

        Waypoint<T>* initialNode = new Waypoint<T>(start, nullptr);
        frontier.addToBack(initialNode);

        HashTable<T> seen;
        seen.insert(start->data);

        Waypoint<T>* node = nullptr;

        while(frontier.length() > 0){

            node = frontier.removeFront();

            if (node->vertex == end){
                return node;
            }

            node->expand();
 
            for (int i = 0; i < node->children.size(); i++){
                Waypoint<T>* neighbor = node->children[i];

                if (!seen.search(neighbor->vertex->data)){
                    frontier.addSorted(neighbor);
                    seen.insert(neighbor->vertex->data);
                }
                else{
                    int prev = frontier.getCumulativeCost(neighbor->vertex);
                    int curr = neighbor->partialCost;

                    if (prev != -1){
                        if (curr < prev){
                            frontier.remove(neighbor->vertex);
                            frontier.addSorted(neighbor);
                        }
                    }
                }
            }
        }
        return nullptr;
    }

    ~Graph(){
        for (int i = 0; i < vertices.size(); i++){
            delete vertices[i];
        }
    }

};

template <class T>
std::ostream& operator<<(std::ostream& os, const Graph<T>& graph){
    for (int i = 0; i < graph.vertices.size(); i++){
        os << graph.vertices[i] << '\n';
    }
    return os;
}

#endif