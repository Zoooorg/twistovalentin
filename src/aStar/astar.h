#ifndef ASTAR_H
#define ASTAR_H

#include <stdlib.h>
#include <stdio.h>
#include "../heap/heap.h"

// Structure représentant un nœud dans le graphe
typedef struct Node {
	int id; // Identifiant général du noeud
	int x; // Coordonnée x du nœud
	int y; // Coordonnée y du nœud
	char ground; // Type de sol
	int g; // Coût du chemin depuis le nœud de départ jusqu'à ce nœud
	int h; // Estimation du coût du chemin restant jusqu'à l'objectif (heuristique)
	int f; // Coût total (g + h)
	struct Node* parent; // Pointeur vers le nœud parent
	struct Node* next; // Pointeur vers le prochain nœud dans la liste
} Node, *NodeList;

typedef struct Graph {
    int MAP_WIDTH;
    int MAP_HEIGHT;
    int numNodes; // Nombre actuel de nœuds dans le graphe
    Node** nodes; // Pointeur vers un tableau de pointeurs vers les nœuds
    Node* start; // Pointeur vers le nœud de départ
    Node* goal; // Pointeur vers le nœud objectif
} Graph;

// Initialisation du graphe
Graph* initializeGraph(int numNodes); 

// Fonction pour ajouter un nœud au graphe
void addNodeToGraph(Graph* graph, Node* node); 

// Fonction pour récupérer un nœud par son identifiant
Node* getNodeById(Graph* graph, int nodeId); 

// Fonction pour libérer la mémoire du graphe et de ses nœuds
void freeGraph(Graph* graph); 

// Fonction pour calculer la distance de Manhattan entre deux nœuds
int manhattanDistance(Node* a, Node* b); 

// Fonction pour vérifier si un nœud est dans la liste spécifiée
int isInList(NodeList list, Node* node); 

// Reconstruire le chemin à partir du nœud objectif
NodeList reconstructPath(Node* goal);

// Fonction pour libérer la mémoire des nœuds
void freeNodes(NodeList list); 

// Fonction pour vérifier si un nœud est dans le tas spécifié
int isInHeap(Heap* heap, int node_id); 

// Fonction principale pour l'algorithme A*
void aStar(Graph* graph); 

#endif  // ASTAR_H
