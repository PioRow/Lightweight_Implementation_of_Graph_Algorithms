import pytest
import LIGA
import numpy as np


@pytest.fixture
def graph():
    g=LIGA.LIGraph(6,weighted=True)
    g.add_edge(0,1,weight=3)
    g.add_edge(1,0,weight=3)
    g.add_edge(0,3,weight=6)
    g.add_edge(3,0,weight=6)
    g.add_edge(0,5,weight=8)
    g.add_edge(5,0,weight=8)
    
    g.add_edge(1,3,weight=7)
    g.add_edge(3,1,weight=7)
    g.add_edge(1,4,weight=5)
    g.add_edge(4,1,weight=5)
    g.add_edge(1,5,weight=7)
    g.add_edge(5,1,weight=7)
    
    g.add_edge(2,3,weight=2)
    g.add_edge(3,2,weight=2)
    g.add_edge(2,4,weight=3)
    g.add_edge(4,2,weight=3)
    
    g.add_edge(3,4,weight=1)
    g.add_edge(4,3,weight=1)
    
    g.add_edge(4,5,weight=4)
    g.add_edge(5,4,weight=4)
    return g

def test_min_cost(graph):
    _,_,total_weight = graph.minimum_spanning_tree_edges()
    assert total_weight == 15
    
    
    
     