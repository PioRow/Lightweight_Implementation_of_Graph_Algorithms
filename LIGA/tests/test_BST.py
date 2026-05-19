import pytest
import LIGA



@pytest.fixture
def graph():
    g=LIGA.LIGraph(7,weighted=False)
    g.add_edge(0,1)
    g.add_edge(1,2)
    g.add_edge(2,3)
    g.add_edge(3,4)
    g.add_edge(0,5)
    g.add_edge(5,4)
    return g

def test_min_length(graph):
    _,length=graph.find_broad_first_path(0,4)
    assert length==3
    
    
def test_path_contains_start_and_end(graph):
    path,_=graph.find_broad_first_path(0,4)
    assert path[0]==0 and path[-1]==4
def test_shortest_path(graph):
    path,_=graph.find_broad_first_path(0,4)
    assert set(path)==set([0,4,5])
    
def test_no_path(graph):
    with pytest.raises(RuntimeError):
        graph.find_broad_first_path(0,6)

