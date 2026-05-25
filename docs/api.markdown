---
layout: page
title: "Python API"
permalink: /API
---

After installation, u need to import main package
```python
import LIGA
```

it contains main object, on which all the algorithms are based:LIGRAPH
```python
G = g=LIGA.LIGraph(8,weighted=False) # number of nodes, bool whether graph has weighted edges
```
After creating the graph you can add, delete or modify edges
```python
G.add_edge(0,2,weight=3) # adds edge 1->2 with weigh 3
G.add_edge(0,1,weight=4)
G.delete_edge(0,2) #delete edge 0->2
G.add_edge(0,1,weight=2) # edge already exists, so its modified to weight 2
```
After creating the Graph, you can call various algorithms on them like:
path finding
```python 
path,cumulative_weight=G.shortest_universal_path(0,5) #comutes shortest path between nodes 0 and 5 using Bellman-Ford algorithm
# path: array of nodes in oreder of traversal
# cumulative_weight: sum of all the weights on the path
```
Cycle detection:
```python 
has_path=G.cycle_detection() #checks whether the graph is acyclic
# has_path: boolean value of 'G has a cycle'
```

Minimal spanning tree:
```python
G_mst=G.get_minimal_spanning_tree() # creates a copy of G, containing only edges of MST

```

For the whole documentation, checkout docstrings available in the source code.

