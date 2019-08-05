import os
import sys
from ctypes import *

pflowlib = cdll.LoadLibrary("libpflow.dylib")
    
class pypflow:
    def __init__(self):
        # Load PFLOW library
     #   pflowlib = cdll.LoadLibrary("libpflow.dylib")
        # Initialize library with options file petscopt
        pflowlib.PFLOWLibraryInitialize(c_int(0),None,"petscopt",None)
        isinitialized = c_int(0)
        pflowlib.PFLOWLibraryInitialized(byref(isinitialized))
        if isinitialized.value != 1:
            raise ValueError('PFLOW library not initialized')
        self.pflow = c_longlong(0)
        comm = c_long()
        ierr = pflowlib.PFLOWGetPETSC_COMM_SELF(byref(comm))
        ierr = pflowlib.PFLOWCreate(comm,byref(self.pflow))

    def ReadMatpowerData(self,filename):
        pflowlib.PFLOWReadMatPowerData(self.pflow,filename)

    def Solve(self):
        pflowlib.PFLOWSolve(self.pflow)
        pflowlib.PFLOWPostSolve(self.pflow)

    
