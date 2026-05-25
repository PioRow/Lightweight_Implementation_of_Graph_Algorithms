from .core import coreGraph
from .pathAlgs import PathAlgs
from typing import Tuple,List
from .sortAlgs import sortAlgs
from .structAlgs import structAlgs
class LIGraph(PathAlgs,sortAlgs,structAlgs):
    """ outer class for graph representation and manipulation
        high level representation of the graph is adjacency list.
        For C API, the graph is restructured to a 3 arrays format:
        - vertex_pointers
        - adjacency lists
        - weights 
    """
    def __init__(self, num_vertices:int, weighted:bool=False)->None:
        """Initializes a graph with given nr of verticies
        Args:
            num_vertices (int): number of verticies in the graph
            weighted (bool): whether the graph is weighted default False
        """
        super().__init__()
        self.num_vertices = num_vertices
        self.weighted = weighted
        if weighted:
            self.weights = {i: [] for i in range(num_vertices)}
        self.adjacency_list = {i: [] for i in range(num_vertices)}

    def add_edge(self, u:int, v:int, weight:float=0.0)->None:
        """Adds an edge to the graph.
            if edge already exists, update value
         Args:
            u (int): source vertex
            v (int): destination vertex
            weight (float): weight of the edge, default 0.0, applies only if the graph is weighted
        """
        if v in self.adjacency_list[u]:
             v_index = self.adjacency_list[u].index(v)
             if self.weighted:
                self.weights[u][v_index]=weight
        else:    
            if self.weighted:
                self.weights[u].append(weight)
            self.adjacency_list[u].append(v)
        
    def add_vertex(self)->None:
        """Adds a vertex to the graph
            with no edges.
         Args:
                None
        """
        self.adjacency_list[self.num_vertices] = []
        self.num_vertices += 1
    
    def remove_edge(self, u:int, v:int)->None:
        """Removes an edge from the graph
         Args:
            u (int): source vertex
            v (int): destination vertex
        """
        if v in self.adjacency_list[u]:
            v_index = self.adjacency_list[u].index(v)
            self.adjacency_list[u].pop(v_index)
            if self.weighted:
                self.weights[u].pop(v_index)
        
    def get_neighbors(self, vertex:int)->List[int]:
        """returns neighbors of a given vertex
            If vertex does not exists, throws an error

        Args:
            vertex (int): given vertex

        Returns:
            List[int]: list of its neighbors
        """
        return self.adjacency_list[vertex]
    
    def degree(self, vertex:int)->int:
        """get degree of a vertex
            If vertex does not exists, throws an error
        Args:
            vertex (int): given vertex

        Returns:
            int: degree of vertex
        """
        return len(self.adjacency_list[vertex])
    def get_weight(self, u:int, v:int)->float:
        """return weight of the edge between u and v
            If edge or weight does not exists, throws an error"""
        if v not in self.adjacency_list[u] or not self.weighted:
            raise ValueError("Edge does not exist or graph is not weighted")
        v_index = self.adjacency_list[u].index(v)
        return self.weights[u][v_index]

    def get_min_spanning_tree(self)->'LIGraph':
        """creates a copy of original graph, containing only edges of minimal spanning tree
        the required graph must meet conditions listed in structAlgs.minimum_spanning_tree() method, otherwise throws an error
        the weights of the result graph are the same as the weights of the original.

        Returns:
            LIGraph: a new graph containing only edges of minimal spanning tree
        """
        res=LIGraph(self.num_vertices,self.weighted)
        (src,trgt,cum_weight)=self.minimum_spanning_tree_edges()
        for i in range(len(src)):
            u=src[i]
            v=trgt[i]
            w=self.get_weight(u,v) if self.weighted else 0.0
            res.add_edge(u,v,w)
            res.add_edge(v,u,w)
        return res
        
        