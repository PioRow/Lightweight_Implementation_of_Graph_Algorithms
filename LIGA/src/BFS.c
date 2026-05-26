#include "common.h"
#define i_key size_t
#define i_tag st
#include <stc/queue.h>
#ifdef _OPENMP
#include <omp.h>
#endif

size_t* BFS(LIGraph *G, size_t start, size_t end, size_t* path_length)
{
   size_t* from_table=(size_t*)malloc(G->num_nodes*sizeof(size_t));
    if (!from_table) return NULL;
    size_t* visited=(size_t*)calloc(G->num_nodes,sizeof(size_t));
    if (!visited) {
        free(from_table);
        return NULL;
    }
    #pragma omp parallel for
    for(size_t i=0;i<G->num_nodes;i++){
        from_table[i]=G->num_nodes;
        visited[i]=0;
    }
    queue_st q= queue_st_init();
    queue_st_push(&q,start);
    visited[start]=1;
    
    while(!queue_st_is_empty(&q)){
        size_t node= *queue_st_front(&q);
        queue_st_pop(&q);
        if(node==end){
            break;
        }
        size_t* neighbors;
        size_t start_n,end_n;
        get_neighbors(G,node,&neighbors,&start_n,&end_n);
        for(size_t i=start_n;i<end_n;i++){
            size_t neighbor=neighbors[i];
            if(visited[neighbor]==0){
                visited[neighbor]=1;
                from_table[neighbor]=node;
                queue_st_push(&q,neighbor);
            }
        }
    }
    if (visited[end]==0){
        free(from_table);
        free(visited);
         queue_st_drop(&q);
        *path_length=G->num_nodes;
        return NULL;
    }
    size_t curr=end;
    size_t length=1;
    while(curr!=start){
        curr=from_table[curr];
        length++;
    }
    *path_length=length;
    
    size_t* path=(size_t*)malloc(length*sizeof(size_t));
    if (!path) {
        return NULL;
    }
    for(size_t i=0;i<length;i++){
        path[length-1-i]=end;
        end=from_table[end];
    }
    free(from_table);
    free(visited);
    queue_st_drop(&q);
    
    return path;
}