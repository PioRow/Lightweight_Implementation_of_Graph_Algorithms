from .core import coreGraph
from .cmodule import *
import numpy as np
from typing import Tuple,List

class sortAlgs(coreGraph):
    """class containing definitions of algorithms related to topological sorting."""
    
    def __init__(self):
        super().__init__()
    
    def topological_sort(self)->np.array:
        """returns a topological ordering of the vertices in the graph
            if sorting is not possible, throws an error
        Args:
            None

        Returns:
            np.array: array of vertices in topological order
        """
        n,m,v_ptrs,neighs,weighted,weights=self.restructure()
        return py_topological_sort(n,m,v_ptrs,neighs,weighted,weights)
    
    def cycle_detection(self)->bool:
        """detect if there is a cycle in the graph.
            if there is a cycle, returns True otherwise False"""
        n,m,v_ptrs,neighs,weighted,weights=self.restructure()
        return py_cycle_detection(n,m,v_ptrs,neighs,weighted,weights)