from .core import coreGraph
from .cmodule import *
import numpy as np
from typing import Tuple,List

class PathAlgs(coreGraph):
    """class containing definitions of algorithms related to path finding."""
    
    def __init__(self):
        super().__init__()
    def find_broad_first_path(self, start:int, end:int)->Tuple[int,np.array]:
        """finds a path between two vertices using breadth first search
            If path does not exists, throws an error
        Args:
            start (int): source vertex
            end (int): destination vertex

        Returns:
            Tuple[int,np.array]: tuple of path length and array of vertices in the path
        """
        n,m,v_ptrs,neighs,weighted,weights=self.restructure()
        if 0>start>=n or 0>end>=n:
            raise ValueError("start and end vertices must be less than the number of vertices in the graph")
        return py_BFS(n,m,v_ptrs,neighs,weighted,weights,start,end)



    def shortest_path(self, start:int, end:int)->Tuple[float,np.array]:
        """finds the shortest path between start and end using Dijkstra's algorithm
            the weights of the graph must be non-negative, otherwise throws an error
            If path does not exists, throws an error
        
        Args:
            start (int): source vertex
            end (int): destination vertex

        Returns:
            Tuple[float,np.array]: tuple of path cumulative weight and array of vertices in the path
        """
        n,m,v_ptrs,neighs,weighted,weights=self.restructure()
        if 0>start>=n or 0>end>=n:
            raise ValueError("start and end vertices must be less than the number of vertices in the graph")
        if not self.weighted:
            raise ValueError("graph must be weighted to use shortest_path")
        return py_Dijkstra(n,m,v_ptrs,neighs,weighted,weights,start,end)
    def shortest_universal_path(self, start:int, end:int)->Tuple[float,np.array]:
        """finds the shortest path between start and end using Bellman-Ford's algorithm
            the weights of the graph can be negative, but there must not be any negative weight cycles in the graph, otherwise throws an error
            If path does not exists, throws an error
            
        Args:
            start (int): source vertex
            end (int): destination vertex

        Returns:
            Tuple[float,np.array]: tuple of path cumulative weight and array of vertices in the path
        """
        n,m,v_ptrs,neighs,weighted,weights=self.restructure()
        if 0>start>=n or 0>end>=n:
            raise ValueError("start and end vertices must be less than the number of vertices in the graph")
        if not self.weighted:
            raise ValueError("graph must be weighted to use shortest_universal_path")
        return py_Bellman_Ford(n,m,v_ptrs,neighs,weighted,weights,start,end)