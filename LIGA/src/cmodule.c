#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "common.h"
// PyArray_* functions:
#include <numpy/arrayobject.h>
#include <numpy/ndarrayobject.h>
#include <numpy/ndarraytypes.h>
#include <numpy/arrayscalars.h>
#include <numpy/ufuncobject.h>



LIGraph * py_parse_Graph(PyObject* args){
    LIGraph * g=(LIGraph*)malloc(sizeof(LIGraph));
    if (NULL==g){
        return NULL;
    }
    PyObject* args0 = PyTuple_GetItem(args, 0);
    if (!args0) return NULL;
    PyObject* args1 = PyTuple_GetItem(args, 1);
    if (!args1) return NULL;
    PyObject* args2 = PyTuple_GetItem(args, 2);
    if (!args2) return NULL;
    PyObject* args3 = PyTuple_GetItem(args, 3);
    if (!args3) return NULL;
    PyObject* args4 = PyTuple_GetItem(args, 4);
    if (!args4) return NULL;
    PyObject* args5 = PyTuple_GetItem(args, 5);
    if (!args5) return NULL;

    g->num_nodes = (size_t)PyLong_AsSize_t(args0);
    g->num_edges = (size_t)PyLong_AsSize_t(args1);
    g->is_weighted = (int)PyObject_IsTrue(args4);
    if (!PyArray_Check(args2) || !PyArray_Check(args3) || (g->is_weighted && !PyArray_Check(args5)))
        return PyErr_Format(PyExc_RuntimeError, "expected a numpy array");

    const PyArrayObject* _nodes = (const PyArrayObject*)args2;
    const PyArrayObject* _adj_list = (const PyArrayObject*)args3;
    const PyArrayObject* _weights = g->is_weighted ? (const PyArrayObject*)args5 : NULL;
    if(PyArray_TYPE(_nodes) != NPY_UINTP || PyArray_TYPE(_adj_list) != NPY_UINTP || (g->is_weighted && PyArray_TYPE(_weights) != NPY_DOUBLE))
        return PyErr_Format(PyExc_RuntimeError, "expected arrays of type size_t for nodes and adj_list, and double for weights");

    if (!PyArray_IS_C_CONTIGUOUS(_nodes) || !PyArray_IS_C_CONTIGUOUS(_adj_list) || (g->is_weighted && !PyArray_IS_C_CONTIGUOUS(_weights)))
        return PyErr_Format(PyExc_RuntimeError, "expected contiguous arrays");
    g->nodes = (size_t*)PyArray_DATA(_nodes);
    g->adj_list = (size_t*)PyArray_DATA(_adj_list);
    if (g->is_weighted) 
    {
        g->weights = (double*)PyArray_DATA(_weights);
    } else 
    {
        g->weights = NULL;
    }
    return g;
    
}


PyObject* py_BFS(PyObject* /*self*/, PyObject* args)
{
   if (PyTuple_Size(args) != 8)
        return PyErr_Format(PyExc_RuntimeError, "expected 8 args, got %zd. 6 of those args are the graph parameters", PyTuple_Size(args));
    LIGraph* g = py_parse_Graph(args);
    if (!g) return PyErr_Format(PyExc_RuntimeError, "failed to parse graph parameters");
    // dummy implementation
    PyObject* arg6 = PyTuple_GetItem(args,6);
    PyObject* arg7 = PyTuple_GetItem(args,7);
    if(!arg6 || !arg7){ 
        free(g);
        return PyErr_Format(PyExc_RuntimeError, "failed to get start and end nodes");
    }
    int start = (size_t)PyLong_AsSize_t(arg6);
    int end = (size_t)PyLong_AsSize_t(arg7);
    size_t len=0;
    size_t* path = BFS(g, start, end, &len);
    free(g);
    if (!path) return PyErr_Format(PyExc_RuntimeError, "BFS failed to find a path or encountered an error");
    npy_intp dims[1] = {(npy_intp)len};
    PyObject* res_path=PyArray_SimpleNewFromData(1,dims, NPY_UINTP, path);
    if (!res_path) {
        free(path);
        return PyErr_Format(PyExc_RuntimeError, "failed to create numpy array for path");
    }
    PyArray_ENABLEFLAGS((PyArrayObject*)res_path, NPY_ARRAY_OWNDATA);
    PyObject *py_len = PyLong_FromSize_t(len);
    PyObject* result = PyTuple_Pack(2, res_path, py_len);
    Py_DECREF(py_len);
    Py_DECREF(res_path);
    return result;    
}


