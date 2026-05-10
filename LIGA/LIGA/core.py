from typing import Tuple,List
import numpy as np

class coreGraph:
    """core graph class, containing base restructuring method for C API.
       Created to be inherited by main LIGraph class and other algorithm classes, to avoid code repetition."""
    def __init__(self)->None:
        self.num_vertices=None
        self.weighted=None
        self.adjacency_list=None
        self.weights=None
        
    
    def restructure(self)->Tuple[int,int,np.array,np.array,bool,np.array]:
        """converts adjacency list representation into 3 vectors, as described in main docs.
            additionally returns vertex and edge counts
        Returns:
            Tuple[int,int,np.array,np.array,bool,np.array]: tuple consisting of:
                - vertex count
                - edge count
                - vertex_pointers
                - flatten adjacency lists
                - is weighted
                - if weighted then weights else None
        """
        n=self.num_vertices
        m=0
        v_ptrs=np.empty(n,dtype=np.uintp)
        flatten_neighs=[]
        flatten_weights=[]
        for idx,u in enumerate(self.adjacency_list):
            v_ptrs[idx]=m
            u_neighs=self.adjacency_list[u]
            flatten_neighs.extend(u_neighs)
            if self.weighted:
                u_weights=self.weights[u]
                flatten_weights.extend(u_weights)
            m+=len(u_neighs)
        return n,m,v_ptrs,np.array(flatten_neighs,dtype=np.uintp),self.weighted,np.array(flatten_weights,dtype=np.float64) if self.weighted else None
    

   