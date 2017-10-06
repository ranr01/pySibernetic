/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "owPhysicsFluidSimulator.h"
#include <functional>
#include <pybind11/pybind11.h>

namespace py = pybind11;

template<class T, typename buffer_T> 
std::function<unsigned long (T const &)> expose_buffer(buffer_T * (T::*fptr) () const){
    return [fptr](T const & a) {return (unsigned long)((a.*fptr)());};
} 
template<class T, typename buffer_T> 
std::function<unsigned long (T &)> expose_buffer(buffer_T * (T::*fptr) ()){
    return [fptr](T & a) {return (unsigned long)((a.*fptr)());};
} 


void bind_owPhysicsFluidSimulator(py::module & m)
{
    py::class_<owPhysicsFluidSimulator>(m,"owPhysicsFluidSimulator")
        .def(py::init<owConfigProperty *>())
        .def("simulationStep", &owPhysicsFluidSimulator::simulationStep)
        .def("reset", &owPhysicsFluidSimulator::reset)
        .def("makeSnapshot", &owPhysicsFluidSimulator::makeSnapshot)
        .def("pushMuscleActivity2openCLsolver", 
            &owPhysicsFluidSimulator::pushMuscleActivity2openCLsolver)
        .def_readwrite("position_cpp_size", 
                &owPhysicsFluidSimulator::position_cpp_size)
        .def_readwrite("velocity_cpp_size", 
                &owPhysicsFluidSimulator::velocity_cpp_size)
        .def_readwrite("density_cpp_size", 
                &owPhysicsFluidSimulator::density_cpp_size)
        .def_readwrite("particleIndex_cpp_size", 
                &owPhysicsFluidSimulator::particleIndex_cpp_size)
        .def_readwrite("elasticConnectionsData_cpp_size", 
                &owPhysicsFluidSimulator::elasticConnectionsData_cpp_size)
        .def_readwrite("membraneData_cpp_size", 
                &owPhysicsFluidSimulator::membraneData_cpp_size)
        .def_readwrite("muscle_activation_signal_cpp_size", 
                &owPhysicsFluidSimulator::muscle_activation_signal_cpp_size)
        .def_property_readonly("Position_cpp", 
                expose_buffer(&owPhysicsFluidSimulator::getPosition_cpp))
        .def_property_readonly("velocity_cpp", 
                expose_buffer(&owPhysicsFluidSimulator::getvelocity_cpp))
        .def_property_readonly("Density_cpp", 
                expose_buffer(&owPhysicsFluidSimulator::getDensity_cpp))
        .def_property_readonly("ParticleIndex_cpp", 
                expose_buffer(&owPhysicsFluidSimulator::getParticleIndex_cpp))
        .def_property_readonly("ElasticConnectionsData_cpp", 
                expose_buffer(&owPhysicsFluidSimulator::getElasticConnectionsData_cpp))
        .def_property_readonly("MembraneData_cpp", 
                expose_buffer(&owPhysicsFluidSimulator::getMembraneData_cpp))
        .def_property_readonly("MuscleAtcivationSignal_cpp", 
                expose_buffer(&owPhysicsFluidSimulator::getMuscleAtcivationSignal))
        .def_property_readonly("Config", &owPhysicsFluidSimulator::getConfig)
        .def_property_readonly("Iteration", &owPhysicsFluidSimulator::getIteration)
    ;
}