PyObject* py_Dijkstra(PyObject* /*self*/, PyObject* args)
{
    if(PyTuple_Size(args) != 8)
        return PyErr_Format(PyExc_RuntimeError, "expected 8 args, got %zd. 6 of those args are the graph parameters", PyTuple_Size(args));
    LIGraph* g = py_parse_Graph(args);
    if (!g) return PyErr_Format(PyExc_RuntimeError, "failed to parse graph parameters");
    PyObject* arg6 = PyTuple_GetItem(args,6);
    PyObject* arg7 = PyTuple_GetItem(args,7);
    if(!arg6 || !arg7){ 
        free(g);
        return PyErr_Format(PyExc_RuntimeError, "failed to get start and end nodes");
    }
    int start = (size_t)PyLong_AsSize_t(arg6);
    int end = (size_t)PyLong_AsSize_t(arg7);
    int flag=1;
    validate_dijkstra_weights(g,&flag);
    if(flag==0){
        free(g);
        return PyErr_Format(PyExc_RuntimeError, "invalid weights: graph is either unweighted or has negative weights");
    }
    double cum_weight=0.0;
    size_t len=0;
    size_t* path = Dijkstra(g, start, end, &cum_weight,&len);
    
    free(g);
    if (!path) return PyErr_Format(PyExc_RuntimeError, "Dijkstra failed to find a path or encountered an error");
    npy_intp dims[1] = {(npy_intp)len};
    PyObject* res_path=PyArray_SimpleNewFromData(1,dims, NPY_UINTP, path);
    if (!res_path) {
        free(path);
        return PyErr_Format(PyExc_RuntimeError, "failed to create numpy array for path");
    }
    PyArray_ENABLEFLAGS((PyArrayObject*)res_path, NPY_ARRAY_OWNDATA);
    PyObject *py_cumweight = PyFloat_FromDouble(cum_weight);
    PyObject* result = PyTuple_Pack(2, res_path, py_cumweight);
    Py_DECREF(py_cumweight);
    Py_DECREF(res_path);
    return result;     
}
PyObject* py_cycle_detection(PyObject* /*self*/, PyObject* args)
{
    if(PyTuple_Size(args) != 6)
        return PyErr_Format(PyExc_RuntimeError, "expected 6 args, got %zd. All of those args are the graph parameters", PyTuple_Size(args));
    LIGraph* g = py_parse_Graph(args);
    if (!g) return PyErr_Format(PyExc_RuntimeError, "failed to parse graph parameters");
    int has_cycle=-1;
    size_t * status=cycle_detection(g,&has_cycle);
    if (!status) return PyErr_Format(PyExc_RuntimeError, "cycle detection failed or encountered an error");
    free(g);
    free(status);
    return PyBool_FromLong(has_cycle);
}
PyObject *py_topological_sort(PyObject* /*self*/, PyObject* args)
{
    if(PyTuple_Size(args) != 6)
        return PyErr_Format(PyExc_RuntimeError, "expected 6 args, got %zd. All of those args are the graph parameters", PyTuple_Size(args));
    LIGraph* g = py_parse_Graph(args);
    if (!g) return PyErr_Format(PyExc_RuntimeError, "failed to parse graph parameters");
    size_t * sorted=topological_sort(g);
    if (!sorted) return PyErr_Format(PyExc_RuntimeError, "topological sort failed or encountered an error (possibly due to a cycle in the graph)");
    npy_intp dims[1] = {(npy_intp)g->num_nodes};
    PyObject* res_sorted=PyArray_SimpleNewFromData(1,dims, NPY_UINTP, sorted);
    if (!res_sorted) {
        free(sorted);
        return PyErr_Format(PyExc_RuntimeError, "failed to create numpy array for sorted nodes");
    }
    
    free(g);
    PyArray_ENABLEFLAGS((PyArrayObject*)res_sorted, NPY_ARRAY_OWNDATA);
    return res_sorted;    
}


PyObject* py_Bellman_Ford(PyObject* /*self*/, PyObject* args)
{
    if(PyTuple_Size(args) != 8)
        return PyErr_Format(PyExc_RuntimeError, "expected 8 args, got %zd. 6 of those args are the graph parameters", PyTuple_Size(args));
    LIGraph* g = py_parse_Graph(args);
    if (!g) return PyErr_Format(PyExc_RuntimeError, "failed to parse graph parameters");
    PyObject* arg6 = PyTuple_GetItem(args,6);
    PyObject* arg7 = PyTuple_GetItem(args,7);
    if(!arg6 || !arg7){ 
        free(g);
        return PyErr_Format(PyExc_RuntimeError, "failed to get start and end nodes");
    }
    int start = (size_t)PyLong_AsSize_t(arg6);
    int end = (size_t)PyLong_AsSize_t(arg7);
    double distance=0.0;
    size_t len=0;
    size_t* path = Bellman_Ford(g, start, end, &distance,&len);
    if (!path) return PyErr_Format(PyExc_RuntimeError, "Bellman-Ford  failed to find a path or encountered an error");
    npy_intp dims[1] = {(npy_intp)len};
    PyObject* res_path=PyArray_SimpleNewFromData(1,dims, NPY_UINTP, path);
    if (!res_path) {
        free(path);
        free(g);
        return PyErr_Format(PyExc_RuntimeError, "failed to create numpy array for path");
    }
    PyObject *py_distance = PyFloat_FromDouble(distance);
    free(g);
    PyObject* result = PyTuple_Pack(2, res_path, py_distance);
    Py_DECREF(res_path);
    Py_DECREF(py_distance);
    return result;
}
PyObject* py_min_spanning_tree(PyObject* /*self*/, PyObject* args)
{    return PyErr_Format(PyExc_RuntimeError, "not implemented yet");
}

static PyMethodDef my_methods[] = {
    {"py_BFS", py_BFS, METH_VARARGS, "py_BFS's docstring"},
    {"py_Dijkstra", py_Dijkstra, METH_VARARGS, "py_Dijkstra's docstring"},
    {"py_cycle_detection", py_cycle_detection, METH_VARARGS, "py_cicle_detection's docstring"},
    {"py_topological_sort", py_topological_sort, METH_VARARGS, "py_topological_sort's docstring"},
    {"py_Bellman_Ford", py_Bellman_Ford, METH_VARARGS, "py_Bellman_Ford's docstring"},
    {"py_min_spanning_tree", py_min_spanning_tree, METH_VARARGS, "py_min_spanning_tree's docstring"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef my_module = {
    PyModuleDef_HEAD_INIT,
    "cmodule",
    "my module's docstring",
    -1,
    my_methods
};
PyMODINIT_FUNC/* PyObject* */ PyInit_cmodule()
{
    PyObject* mod = PyModule_Create(&my_module);
    if (!mod) return NULL;
    import_array();
    return mod;

}

