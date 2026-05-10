#include "common.h"

void get_neighbors(LIGraph *G,size_t node, size_t** list, size_t* start,size_t *end)
{
    *list= G->adj_list;
    *start=G->nodes[node];
    if(node==G->num_nodes-1){
        *end=G->num_edges;
    }else{
        *end=G->nodes[node+1];
    }

}
void get_weights(LIGraph *G,size_t node, double** list, size_t* start,size_t *end)
{
    if(G->is_weighted){
        *list= G->weights;
        *start=G->nodes[node];
        if(node==G->num_nodes-1){
            *end=G->num_edges;
        }else{
            *end=G->nodes[node+1];
        }
    }else{
        *list=NULL;
    }
}
size_t get_degree(LIGraph *G,size_t node){
    size_t start=G->nodes[node];
    size_t end;
    if(node==G->num_nodes-1){
        end=G->num_edges;
    }else{
        end=G->nodes[node+1];
    }
    return end-start;
}