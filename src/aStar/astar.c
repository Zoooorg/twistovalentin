#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../heap/heap.h"
#include "astar.h"

// Initialisation du graphe
Graph* initializeGraph(int numNodes) {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	if (graph == NULL) {
		// Gestion de l'erreur d'allocation mémoire
		exit(EXIT_FAILURE);
	}
	graph->numNodes = numNodes;
	graph->nodes = (Node**)malloc(numNodes * sizeof(Node*));
	if (graph->nodes == NULL) {
		// Gestion de l'erreur d'allocation mémoire
		free(graph);
		exit(EXIT_FAILURE);
	}
	// Initialiser tous les éléments du tableau à NULL
	for (int i = 0; i < numNodes; i++) {
		graph->nodes[i] = NULL;
	}
	return graph;
}

// Fonction pour ajouter un nœud au graphe
void addNodeToGraph(Graph* graph, Node* node) {
	if (node->id < 0 || node->id >= graph->numNodes) {
		fprintf(stderr, "Error: Invalid node ID\n");
		return;
	}
	graph->nodes[node->id] = node;
}

// Fonction pour récupérer un nœud par son identifiant
Node* getNodeById(Graph* graph, int nodeId) {
	if (graph == NULL || nodeId < 0 || nodeId >= graph->numNodes) {
		fprintf(stderr, "Error: Invalid graph or node ID\n");
		return NULL;
	}
	Node* node = graph->nodes[nodeId];
	if (node == NULL) {
		fprintf(stderr, "Error: Node with ID %d does not exist\n", nodeId);
		return NULL;
	}
	return node;
}

// Fonction pour libérer la mémoire du graphe et de ses nœuds
void freeGraph(Graph* graph) {
	if (graph == NULL) {
		return;
	}
	for (int i = 0; i < graph->numNodes; i++) {
		if (graph->nodes[i] != NULL) {
			free(graph->nodes[i]);
		}
	}
	free(graph->nodes);
	free(graph);
}

// Fonction pour calculer la distance de Manhattan entre deux nœuds
int manhattanDistance(Node* a, Node* b) {
	return abs(a->x - b->x) + abs(a->y - b->y);
}

