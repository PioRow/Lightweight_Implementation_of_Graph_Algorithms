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
    
def test_edges(graph):
    sources, dests, _ = graph.minimum_spanning_tree_edges()
    edges = (zip(sources,dests))
    set_edges=set()
    for u,v in edges:
        if u<v:
            set_edges.add((u,v))
        else:
            set_edges.add((v,u))
    expected_edges = set([(0,1),(1,4),(2,3),(3,4),(4,5)])
    assert set_edges == expected_edges
    
def test_new_has_edges(graph):
    mst_graph = graph.get_min_spanning_tree()
    assert isinstance(mst_graph, LIGA.LIGraph)
    sources, dests, _ = mst_graph.minimum_spanning_tree_edges()
    sum=0.0
    for(u,v) in zip(sources,dests):
        assert v in mst_graph.get_neighbors(u)
        assert mst_graph.get_weight(u,v) == graph.get_weight(u,v)
        sum+=mst_graph.get_weight(u,v)
    assert sum == 15
    
def test_new_no_extra_edges(graph):
    mst_graph= graph.get_min_spanning_tree()
    edge_cnt=0
    for u in range(mst_graph.num_vertices):
        for v in mst_graph.get_neighbors(u):
            edge_cnt+=1
    assert edge_cnt == 2*5

     