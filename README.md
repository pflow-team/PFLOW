# Utility to perform Power Flow calculations in power systems

<b>PFLOW</b> is a steady-state power flow solver that can be used for both transmission and distribution systems. A shared library for PFLOW (for Linux and MacOS) is provided in the lib directory. PFLOW uses numerical routines from the PETSc library that needs to be installed for PFLOW. The code for the transmission-distribution power flow is written in C and it is tested on Ubuntu and MacOS. It uses the following libraries

## Installation

### Install PETSc

PETSc is an open-source numerical library providing high-performance time-stepping, nonlinear, and linearsolvers. The following are steps to install PETSc

<b>Step 1.</b> Clone PETSc from its Git repository

```
git clone https://bitbucket.org/petsc/petsc.git
```

<b>Step 2.</b> Set PETSC_DIR and PETSC_ARCH environment variables

Before beginning the installation, let us set two environmental variables needed by PETSc. The first one is the location of the library, called PETSC_DIR, and the second one is PETSC_ARCH. When PETSc is installed, the configuration settings are saved in a directory with the PETSC_ARCH name set. Thus, this provides flexibility in maintaing several configuration settings with different PETSC_ARCH. The environmental variables can set by the ```export``` command in bash shell. Its best to store environmental variables in .bashrc file in the root folder. Thus, every time the bash shell is active, all environmental variables in the .bashrc file are loaded. Here's how to set the environmental variables in .bashrc file

``` 
cd ~
emacs .bashrc
export PETSC_DIR=<location_of_PETSc directory>
export PETSC_ARCH=<any-arbritraty-name-you-want>  for e.g. debug-mode
```
Save .bashrc file and then source it so that the environmental variables are loaded
```
source ~/.bashrc
```
Now, check whether the environment variables are loaded
```
echo $PETSC_DIR
```
This should display the PETSC_DIR variable you set previously. If you don't see anything, then the environmental variable is not loaded.

<b>Step 3.</b> Configure and compile PETSc
```
cd $PETSC_DIR
./config/configure.py
make
make test
```
The above commands will configure the PETSc library and compile it. If everything goes correctly then you should see display messages by PETSc that all tests have passed. 
This completes basic installation of the PETSc library that we need. For additional detailed installation instructions refer to <a href="https://www.mcs.anl.gov/petsc/documentation/installation.html">PETSc Installation</a>.

### Install PFLOW

<b>Step 1.</b> Clone the repository as shown below.

```
git clone https://github.com/pflow-team/pflow.git
cd pflow
```
<b>Step 2.</b> Compile PFLOW using the makefile.

```
make PFLOW
```

## Who is responsible?

**Core developers:**

- Shrirang Abhyankar shrirang.abhyankar@gmail.com

**Contributor:**

- Karthikeyan Balasubramaniam kbalasubramaniam@anl.gov

## Acknowledgement

This work is supported by U.S. Department of Energy, Office of Energy Efficiency and Renewable Energy, Solar Energy Technologies Office, under contract DE-EE0001748.

## Citation
If you use this code please cite it as:
```
@misc{PFLOW,
  title = {{PFLOW}: A utility to calculate power flow in electric power systems},
  author = "{Shrirang Abhyankar, Karthikeyan Balasubramaniam}",
  howpublished = {\url{https://github.com/pflow-team/PFLOW}},
  url = "https://github.com/pflow-team/PFLOW",
  year = 2019,
  note = "[Online; accessed 1-August-2019]"
}
```
## Copyright and License
Copyright © 2019, UChicago Argonne, LLC

This tool is distributed under the terms of [BSD-3 OSS License.](LICENSE.md)
