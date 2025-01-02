# Lorentz-Solver-V2



# Dependencies and installation

This project requires a number of dependencies:  
- Manim Community dependencies, including `manim` python library, `ffmpeg` and `Python`. Installation of these packages is attempted when `make` is run, but manual installation may be required.
- The new version of `g++`
- Python libraries including `pandas`, `os`, `numpy` and `csv`. Installation of these is also attempted in the makefile.

To run the default installation and compilation, run `make`. To clean up the environment, run `make clean`.   
Compiled files are stored in the `compiled_files` and additional text files are stored in `other_config_files`.  

# User instructions

1. Run `make`
2. Update the `config.txt` file. Specific instructions will be covered later in this document.
3. Run `./simulate.py` to run the numerical simulation and animate using Manim.
4. The resulting video can be found in the `media/videos/scene/480p15`

The C++ code reads the config file and runs the appropriate simulation. The electric and magnetic field strengths are computed at each particles' position, and then the Lorentz equation is integrated to determine the new velocity and position of each particle. The numerical integration is performed using the algorithm specified in the config file (see later section). The particle positions are logged to the `data.csv` file after each simulation timestep.  
  
Next, the python code reads both the config and data files and animates the data using Manimi, whether it be a particle motion animation or E or B vector field visualization.  

# Config file

## General structure

The `config.txt` file has various sections, denoted by tags. The structure is shown below. The `%%` is used to denote a comment, although this is not supported in the solver.

```
TITLE
%% parameters

SIM
%% parameters

CONFIG
%% parameters

%% object definitions

\# %% this is then end character. The solver will stop reading when it gets to this character.

```

## TITLE

The `TITLE` section is comprised of two titles lines:
```
TITLE
%% line 1
%% line 2
```
  
eg.
  
```
TITLE
Simulation of the ExB drift of a particle
in an electric and magnetic field
```

## SIM

The `SIM` section contains one parameter, the animation time.
```
SIM
%% animation time
```
  
eg.
  
```
SIM
10
```

## CONFIG

### General structure

The `CONFIG` section contains information about the numerical simulation. 
```
CONFIG
%% simulation type
%% other parameters
```

The simulation type can be:
- `Lorentz Motion`, which computes the path of particles in the specified space.
- `B Field`, which computes the magnetic vector field in the specified region by logging the field vectors in the space.

### Lorentz Motion

```
CONFIG
Lorentz Motion
%% simulation time
%% simulation time step
%% numerical method
```
The numerical method can be either `RK4 Euler` (recommended), `RK4 Hybrid` or `Euler`.  

eg.

```
CONFIG
Lorentz Motion
10
0.01
RK4 Euler
```

### B Field
```
CONFIG
B Field
%% coordinates of one corner of the space
%% coordinates of the opposite corner of the space
%% Step size between vectors in 3D space
```

eg.
```
CONFIG
B Field
[-2,-2,-2]
[2,2,2]
1
```

## Object definitions

### Particle 

A *particle* has *initial position*, *initial velocity*, *charge* and *mass* (all in standard SI units). Hence,  it is defined as follows:
```
P
%% position vector
%% velocity vector
%% charge
%% mass
```
eg.
```
P
[0,0,0]
[1,1,1]
1.6e-19
1.6e-32
```

### Uniform Fields
#### Uniform Electric Field
#### Uniform Magnetic Field

### Static Point Charge













There are various codes for the different objects  
https://github.com/user-attachments/assets/79137115-c350-4835-b776-b185a7a2faeb


config.txt file setup:
  
CONFIG  %config header%  
%simulation time%  
%simulation step%  
  
P   %particle header%  
%position vector - eg [1,0,0]%  
%velocity vector%  
%charge%  
%mass%  
  
UMF  %uniform magnetic field header%  
%field vector%  
  
UEF  %uniform electric field header%  
%field vector%  
    
SPC  %static point charge header%  
%position vector%  
%charge%  
  
\# %means end%  
