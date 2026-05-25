import pytest
import LIGA



@pytest.fixture
def cycle_graph():
    g=LIGA.LIGraph(3)
    g.add_edge(0,1)
    g.add_edge(1,2)
    g.add_edge(2,0)
    return g

@pytest.fixture
def acyclic_graph():
    g=LIGA.LIGraph(3)
    g.add_edge(0,1)
    g.add_edge(1,2)
    return g

def test_cycle(cycle_graph):
    assert cycle_graph.cycle_detection()==True
    
def test_acyclic(acyclic_graph):
    assert acyclic_graph.cycle_detection()==False