#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct Node {
int destination;
int weight;
struct Node* next;
};
struct Graph {
int V;
struct Node** adjLists;
};
struct Node* createNode(int dest, int weight) {
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
newNode->destination = dest;
newNode->weight = weight;
newNode->next = NULL;
return newNode;
}
struct Graph* createGraph(int V) {
struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
graph->V = V;
graph->adjLists = (struct Node*)malloc(V * sizeof(struct Node));
for (int i = 0; i < V; ++i) {
graph->adjLists[i] = NULL;
}
return graph;
}
void addEdge(struct Graph* graph, int src, int dest, int weight) {
struct Node* newNode = createNode(dest, weight);
newNode->next = graph->adjLists[src];
graph->adjLists[src] = newNode;
newNode = createNode(src, weight);
newNode->next = graph->adjLists[dest];
graph->adjLists[dest] = newNode;
}
void printGraph(struct Graph* graph) {
for (int i = 0; i < graph->V; ++i) {
struct Node* temp = graph->adjLists[i];
printf("Adjacency list of vertex %d:\n", i);
while (temp) {
printf("(%d, %d) -> ", temp->destination, temp->weight);
temp = temp->next;
}
printf("NULL\n");
}
}
int minDistance(int dist[], int sptSet[], int V) {
int min = INT_MAX, min_index;
for (int v = 0; v < V; ++v) {
if (!sptSet[v] && dist[v] <= min) {
min = dist[v];
min_index = v;
}
}
return min_index;
}
void printPath(int parent[], int j) {
if (parent[j] == -1) {
printf("%d ", j);
return;
}
printPath(parent, parent[j]);
printf("%d ", j);
}
void printSolution(int dist[], int n, int parent[]) {
int src = 0;
printf("Vertex \t\t Distance\tPath\n");
for (int i = 1; i < n; ++i) {
printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
printPath(parent, i);
}
}
void dijkstra(struct Graph* graph, int src, int goal) {
int V = graph->V;
int dist[V];
int sptSet[V];
int parent[V];
for (int i = 0; i < V; ++i) {
dist[i] = INT_MAX;
sptSet[i] = 0;
parent[i] = -1;
}
dist[src] = 0;
for (int count = 0; count < V - 1; ++count) {
int u = minDistance(dist, sptSet, V);
sptSet[u] = 1;
struct Node* temp = graph->adjLists[u];
while (temp != NULL) {
int v = temp->destination;
int weight = temp->weight;
if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
dist[v] = dist[u] + weight;
parent[v] = u;
}
temp = temp->next;
}
}
printSolution(dist, V, parent);
// Print the shortest path from src to goal
printf("\nShortest Path from %d to %d: ", src, goal);
printPath(parent, goal);
printf("\n");
}
int main() {
int V, E; // Number of vertices and edges
printf("Enter the number of vertices: ");
scanf("%d", &V);
struct Graph* graph = createGraph(V);
printf("Enter the number of edges: ");
scanf("%d", &E);
printf("Enter the edges (source destination weight):\n");
for (int i = 0; i < E; ++i) {
int src, dest, weight;
printf("Enter edge %d: ", i + 1);
scanf("%d %d %d", &src, &dest, &weight);
addEdge(graph, src, dest, weight);
}
printf("Adjacency list representation of the graph:\n");
printGraph(graph);
int startVertex, goalVertex;
printf("\nEnter the starting vertex: ");
scanf("%d", &startVertex);
printf("Enter the goal vertex: ");
scanf("%d", &goalVertex);
dijkstra(graph, startVertex, goalVertex);
// Free allocated memory
for (int i = 0; i < V; ++i) {
struct Node* temp = graph->adjLists[i];
while (temp) {
struct Node* next = temp->next;
free(temp);
temp = next;
}
}
free(graph->adjLists);
free(graph);
return 0;
}