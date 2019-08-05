import os
import sys
from ctypes import *
from pypflow import pypflow

pflow = pypflow()

pflow.ReadMatpowerData("/Users/Shri/software/tsopf/datafiles/case9mod.m")
pflow.Solve()



#pflowlib.PFLOWLibraryFinalize()
