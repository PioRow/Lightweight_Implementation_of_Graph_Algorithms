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


size_t* reconstruct_path(size_t start, size_t end, size_t* from_table,size_t* len){
    size_t curr=end;
    size_t length=1;
    while(curr!=start){
        curr=from_table[curr];
        length++;
    }
    *len=length;
    size_t* path=(size_t*)malloc(length*sizeof(size_t));
    if (!path) {
        return NULL;
    }
    curr=end;
    for(size_t i=0;i<length;i++){
        path[length-1-i]=curr;
        curr=from_table[curr];
    }
    return path;
}