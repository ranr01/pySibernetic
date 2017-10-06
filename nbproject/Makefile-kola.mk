#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=kola
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/owHelper.o \
	${OBJECTDIR}/src/owOpenCLSolver.o \
	${OBJECTDIR}/src/owPhysicsFluidSimulator.o \
	${OBJECTDIR}/src/pyOwConfigProperty.o \
	${OBJECTDIR}/src/pyOwPhysicsFliudSimulator.o \
	${OBJECTDIR}/src/pySibertetic.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk /home/ranr/Celegance/pySibernetic/pySibernetic/_pySibernetic.${CND_DLIB_EXT}

/home/ranr/Celegance/pySibernetic/pySibernetic/_pySibernetic.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p /home/ranr/Celegance/pySibernetic/pySibernetic
	${LINK.cc} -o /home/ranr/Celegance/pySibernetic/pySibernetic/_pySibernetic.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -lOpenCL -shared -fPIC

${OBJECTDIR}/src/owHelper.o: src/owHelper.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iheaders -I/usr/include/python3.5 -I/usr/local/cuda-8.0/targets/x86_64-linux/include -I/home/ranr/.local/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/owHelper.o src/owHelper.cpp

${OBJECTDIR}/src/owOpenCLSolver.o: src/owOpenCLSolver.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iheaders -I/usr/include/python3.5 -I/usr/local/cuda-8.0/targets/x86_64-linux/include -I/home/ranr/.local/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/owOpenCLSolver.o src/owOpenCLSolver.cpp

${OBJECTDIR}/src/owPhysicsFluidSimulator.o: src/owPhysicsFluidSimulator.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iheaders -I/usr/include/python3.5 -I/usr/local/cuda-8.0/targets/x86_64-linux/include -I/home/ranr/.local/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/owPhysicsFluidSimulator.o src/owPhysicsFluidSimulator.cpp

${OBJECTDIR}/src/pyOwConfigProperty.o: src/pyOwConfigProperty.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iheaders -I/usr/include/python3.5 -I/usr/local/cuda-8.0/targets/x86_64-linux/include -I/home/ranr/.local/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pyOwConfigProperty.o src/pyOwConfigProperty.cpp

${OBJECTDIR}/src/pyOwPhysicsFliudSimulator.o: src/pyOwPhysicsFliudSimulator.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iheaders -I/usr/include/python3.5 -I/usr/local/cuda-8.0/targets/x86_64-linux/include -I/home/ranr/.local/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pyOwPhysicsFliudSimulator.o src/pyOwPhysicsFliudSimulator.cpp

${OBJECTDIR}/src/pySibertetic.o: src/pySibertetic.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iheaders -I/usr/include/python3.5 -I/usr/local/cuda-8.0/targets/x86_64-linux/include -I/home/ranr/.local/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pySibertetic.o src/pySibertetic.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
