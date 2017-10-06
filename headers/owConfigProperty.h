/*******************************************************************************
 * The MIT License (MIT)
 *
 * Copyright (c) 2011, 2013 OpenWorm.
 * http://openworm.org
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the MIT License
 * which accompanies this distribution, and is available at
 * http://opensource.org/licenses/MIT
 *
 * Contributors:
 *     	OpenWorm - http://openworm.org/people.html
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *******************************************************************************/
/*
 * This file contains definition for struct configuration
 */
#ifndef OWCONFIGURATION_H_
#define OWCONFIGURATION_H_

#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "owOpenCLConstant.h"
#include "owPhysicsConstant.h"

struct owConfigProperty{
	//This value defines boundary of box in which simulation is
	//Sizes of the box containing simulated 'world'
	//Sizes choice is realized this way because it should be proportional to smoothing radius h
public:
	typedef unsigned int uint;
	const int getParticleCount(){ return PARTICLE_COUNT; }
	void setParticleCount(int value){
		PARTICLE_COUNT = value;
		PARTICLE_COUNT_RoundedUp = ((( PARTICLE_COUNT - 1 ) / local_NDRange_size ) + 1 ) * local_NDRange_size;
	}
	void setDeviceType(DEVICE type) { prefDeviceType = type; }
	const int getParticleCount_RoundUp(){ return PARTICLE_COUNT_RoundedUp; }
	const int getDeviceType() const { return prefDeviceType; };
	const int getNumberOfIteration() const { return totalNumberOfIteration ;}
	const char * getDeviceName() const { return devFullName.c_str(); }
	const std::string & getSourceFileName() const { return sourceFileName; }
	void setDeviceName(const char * name) {
		devFullName = name;
	}
	INTEGRATOR getIntegrationMethod() const { return integrationMethod; }
	const std::string & getConfigFileName() const { return configFileName; }
	const std::string & getConfigPath() const { return path; }
	const std::string & getLoadPath() const { return loadPath; }
	bool isWormConfig(){ return (configFileName.find("worm") != std::string::npos);}//   == "worm" || configFileName == "worm_no_water")? true:false; }
	void setConfigFileName( const char * name ) { configFileName = name; }
	void setTimeStep(float value){
            if (value <=0.)
                throw std::runtime_error("Time step cannot be less or equal to zero");
            
            this->timeStep = value;
            beta = this->timeStep*this->timeStep*mass*mass*2/(rho0*rho0);
	}
	void setLogStep(int value){
		logStep = value;
	}
	int getLogStep(){ return logStep; }
	float getTimeStep() const { return this->timeStep; }
	float getDelta() const { return delta; }
	
        void setTimeLim(float value){
            if (value <0.)
                throw std::runtime_error("Time Limit cannot be less than zero");
            timeLim=value;
            totalNumberOfIteration = timeLim/this->timeStep; // if it equals to 0 it means that simulation will work infinitely	
        }
        float getTimeLim(){
            return timeLim;
        }
        
