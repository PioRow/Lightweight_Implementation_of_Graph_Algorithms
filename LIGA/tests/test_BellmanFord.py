import pytest
import LIGA



@pytest.fixture
def graph():
    g=LIGA.LIGraph(7,weighted=True)
    g.add_edge(0,1,weight=1)
    g.add_edge(1,2,weight=1)
    g.add_edge(2,3,weight=1)
    g.add_edge(3,4,weight=1)
    g.add_edge(0,5,weight=2)
    g.add_edge(5,4,weight=-3)
    return g

def test_min_length(graph):
    _,length=graph.shortest_universal_path(0,4)
    assert length==-1
    
    
def test_path_contains_start_and_end(graph):
    path,_=graph.shortest_universal_path(0,4)
    assert path[0]==0 and path[-1]==4
    
    
def test_shortest_path(graph):
    path,_=graph.shortest_universal_path(0,4)
    assert set(path)==set([0,4,5])
    
def test_no_path(graph):
    with pytest.raises(RuntimeError):
        graph.shortest_universal_path(0,6)
        

def test_negative_cycle(graph):
    graph.add_edge(4,0,weight=-3)
    with pytest.raises(RuntimeError):
        graph.shortest_universal_path(0,4)