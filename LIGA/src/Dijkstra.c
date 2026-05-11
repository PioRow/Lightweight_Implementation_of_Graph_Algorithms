#include "common.h"

typedef struct {
    size_t node;
    double weight;
} PQItem;
int PQItem_cmp(const PQItem* a, const PQItem* b) {
    if (a->weight < b->weight) return 1;
    if (a->weight > b->weight) return -1;
    return 0;
}
#define i_key PQItem
#define i_tag pqi
#define i_cmp PQItem_cmp
#include <stc/pqueue.h>
size_t* Dijkstra(LIGraph *G, size_t start, size_t end, double* cum_weight,size_t* len){
    double* dist=(double*)malloc(G->num_nodes*sizeof(double));
    if (!dist) return NULL;
    size_t* from_table=(size_t*)malloc(G->num_nodes*sizeof(size_t));
    if (!from_table) {
        free(dist);
        return NULL;
    }
    pqueue_pqi pq = pqueue_pqi_init();
    for(size_t i=0;i<G->num_nodes;i++){
        dist[i]=INFINITY;
        from_table[i]=G->num_nodes;
        
    }
    dist[start]=0.0;
    pqueue_pqi_push(&pq, (PQItem){start,0.0});
    while(!pqueue_pqi_is_empty(&pq)){
        PQItem item= *pqueue_pqi_top(&pq);
        pqueue_pqi_pop(&pq);
        size_t node=item.node;
        double weight=item.weight;
        if(weight>dist[node]){
            continue;
        }
        if(node==end){
            break;
        }
        size_t* neighbors;
        double* weights;
        size_t start_n,end_n;
        get_neighbors(G,node,&neighbors,&start_n,&end_n);
        get_weights(G,node,&weights,&start_n,&end_n);
        for(size_t i=start_n;i<end_n;i++){
            size_t neighbor=neighbors[i];
            if(dist[node]+weights[i]<dist[neighbor]){
                dist[neighbor]=dist[node]+weights[i];
                from_table[neighbor]=node;
                pqueue_pqi_push(&pq, (PQItem){neighbor,dist[neighbor]});
            }
        }
        
    }
    if (dist[end]==INFINITY){
        free(dist);
        free(from_table);
        pqueue_pqi_drop(&pq);
        return NULL;
    }
    *cum_weight=dist[end];
    size_t* path=reconstruct_path(start,end,from_table,len);
    free(dist);
    free(from_table);
    pqueue_pqi_drop(&pq);    
    return path;
}

void validate_dijkstra_weights(LIGraph *G,int* flag){
    if(!G->is_weighted){
        *flag=0;
        return;
    }
    for(size_t i=0;i<G->num_edges;i++){
        if(G->weights[i]<0){
            *flag=0;
            return;
        }
    }
    *flag=1;
    return;
}