        std::string getSnapshotFileName() {
		std::string fileName = "./configuration/snapshot/" + configFileName + "_";
		std::stringstream ss;
		time_t t = time(0);   // get time now
		struct tm * now = localtime( & t );
		ss << now->tm_hour;
		ss << "-";
		ss << now->tm_min;
		ss << "-";
		ss << now->tm_sec;
		ss << "_";
		ss << now->tm_mday;
		ss << ".";
		ss << (now->tm_mon + 1);
		ss << ".";
		ss << (now->tm_year + 1900);
		fileName += ss.str();
		return fileName;
	}
	// Constructor
	owConfigProperty(std::string const & configFN)
                    :numOfElasticP(0), numOfLiquidP(0), numOfBoundaryP(0),
		     numOfMembranes(0), MUSCLE_COUNT(100), logStep(10), path("./configuration/"),
		     loadPath("./buffers/"), configFileName(configFN),
                     sourceFileName( OPENCL_PROGRAM_PATH )
        {
            prefDeviceType = ALL;
            this->timeStep = ::timeStep;
            timeLim = 0.f;
            beta = ::beta;
            this->integrationMethod = EULER;
            std::string strTemp;
            std::string simName = "";
            nrnSimRun = false;
            nrnSimulationFileName = "";
            totalNumberOfIteration = timeLim/this->timeStep; // if it equals to 0 it means that simulation will work infinitely
            calcDelta();
	}
	void initGridCells(){
		//TODO move initialization to configuration class
		gridCellsX = static_cast<uint>( ( xmax - xmin ) / h ) + 1;
		gridCellsY = static_cast<uint>( ( ymax - ymin ) / h ) + 1;
		gridCellsZ = static_cast<uint>( ( zmax - zmin ) / h ) + 1;
		gridCellCount = gridCellsX * gridCellsY * gridCellsZ;
	}
	~owConfigProperty(){
	}
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	float zmin;
	float zmax;
	uint gridCellsX;
	uint gridCellsY;
	uint gridCellsZ;
	uint gridCellCount;
	uint numOfElasticP;
	uint numOfLiquidP;
	uint numOfBoundaryP;
	uint numOfMembranes;
	uint MUSCLE_COUNT;
        DEVICE prefDeviceType; // 0-CPU, 1-GPU
	INTEGRATOR integrationMethod; //DEFAULT is EULER
        std::string path;              // PATH to configuration files
	std::string loadPath;          // PATH to load buffer files
        std::string sourceFileName;
	
	
private:
	/** Calculating delta parameter.
	 *
	 *  "In these situations,
	 *  the SPH equations result in falsified values. To circumvent that problem, we pre-
	 *  compute a single scaling factor δ according to the following formula [1, eq. 8] which is
	 *  evaluated for a prototype particle with a filled neighborhood. The resulting value
	 *  is then used for all particles. Finally, we end up with the following equations
	 *  which are used in the PCISPH method" [1].
	 *  [1] http://www.ifi.uzh.ch/vmml/publications/pcisph/pcisph.pdf
	 */
	inline void calcDelta(){

		float x[] = { 1, 1, 0,-1,-1,-1, 0, 1, 1, 1, 0,-1,-1,-1, 0, 1, 1, 1, 0,-1,-1,-1, 0, 1, 2,-2, 0, 0, 0, 0, 0, 0 };
	    float y[] = { 0, 1, 1, 1, 0,-1,-1,-1, 0, 1, 1, 1, 0,-1,-1,-1, 0, 1, 1, 1, 0,-1,-1,-1, 0, 0, 2,-2, 0, 0, 0, 0 };
	    float z[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 0, 0, 0, 2,-2, 1,-1 };
	    float sum1_x = 0.f;
		float sum1_y = 0.f;
		float sum1_z = 0.f;
	    double sum1 = 0.0, sum2 = 0.0;
		float v_x = 0.f;
		float v_y = 0.f;
		float v_z = 0.f;
		float dist;
		float particleRadius = pow(mass/rho0,1.f/3.f);  // It's equal to simulationScale
														// TODO: replace it with simulation scale
		float h_r_2;

	    for (int i = 0; i < MAX_NEIGHBOR_COUNT; i++)
	    {
			v_x = x[i] * 0.8f/*1.f*/ * particleRadius; // return it back to 0.8 it's more stable
			v_y = y[i] * 0.8f/*1.f*/ * particleRadius; // return it back to 0.8 it's more stable
			v_z = z[i] * 0.8f/*1.f*/ * particleRadius; // return it back to 0.8 it's more stable

	        dist = sqrt(v_x*v_x+v_y*v_y+v_z*v_z);//scaled, right?

	        if (dist <= h*simulationScale)
	        {
				h_r_2 = pow((h*simulationScale - dist),2);//scaled

	            sum1_x += h_r_2 * v_x / dist;
				sum1_y += h_r_2 * v_y / dist;
				sum1_z += h_r_2 * v_z / dist;

	            sum2 += h_r_2 * h_r_2;
	        }
	    }
		sum1 = sum1_x*sum1_x + sum1_y*sum1_y + sum1_z*sum1_z;
		double result = 1.0 / (beta * gradWspikyCoefficient * gradWspikyCoefficient * (sum1 + sum2));
		//return  1.0f / (beta * gradWspikyCoefficient * gradWspikyCoefficient * (sum1 + sum2));
		delta = (float)result;
	}

	int PARTICLE_COUNT;
	int PARTICLE_COUNT_RoundedUp;
	int totalNumberOfIteration;
	int logStep;
	float timeStep;
	float timeLim;
	float beta;
	float delta;
	
	std::string configFileName;
	std::string devFullName;
	bool nrnSimRun; //indicates if we also ran NEURON simulation
	bool c302; //indicates if we also ran NEURON simulation
	std::string nrnSimulationFileName;
};

#endif /* OWCONFIGURATION_H_ */