// Fonction pour ajouter un noeud à une liste de noeud
NodeList addToNodeList(NodeList list, Node* node) {
	if (node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	node->next = list;

	return node;
}

// Fonction pour vérifier si un nœud est dans la liste spécifiée
int isInList(NodeList list, Node* node) {
	Node* current = list;
	while (current != NULL) {
		if (current->x == node->x && current->y == node->y) {
			return 1;
		}
		current = current->next;
	}
	return 0;
}


// Fonction pour vérifier si un nœud est dans le tas spécifié
int isInHeap(Heap* heap, int node_id) {
	for (int i = 0; i < heap->nbElements; i++) {
		if (heap->heap[i] == node_id) {
			return 1;
		}
	}
	return 0;
}

// Reconstruire le chemin à partir du nœud objectif
NodeList reconstructPath(Node* goal) {
	NodeList path = NULL;
	Node* current = goal;
	while (current != NULL) {
		path = addToNodeList(path, current);
		current = current->parent;
	}
	return path;
}

// Fonction pour libérer la mémoire des nœuds
void freeNodes(NodeList list) {
	Node* current = list;
	Node* next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
}


// Fonction principale pour l'algorithme A*
void aStar(Graph* graph) {
	Node* start = graph->start;
	Node* goal = graph->goal;
	int N = graph->numNodes;
	// Initialisation de la liste ouverte et de la liste fermée
	Heap *openList = createHeap(N);
	NodeList closedList = NULL;

	// Mettre le nœud de départ dans la liste ouverte
	start->g = 0;
	start->h = manhattanDistance(start, goal);
	start->f = start->g + start->h;
	insertHeap(openList, start->id, start->f);

	// Tant que la liste ouverte n'est pas vide
	while (openList->nbElements != 0) {
		// Trouver le nœud avec le coût total le plus bas dans la liste ouverte
		int current_id = removeElement(openList);
		Node* current = getNodeById(graph, current_id);

		// Si le nœud actuel est le nœud objectif, terminer la recherche
		if (current->x == goal->x && current->y == goal->y) { 
			// Reconstruction du chemin
			printf("Chemin trouvé !\n");
			NodeList path = reconstructPath(current);
			// Affichage du chemin (à adapter selon vos besoins)
			printf("Chemin : ");
			Node* node = path;
			while (node != NULL) {
				printf("(%d, %d) ", node->x, node->y);
				node = node->next;
			}
			printf("\n");
			// Libérer la mémoire du chemin
			break;

		}

		// Générer les successeurs du nœud actuel
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				// Ne pas considérer le nœud actuel comme un successeur
				if (i == 0 && j == 0) continue;

				int newX = current->x + i;
				int newY = current->y + j;

				// Vérifier si le successeur est valide
				if (newX >= 0 && newX < graph->MAP_WIDTH && newY >= 0 && newY < graph->MAP_HEIGHT) {

					// Vérifier si le successeur est un obstacle		
					Node* currentSucessor = getNodeById(graph, current_id);
					if (currentSucessor->ground == '.') {
						continue;
					}

					// Créer un nouveau nœud successeur
					Node* successor = (Node*)malloc(sizeof(Node));
					successor->x = newX;
					successor->y = newY;
					successor->id = newY * graph->MAP_WIDTH + newX;
					successor->parent = current;

					// Calculer les coûts g, h et f du successeur
					successor->g = current->g + 1; // Coût uniforme, car tous les mouvements coûtent 1
					successor->h = manhattanDistance(successor, goal);
					successor->f = successor->g + successor->h;

					// Si le successeur est déjà dans la liste ouverte et a un coût total inférieur, ignorer
					if (isInHeap(openList, successor->id)) {
						// Trouver l'élément correspondant dans la liste ouverte
						Node* openNode = getNodeById(graph, successor->id);
						if (successor->f >= openNode->f) {
							// Le successeur a un coût total plus élevé que l'élément correspondant dans la liste ouverte
							free(successor); // Libérer la mémoire du nœud successeur
							continue;
						} else {
							// Mettre à jour les informations du nœud existant dans la liste ouverte avec les nouvelles valeurs du successeur
							openNode->g = successor->g;
							openNode->h = successor->h;
							openNode->f = successor->f;
							openNode->parent = successor->parent;
							free(successor); // Libérer la mémoire du nœud successeur
							continue;
						}
					} else if (isInList(closedList, successor)) {
						// Le successeur est dans la liste fermée
						Node* closedNode = getNodeById(graph, successor->id); 
						if (successor->f >= closedNode->f) {
							// Le successeur a un coût total plus élevé que l'élément correspondant dans la liste fermée
							free(successor); // Libérer la mémoire du nœud successeur
							continue;
						} else {
							// Ajouter le successeur à la liste ouverte
							insertHeap(openList, successor->id, successor->f);
							closedNode->g = successor->g;
							closedNode->h = successor->h;
							closedNode->f = successor->f;
							closedNode->parent = successor->parent;
							free(successor); // Libérer la mémoire du nœud successeur
							continue;
						}
					} else {
						// Le successeur n'est ni dans la liste ouverte ni dans la liste fermée, l'ajouter à la liste ouverte
						insertHeap(openList, successor->id, successor->f);
						Node* newNode = getNodeById(graph, successor->id);
						newNode->g = successor->g;
						newNode->h = successor->h;
						newNode->f = successor->f;
						newNode->parent = successor->parent;
						free(successor); // Libérer la mémoire du nœud successeur
						continue;

					}
				}
			}
		}

		// Ajouter le nœud actuel à la liste fermée
		closedList = addToNodeList(closedList, current);
	}

	// Libérer la mémoire des nœuds et des listes
	freeHeap(openList);
	//freeNodes(closedList);
}
