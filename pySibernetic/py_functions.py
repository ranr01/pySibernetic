import numpy as np
import math
from . import _pySibernetic


class namespace:
    pass

def getNDArrayFromBuffer(buffer_adrs,size,typestr='<f4'):
    b=namespace()
    b.__array_interface__={
         'data': (buffer_adrs, False),
         'descr': [('', typestr)],
         'shape': (size,),
         'strides': None,
         'typestr': typestr,
         'version': 3}
    return np.asarray(b)

    
class owPhysicsFluidSimulator(_pySibernetic.owPhysicsFluidSimulator):
    def __init__(self,config):
        #call the c++ constructor
        _pySibernetic.owPhysicsFluidSimulator.__init__(self,config)
        # here we create ndarray views of the internal buffers of the class
        # Changes in the ndarray's ELEMENTS will be visible to the cpp side
        # however changes to the ndarray itself will destroy the link.
        
        # The folowing buffers are always held updated by the simulator.
        # For buffers that need an update from the oCL buffers we define properties 
        # outside __init__
        self.Position = getNDArrayFromBuffer(self.Position_cpp,self.position_cpp_size,'<f4')
        self.ElasticConnectionsData = getNDArrayFromBuffer(\
                self.ElasticConnectionsData_cpp,self.elasticConnectionsData_cpp_size,'<f4')
        self.MembraneData = getNDArrayFromBuffer(self.MembraneData_cpp,\
                                                 self.membraneData_cpp_size,'<i4')
        self.MuscleAtcivationSignal = getNDArrayFromBuffer(\
                                            self.MuscleAtcivationSignal_cpp,\
                                            self.muscle_activation_signal_cpp_size,'<f4')
        # these buffers need to be updated before they are read
        self._Velocity = getNDArrayFromBuffer(self.velocity_cpp,self.velocity_cpp_size,'<f4')
        self._Density = getNDArrayFromBuffer(self.Density_cpp,self.density_cpp_size,'<f4')
        self._ParticleIndex = getNDArrayFromBuffer(self.ParticleIndex_cpp,\
                                                   self.particleIndex_cpp_size,'<u4')
    @property
    def Velocity(self):
        # self.*_cpp updates the buffer from the oCL buffers (return the buffer's adrs)
        self.velocity_cpp
        return self._Velocity
  
    @property
    def Density(self):
        # self.*_cpp updates the buffer from the oCL buffers (return the buffer's adrs)
        self.Density_cpp
        return self._Density
  
    @property
    def ParticleIndex(self):
        # self.*_cpp updates the buffer from the oCL buffers (return the buffer's adrs)
        self.ParticleIndex_cpp
        return self._ParticleIndex

def parallel_waves(n, #24 for our first test?
                   step=0, 
                   phi=math.pi,
                   amplitude=1,
                   velocity =0.000015):
    """
    Array of two travelling waves, second one starts
    half way through the array
    """

    if n % 2 != 0:
        raise NotImplementedError("Currently only supports even number of muscles!")

    j = n/2

    row_positions = np.linspace(0,0.75*1.5*2*math.pi,j)

    wave_1 = (map(math.sin,(row_positions - velocity*step)))
    wave_2 = (map(math.sin,(row_positions + (math.pi) - velocity*step)))

    normalize_sine = lambda x : (x + 1)/2
    wave_1 = map(normalize_sine, wave_1)
    wave_2 = map(normalize_sine, wave_2)

    double_wave_1 = []
    double_wave_2 = []

    for i in wave_1:
        double_wave_1.append(i)
        double_wave_1.append(i)

    for i in wave_2:
        double_wave_2.append(i)
        double_wave_2.append(i)
        
    return (double_wave_1,double_wave_2)

class MuscleSimulation():

    def __init__(self,increment=1.0,muscle_row_count=24):
        self.increment = increment
        self.step = 0
        self.muscle_row_count=muscle_row_count


    def run(self, skip_to_time=0, do_plot = True):
        self.contraction_array =  parallel_waves(self.muscle_row_count,step = self.step)
        self.step += self.increment
        # for reversal movment after 40000 steps it will switch sinusoid
        
        self.contraction_array[0][self.muscle_row_count - 2] = 0
        self.contraction_array[0][self.muscle_row_count - 1] = 0
        self.contraction_array[1][self.muscle_row_count - 2] = 0
        self.contraction_array[1][self.muscle_row_count - 1] = 0

        return np.concatenate([self.contraction_array[0],
                               self.contraction_array[1],
                               self.contraction_array[1],
                               self.contraction_array[0]]) 
 
