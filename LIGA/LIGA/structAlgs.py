from .core import coreGraph
from .cmodule import *
import numpy as np
from typing import Tuple

class structAlgs(coreGraph):
    """class containing definitions of algorithms related finding structural properties."""
    
    def __init__(self):
        super().__init__()
    
    def minimum_spanning_tree_edges(self)->Tuple[np.array,np.array,float]:
        """
        returns the edges in the minimum spanning tree, using Prim's algorithm.
        the graph must be undirected, otherwise throws an error.
        to obtain an undirected graph, add edges in both directions with the same weight.
        if graph is not connected, throws an error.
        
        if graph has no weights, treats all edges as having weight 1.
        
        Args:
            None
        Returns:
            Tuple[np.array,np.array,float]: tuple of two arrays, the first array contains the source vertices,
             the second array contains the destination vertices of the edges in the minimum spanning tree.
             float: the total weight of the minimum spanning tree.
        
        """
        n,m,v_ptrs,neighs,weighted,weights=self.restructure()
        return py_min_spanning_tree(n,m,v_ptrs,neighs,weighted,weights)