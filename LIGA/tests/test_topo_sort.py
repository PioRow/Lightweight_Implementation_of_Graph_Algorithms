import pytest
import LIGA
import numpy as np


@pytest.fixture
def cycle_graph():
    g=LIGA.LIGraph(3)
    g.add_edge(0,1)
    g.add_edge(0,2)
    g.add_edge(1,2)
    g.add_edge(2,0)
    return g

@pytest.fixture
def acyclic_graph():
    g=LIGA.LIGraph(3)
    g.add_edge(0,1)
    g.add_edge(1,2)
    return g

def test_return_has_all_vertices(acyclic_graph):
    sorted_vertices=acyclic_graph.topological_sort()
    assert set(sorted_vertices)==set(range(3))
    assert len(sorted_vertices)==3
    
def test_return_has_correct_order(acyclic_graph):
    sorted_vertices=acyclic_graph.topological_sort()
    np.testing.assert_array_equal(sorted_vertices,np.array([0,1,2]))
    
def test_is_cyclic(cycle_graph):
    with pytest.raises(RuntimeError):
        cycle_graph.topological_sort()