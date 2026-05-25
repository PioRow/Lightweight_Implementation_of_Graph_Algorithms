# Lightweight Implementation of Graph Algorithms (LIGA)

## About
LIGA is a lightweight library for python, implemented in C.
It allows to model complex problems using Graphs, and solve them utilizing various algorithms, without overhead of unwanted functionalities other libraries present.

## Features
* **Graph manipulation**: Build graph, add vertecies, manipulate edges (add,delete, change weights). Default definition is Directed
* **Shortest paths**: allows to find shortest path bettween two nodes when:
    * Graph is unweighted (BFS)
    * all weights are non-negative (Dijkstra)
    * there is no negative cycle (Bellman-Frod)
* **Topological properites**:
    * check whether graph has a cycle (is DAG)
    * sort the vertecies topologically
* **Structures within**:
    * find minimal spanning tree (Prim)

## Author and Contributor(s)
**Author and maintainer** [Piotr Rowicki](https://github.com/PioRow)

## Exapmles and Documentation

```Python
import LIGA

g=LIGA.LIGraph(n,weighted=True) # n= initial number of vertecies
g.add_edge(u,v,w) ## weight addition
. 
.
.
hasCycle= g.cycle_detection()
```

```Python
import LIGA

g=LIGA.LIGraph(n,weighted=True) # n= initial number of vertecies
g.add_edge(u,v,w) ## weight addition
. 
.
.
path,length= g.shortest_path(u1,u2) ## shortest path using Dijkstra
# path is an numpy array, length is double
```

## Instalation
Package requries Python 3.12+ and **numpy**>=2.0.0
The source code depends on data structes, from [STC](https://github.com/stclib/STC/tree/main) library.


To install the package, clone the source repository
```Bash
git clone https://github.com/PioRow/Lightweight_Implementation_of_Graph_Algorithms.git
cd Lightweight_Implementation_of_Graph_Algorithms/LIGA
pip3 install .
```


