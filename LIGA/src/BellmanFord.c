#include "common.h" 
#ifdef _OPENMP
#include <omp.h>
#endif




size_t* Bellman_Ford(LIGraph* G,size_t start,size_t end, double* res_dist,size_t*len){
    
    double* dist=(double*)malloc(G->num_nodes*sizeof(double));
    
    if(!dist) return NULL;
    size_t* from_table=(size_t*)malloc(G->num_nodes*sizeof(size_t));
    if(!from_table){
        free(dist);
        return NULL;
    }
    #pragma omp parallel for
    for(size_t i=0;i<G->num_nodes;i++){
        dist[i]=INFINITY;
        from_table[i]=G->num_nodes;
    }
    dist[start]=0.;
    for(size_t i=0;i<(G->num_nodes-1);i++){
        
        for(size_t node=0;node<G->num_nodes;node++){
            size_t n_start,n_end;
            size_t* neighbors;
            double * weights;
           
            get_neighbors(G,node,&neighbors,&n_start,&n_end);
            get_weights(G,node,&weights,&n_start,&n_end);
            for(size_t j=n_start;j<n_end;j++){

                size_t neighbor=neighbors[j];
                double w=weights[j];
                if(dist[node]+w<dist[neighbor]){
                    dist[neighbor]=dist[node]+w;
                    from_table[neighbor]=node;
                }
            }
        }
    }

    if(dist[end]==INFINITY){
        free(dist);
        free(from_table);
        return NULL;
    }
    for(size_t node=0;node<G->num_nodes;node++){
        size_t n_start,n_end;
        size_t* neighbors;
        double * weights;
        get_neighbors(G,node,&neighbors,&n_start,&n_end);
        get_weights(G,node,&weights,&n_start,&n_end);
        for(size_t j=n_start;j<n_end;j++){
            size_t neighbor=neighbors[j];
            double w=weights[j];
            if(dist[node]+w<dist[neighbor]){
                free(dist);
                free(from_table);
                return NULL;
            } 
        }
    }
    *res_dist=dist[end];
    size_t* path=reconstruct_path(start,end,from_table,len);
    free(dist);
    free(from_table);
    return path;
}