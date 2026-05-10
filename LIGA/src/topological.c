#include "common.h"

#define i_key size_t
#define i_tag st
#include <stc/queue.h>

size_t* base_topo_sort(LIGraph *G,size_t* out_len){
    size_t* in_deg=(size_t*)malloc(G->num_nodes*sizeof(size_t));
    if (!in_deg) return NULL;
    size_t* sorted=(size_t*)malloc(G->num_nodes*sizeof(size_t));
    if(!sorted){
        free(in_deg);
        return NULL;
    }
    for(size_t i=0;i<G->num_nodes;i++){
        in_deg[i]=0;
        sorted[i]=G->num_nodes;
    }
    for(size_t i=0;i<G->num_nodes;i++){
        size_t* neighbors;
        size_t start,end;
        get_neighbors(G,i,&neighbors,&start,&end);
        for(size_t j=start;j<end;j++){
            in_deg[neighbors[j]]++;
        }
    }
    queue_st q=queue_st_init();
    for(size_t i=0;i<G->num_nodes;i++){
        if(in_deg[i]==0){
            queue_st_push(&q,i);
        }
    }
    size_t len=0;
    while(!queue_st_is_empty(&q)){
        size_t node=*queue_st_front(&q);
        queue_st_pop(&q);
        sorted[len++]=node;
        size_t* neighbors;
        size_t start,end;
        get_neighbors(G,node,&neighbors,&start,&end);
        for(size_t j=start;j<end;j++){
            size_t neighbor=neighbors[j];
            in_deg[neighbor]--;
            if(in_deg[neighbor]==0){
                queue_st_push(&q,neighbor);
            }
        }
    }
    queue_st_drop(&q);
    free(in_deg);
    *out_len=len;
    return sorted;
}

size_t* topological_sort(LIGraph *G){
    size_t out_len;
    size_t* sorted=base_topo_sort(G,&out_len);
    if(!sorted) return NULL;
    if(out_len!=G->num_nodes){
        free(sorted);
        return NULL;
    }
    return sorted;
}


size_t* cycle_detection(LIGraph *G,int* has_cycle){
    size_t out_len;
    size_t* sorted=base_topo_sort(G,&out_len);
    if(!sorted) return NULL;
    if(out_len==G->num_nodes){
        *has_cycle=0;
    }else{
        *has_cycle=1;
    };
    return sorted;
}