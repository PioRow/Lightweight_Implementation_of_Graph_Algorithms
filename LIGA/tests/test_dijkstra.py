import pytest
import LIGA



@pytest.fixture
def graph():
    g=LIGA.LIGraph(7,weighted=True)
    g.add_edge(0,1,weight=1.0)
    g.add_edge(1,2,weight=1.0)
    g.add_edge(2,3,weight=1.0)
    g.add_edge(3,4,weight=1.0)
    g.add_edge(0,5,weight=5.0)
    g.add_edge(5,4,weight=1.0)
    return g

def test_min_length(graph):
    _,cost=graph.shortest_path(0,4)
    assert cost==4.0
    
    
def test_path_contains_start_and_end(graph):
    path,_=graph.shortest_path(0,4)
    assert path[0]==0 and path[-1]==4
def test_shortest_path(graph):
    path,_=graph.shortest_path(0,4)
    assert set(path)==set([0,1,2,3,4])
    
def test_no_path(graph):
    with pytest.raises(RuntimeError):
        graph.shortest_path(0,6)

def test_negative_weight(graph):
    graph.add_edge(6,4,weight=-1.0)
    with pytest.raises(RuntimeError):
        graph.shortest_path(0,4)