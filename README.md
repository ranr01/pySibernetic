### INCOMPLETE README FILE
# pySibernetic

This is a simple python binding for the OpenWorm worm simulator, Sibernetic.

## Motivation

The Sibernetic project provides a C++ command line application that tightly binds
simulation, visualization, data acquisition and interaction with some neural simulation tools
(written in Python).
An alternative and possibly more flexible and customizable approach (which I take here)
is to provide python bindings for the core physics simulations features of Sibernetic and leave the rest for the choice of the user.

This allows the user to control the simulation directly from Python and easily integrate the simulator with any choice of data analysis, visualization framework or neural simulator he chooses without the need to change any of the C++ code.

## Architecture

The project provides the Python module pySibernetic which exposes (using PyBind11) the two main C++ classes of the worm simulation:

1. owConfigProperty - A helper class to specify the simulation's parameters
2. owPhysicsFluidSimulator - A class that implements a single step of the worm simulation

The wrapped Python classes provide access to all the needed parameters and data in a "pythonic" way. Specifically, simulation data arrays (position, velocity, etc.) are exposed as NumPy array views which gives the user direct access to the C++ arrays without the need a copy operation.   

## Usage

For a simple example of usage see this Jupyter notebook.

## Directory Structure

* pySibernetic
  - configuration - Simulation configuration files taken from [here]
  - headers - C++ headers. Mostly taken as is from Sibernetic with a few modification
  - src - C++ and OpenCL source files. Includes both modified Sibernetic files and Python binding files
  - pySibernetic - Python module

## Build Instruction

From the project's root directory run:
~~~
g++ -O3 -fPIC -shared -o pySibernetic/_pySibernetic.so -Iheaders -I/usr/include/python3.5m/ src/owHelper.cpp src/owOpenCLSolver.cpp src/owPhysicsFluidSimulator.cpp src/pyOwConfigProperty.cpp src/pyOwPhysicsFliudSimulator.cpp src/pySibertetic.cpp -lOpenCL
~~~

You may need to adjust the python -I directive to point the compiler to the location
of your Pyhton.h header file
