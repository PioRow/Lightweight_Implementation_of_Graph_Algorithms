import setuptools
import numpy

setuptools.setup(
    name="LIGA",
    packages=setuptools.find_packages(),
    include_dirs=[numpy.get_include()],
    ext_modules=[
        setuptools.Extension(
            "LIGA.cmodule",
            sources=["src/cmodule.c"]
        )
    ]
)