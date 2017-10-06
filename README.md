# pySibernetic

This is a simple python binding for the OpenWorm worm simulater Sibernetic.

## Motivation

The Sibernetic project provides a C++ command line application that tightly binds
simulation, visualization, data acquisition and interaction with some neural simulation tools
(written in Python).
An alternative and possibly more flexible and customizable approach (which I take here)
is to provide python bindings for the core physics simulations features of Sibernetic and leave the rest for the choice of the user.

This allows the user to control the simulation directly from Python and easily integrate the simulator with any choice of data analysis, visualization framework or neural simulator he chooses without the need to change any of the C++ code.
