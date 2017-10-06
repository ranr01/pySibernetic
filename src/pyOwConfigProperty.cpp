// File:
#include "owConfigProperty.h"
#include <pybind11/pybind11.h>

namespace py = pybind11; 


void bind_owConfigProperty(py::module & M)
{
    // DEVICE file: line:55
    py::enum_<DEVICE>(M, "DEVICE", "")
		.value("CPU", DEVICE::CPU)
		.value("GPU", DEVICE::GPU)
		.value("ALL", DEVICE::ALL)
		.export_values();

    // INTEGRATOR file: line:56
    py::enum_<INTEGRATOR>(M, "INTEGRATOR", "")
		.value("EULER", INTEGRATOR::EULER)
		.value("LEAPFROG", INTEGRATOR::LEAPFROG)
		.export_values();


    // owConfigProperty file: line:52
    py::class_<owConfigProperty>(M, "owConfigProperty", "")
        .def(py::init<std::string>())
        .def("initGridCells",  &owConfigProperty::initGridCells, "C++: owConfigProperty::initGridCells() --> void")
        .def_readwrite("xmin", &owConfigProperty::xmin)
	.def_readwrite("xmax", &owConfigProperty::xmax)
	.def_readwrite("ymin", &owConfigProperty::ymin)
        .def_readwrite("ymax", &owConfigProperty::ymax)
	.def_readwrite("zmin", &owConfigProperty::zmin)
	.def_readwrite("zmax", &owConfigProperty::zmax)
	.def_readwrite("gridCellsX", &owConfigProperty::gridCellsX)
	.def_readwrite("gridCellsY", &owConfigProperty::gridCellsY)
	.def_readwrite("gridCellsZ", &owConfigProperty::gridCellsZ)
	.def_readwrite("gridCellCount", &owConfigProperty::gridCellCount)
	.def_readwrite("numOfElasticP", &owConfigProperty::numOfElasticP)
        .def_readwrite("numOfLiquidP", &owConfigProperty::numOfLiquidP)
	.def_readwrite("numOfBoundaryP", &owConfigProperty::numOfBoundaryP)
	.def_readwrite("numOfMembranes", &owConfigProperty::numOfMembranes)
        .def_readwrite("MUSCLE_COUNT", &owConfigProperty::MUSCLE_COUNT)
        .def_readwrite("prefDeviceType", &owConfigProperty::prefDeviceType)
        .def_readwrite("integrationMethod", &owConfigProperty::integrationMethod)
        .def_readwrite("ConfigFilePath", &owConfigProperty::path)
        .def_readwrite("LoadPath", &owConfigProperty::loadPath)
        .def_readwrite("OpenCLSourceFileName", &owConfigProperty::sourceFileName)
        .def_property("ParticleCount",
                      &owConfigProperty::getParticleCount,
                      &owConfigProperty::setParticleCount)
        .def_property("DeviceType",
                      &owConfigProperty::getDeviceType,
                      &owConfigProperty::setDeviceType)
        .def_property("DeviceName",
                      &owConfigProperty::getDeviceName,
                      &owConfigProperty::setDeviceName)
        .def_property_readonly("ParticleCount_RoundUp",
                      &owConfigProperty::getParticleCount_RoundUp)
        .def_property_readonly("NumberOfIteration",
                      &owConfigProperty::getNumberOfIteration)
        .def_property("ConfigFileName",
                      &owConfigProperty::getConfigFileName,
                      &owConfigProperty::setConfigFileName)
        .def_property_readonly("ConfigPath",
                      &owConfigProperty::getConfigPath)
        .def_property_readonly("LoadPath",
                      &owConfigProperty::getLoadPath)
        .def_property_readonly("WormConfig",
                      &owConfigProperty::isWormConfig)
        .def_property("TimeStep",
                      &owConfigProperty::getTimeStep,
                      &owConfigProperty::setTimeStep)
        .def_property("TimeLim",
                      &owConfigProperty::getTimeLim,
                      &owConfigProperty::setTimeLim)
        .def_property("LogStep",
                      &owConfigProperty::getLogStep,
                      &owConfigProperty::setLogStep)
        .def_property_readonly("Delta",
                      &owConfigProperty::getDelta)
        .def_property_readonly("SnapshotFileName",
                      &owConfigProperty::getSnapshotFileName)
    ;
}

