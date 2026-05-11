#ifndef LIGA_GRAPH_H
#define LIGA_GRAPH_H
#include <stdlib.h>
#include <math.h>
typedef struct {
    size_t num_nodes;
    size_t num_edges;
    size_t* nodes;  // start of node in adj_list
    size_t* adj_list; // flattened adjencency lists
    double* weights;
    int is_weighted; //flattened weights of edges
} LIGraph;
void get_neighbors(LIGraph *G,size_t node, size_t** list, size_t* start,size_t *end);
void get_weights(LIGraph *G,size_t node, double** list, size_t* start,size_t *end);
size_t* BFS(LIGraph *G, size_t start, size_t end, size_t* path_length);
size_t* cycle_detection(LIGraph *G,int* has_cycle);
size_t* topological_sort(LIGraph *G);
size_t* Dijkstra(LIGraph *G, size_t start, size_t end, double* cum_weight,size_t* len);
size_t* Bellman_Ford(LIGraph* G,size_t start,size_t end, double* distance,size_t*len);
size_t* reconstruct_path(size_t start, size_t end, size_t* from_table,size_t* len);

void validate_dijkstra_weights(LIGraph *G,int* flag);


#endif