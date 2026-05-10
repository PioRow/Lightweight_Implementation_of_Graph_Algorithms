import setuptools

import numpy

setuptools.setup(
    name="LIGA",
    packages=setuptools.find_packages(),
    ext_modules=[
        setuptools.Extension(
            "LIGA.cmodule",
            sources=["src/cmodule.c","src/common.c","src/BFS.c","src/Dijkstra.c","src/topological.c"],
            include_dirs=[numpy.get_include()]
        )
    ]
)


