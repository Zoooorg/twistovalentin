#include <stdio.h>
#include <stdlib.h>
#include "astar.h"

// Map droitAuBut

#define WIDTH 32
#define HEIGHT 16


// Nouvelle Map
/*
#define WIDTH 60
#define HEIGHT 30
*/

// Fonction pour créer un nœud à partir des coordonnées et du type de sol
Node* createNode(Graph* graph, int x, int y, char ground) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->id = y * graph->MAP_WIDTH + x;
    node->x = x;
    node->y = y;
    node->ground = ground;
    node->g = 0;
    node->h = 0;
    node->f = 0;
    node->parent = NULL;
    node->next = NULL;
    return node;
}

// Fonction pour créer et initialiser un graphe à partir de la carte
Graph* createGraphFromMap(char map[HEIGHT][WIDTH]) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    graph->MAP_WIDTH = WIDTH;
    graph->MAP_HEIGHT = HEIGHT;
    graph->numNodes = graph->MAP_WIDTH * graph->MAP_HEIGHT;
    graph->nodes = (Node**)malloc(graph->numNodes * sizeof(Node*));
    if (graph->nodes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(graph);
        exit(EXIT_FAILURE);
    }

    // Parcourir la carte pour créer les nœuds et les ajouter au graphe
    for (int y = 0; y < graph->MAP_HEIGHT; y++) {
        for (int x = 0; x < graph->MAP_WIDTH; x++) {
            char ground = map[y][x];
            Node* node = createNode(graph, x, y, ground);
            addNodeToGraph(graph, node);
        }
    }

    // Définir le nœud de départ et le nœud objectif (à adapter selon votre carte)

    int startY = 5;
    int startX = 3;
    int goalY = 7;
    int goalX = 27;


/*
    int startY = 1;
    int startX = 17;
    int goalY = 9;
    int goalX = 20;
*/

    graph->start = getNodeById(graph, startY * graph->MAP_WIDTH + startX);
    graph->goal = getNodeById(graph, goalY * graph->MAP_WIDTH + goalX);

    return graph;
}

int main() {
    // Carte fournie droit au but
    char map[HEIGHT][WIDTH] = {
        "................................",
        "................................",
        "................................",
        "................................",
        "..#########################==...",
        "..#1#######################==...",
        "..#########################==...",
        "..#2#######################==...",
        "..#########################==...",
        "..#3#######################==...",
        "..#########################==...",
        "................................",
        "................................",
        "................................",
        "................................",
        "................................"
    };
    /*
    // Nouvelle carte fournie
    char map[HEIGHT][WIDTH] = {
        "............................................................",
        ".................1#####.....................................",
        ".................2#############............................",
        ".................3#####################.....................",
        ".....................######################.................",
        ".............................###############.................",
        ".....................................#########...............",
        ".........................................######..............",
        "..........#####...........................######.............",
        "........############==......................######...........",
        ".......#############==.......................######..........",
        ".......#####.#######==........................######.........",
        "......####......................................####.........",
        "......####......................................####.........",
        "......###.......................................####.........",
        "......###.......................................###..........",
        "......###.......................................###..........",
        "......####.....................................####..........",
        "......#####...................................#####..........",
        ".......####...............................########...........",
        "........##########################################...........",
        "........########################################.............",
        ".........###################################................",
        "............................................................",
        "............................................................",
        "............................................................",
        "............................................................",
        "............................................................",
        "............................................................",
        "............................................................",
        "............................................................"
    };
    */

    // Créer et initialiser le graphe à partir de la carte
    Graph* graph = createGraphFromMap(map);

    // Exécuter l'algorithme A*
    aStar(graph);

    // Libérer la mémoire du graphe
    freeGraph(graph);

    return 0;
}

