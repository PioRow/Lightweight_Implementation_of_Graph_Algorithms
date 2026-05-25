#include "common.h"

typedef struct {
    size_t node;
    double weight;
} HeapItem;
int HeapItem_cmp(const HeapItem* a, const HeapItem* b) {
    if (a->weight < b->weight) return 1;
    if (a->weight > b->weight) return -1;
    return 0;
}
#define i_key HeapItem
#define i_tag min
#define i_cmp HeapItem_cmp
#include <stc/pqueue.h>

#define i_key size_t
#define i_tag st
#include <stc/hashset.h>
int* Prim(LIGraph *G,size_t **src,size_t**trgt,double * cum_weight)
{
    if(G->num_edges==0){
        *cum_weight=0.0;
        return NULL;
    }
    double * dist=(double*)malloc(G->num_nodes*sizeof(double));
    if(!dist)
    {
        *cum_weight=INFINITY;
        return NULL;
    }

    size_t * parent=(size_t*)malloc(G->num_nodes*sizeof(size_t));
    if(!parent)
    {
        free(dist);
        *cum_weight=INFINITY;
        return NULL;
    }
    for(size_t i=0;i<G->num_nodes;i++)
    {
        dist[i]=INFINITY;
        parent[i]=G->num_nodes;
    }
    pqueue_min pq = pqueue_min_init();
    hset_st visited= hset_st_init();
    pqueue_min_push(&pq, (HeapItem){0,0.0});
    dist[0]=0.0;
    *src=(size_t*)malloc((G->num_nodes-1)*sizeof(size_t));
    *trgt=(size_t*)malloc((G->num_nodes-1)*sizeof(size_t));
    if(!*src || !*trgt)
    {
        free(dist);
        free(parent);
        free(*src);
        free(*trgt);
        pqueue_min_drop(&pq);
        hset_st_drop(&visited);
        *cum_weight=INFINITY;
        return NULL;
    }
    while(!pqueue_min_is_empty(&pq))
    {
        HeapItem item= *pqueue_min_top(&pq);
        pqueue_min_pop(&pq);
        if(hset_st_contains(&visited, item.node))
        {
            continue;
        }
        hset_st_insert(&visited, item.node);
        size_t* neighbors;
        double* weights;
        size_t start_n,end_n;
        get_neighbors(G,item.node,&neighbors,&start_n,&end_n);
        get_weights(G,item.node,&weights,&start_n,&end_n);
        if(weights==NULL)
        {
            weights=(double*)malloc((end_n-start_n)*sizeof(double));
            if(!weights)
            {
                free(dist);
                free(parent);
                free(*src);
                free(*trgt);
                pqueue_min_drop(&pq);
                hset_st_drop(&visited);
                *cum_weight=INFINITY;
                return NULL;
            }
            for(size_t i=start_n;i<end_n;i++)
            {
                weights[i-start_n]=1.0;
            }
        }
        for(size_t i=start_n;i<end_n;i++)
        {
            size_t neighbor=neighbors[i];
            double d=weights[i];
            if(!hset_st_contains(&visited, neighbor) && weights[i]<dist[neighbor])
            {
                dist[neighbor]=weights[i];
                parent[neighbor]=item.node;
                pqueue_min_push(&pq, (HeapItem){neighbor,dist[neighbor]});
            }
        }
    }
    for(size_t i=1;i<G->num_nodes;i++)
    {
        if(parent[i]==G->num_nodes)
        {
            free(dist);
            free(parent);
            free(*src);
            free(*trgt);
            pqueue_min_drop(&pq);
            hset_st_drop(&visited);
            *cum_weight=INFINITY;
            return NULL; 
        }
    }
    *cum_weight=0.0;
    
    for(size_t i=1;i<G->num_nodes;i++)
    {
        (*src)[i-1]=parent[i];
        (*trgt)[i-1]=i;
        *cum_weight+=dist[i];
    }
    free(dist);
    free(parent);
    pqueue_min_drop(&pq);
    hset_st_drop(&visited);
    return (int*)cum_weight;
}