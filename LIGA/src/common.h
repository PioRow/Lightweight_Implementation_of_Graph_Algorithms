
typedef struct {
    int num_nodes;
    int num_edges;
    int* nodes;  // start of node in adj_list
    int* adj_list; // flattened adjencency lists
    double* weights; //flattened weights of edges
} LIGA_graph;

void get_neighbors(LIGA_graph* G,int node, int** list, int* start,int *end);
