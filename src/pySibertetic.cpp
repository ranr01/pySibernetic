/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "owConfigProperty.h"
#include "owPhysicsFluidSimulator.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void bind_owPhysicsFluidSimulator(py::module& );
void bind_owConfigProperty(py::module&);
//void display(owPhysicsFluidSimulator *fluid_simulation);
//int run(owPhysicsFluidSimulator * sim, const bool with_graphics);


PYBIND11_MODULE(_pySibernetic,m){
    bind_owConfigProperty(m);
    bind_owPhysicsFluidSimulator(m);
    
    //m.def("OpenGLdisplay",&display);
    //m.def("run",&run);
}