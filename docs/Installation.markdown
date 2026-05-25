---
layout: page
title: "Installation"
permalink: /installation
---

This package is designated to work on Unix-like systems with Python3.12+.
Installation requires [STC](https://github.com/stclib/STC) library in header-only mode.
to install it execute following commands:
```bash
git clone --depth 1 https://github.com/stclib/STC.git
sudo cp -r STC/include/stc /usr/include/
```
To install the package itself execute following steps:
```bash

sudo apt-get update
sudo apt-get install -y build-essential python3-dev
git clone --depth 1  https://github.com/PioRow/Lightweight_Implementation_of_Graph_Algorithms.git
cd Lightweight_Implementation_of_Graph_Algorithms
python3 -m pip install -r requirements.txt
python3 -m pip install LIGA/.
```

In case of any problems, report them [here](https://github.com/PioRow/Lightweight_Implementation_of_Graph_Algorithms/issues).