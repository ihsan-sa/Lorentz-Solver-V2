# Lorentz-Solver-V2

This Lorentz solver is designed to compute the paths of particles in complex custom electromagnetic spaces and then animate them using the Manim library for maximum clarity.  

See the [*Examples* section](#examples) for images and videos.

**Contents**
1. [*Examples*](#examples)
2. [*Dependencies and installation*](#dependencies-and-installation)
3. [*User instructions*](#user-instructions)
4. [*Physics and math*](#physics-and-math)
5. [*Config file*](#config-file)
6. [*Animation*](#animation)

# Examples

### Particle motion simulation 1 

https://github.com/user-attachments/assets/a52f1ddd-b384-40a9-a1bc-44f1a0ce4402

### Particle motion simulation 2 - No intro

https://github.com/user-attachments/assets/5eab858d-2724-40e9-9c16-1d35911e4cc2

### E x B drift simuulation

https://github.com/user-attachments/assets/3ef07e9f-b105-45bf-8fdb-ad0d5772c3bd

### grad(B) drift simulation

https://github.com/user-attachments/assets/281a55c2-c2e3-4e90-99e2-dc70d91bdf94

### Rudimentary visualization of grad(B) simulation B vector field.  

https://github.com/user-attachments/assets/6f529941-3a40-4a7d-953a-154703d1cfff

# Dependencies and installation

This project requires a number of dependencies:  
- Manim Community dependencies, including `manim` python library, `ffmpeg` and `Python`. Installation of these packages is attempted when `make` is run, but manual installation may be required.
- The new version of `g++`
- Python libraries including `pandas`, `os`, `numpy` and `csv`. Installation of these is also attempted in the makefile.

To run the default installation and compilation, run `make`. To clean up the environment, run `make clean`.   
Compiled files are stored in the `compiled_files` and additional text files are stored in `other_config_files`.  

# User instructions

1. Run `make`
2. Update the `config.txt` file. Specific instructions will be covered in the [*Config file* section](#config-file). There is a simple config file provided for first simulations.
3. Run `./simulate.py` to run the numerical simulation and animate using Manim.
4. The resulting video can be found in the `media/videos/scene/480p15`

The C++ code reads the config file and runs the appropriate simulation. The electric and magnetic field strengths are computed at each particles' position, and then the Lorentz equation is integrated to determine the new velocity and position of each particle (see [*Physics and math* section](#physics-and-math). The numerical integration is performed using the algorithm specified in the config file (see [*Config file* section](#config-file)). The particle positions are logged to the `data.csv` file after each simulation timestep.  
  
Next, the python code reads both the config and data files and animates the data using Manimi, whether it be a particle motion animation or E or B vector field visualization.  

# Physics and math

The equation for the Lorentz force on a particle moving through an electric and magnetic field is:
```math
F = q(\vec{E} + \vec{v} \times \vec{B})
```
This equation is numerically integrated using various techniques, an RK4-euler hybrid solution being the most successful in this simulation.  
The code for this simulation can be found in the `void Space::simulate(long double const t, long double const dt) const` function in `./numerical_simulation/space.cpp`.


# Config file

## General structure

The `config.txt` file has various sections, denoted by tags. The structure is shown below. The `%%` is used to denote a comment, although this is not supported in the solver.   
Note: It is usually best to leave 2-3 lines between tags.

```
TITLE
%% parameters

AUTHOR
%% parameters

SIM
%% parameters

CONFIG
%% parameters

%% object definitions

\# %% this is then end character. The solver will stop reading when it gets to this character.

```

## Title

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

## Author
The author's name is displayed in the bottom right corner of the screen for the entire animation.
```
AUTHOR
%% name

```
eg.
```
AUTHOR
Ihsan
```

## Sim animation settings

The `SIM` section contains one parameter, the animation time. For more animation settings, see the [*Animation* section](#animation).
```
SIM
%% animation time
```
  
eg.
  
```
SIM
10
```

## Numerical sim config

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
- `E Field`, which computes the electric vector field in the specified region by logging the field vectors in the space.

Note: The `B Field` and `E Field` simulations are still under development and are using very crude patched together experimental code by me, various online sources and AI. This is purely experimental and will be re-written by me once experimentation is complete. All other code is written by me.
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

### E Field

Coming soon.

```
CONFIG
E Field
%% coordinates of one corner of the space
%% coordinates of the opposite corner of the space
%% Step size between vectors in 3D space
```

eg.
```
CONFIG
E Field
[-1,-1,-1]
[2,2,2]
0.5
```

## Object definitions

There are a number of objects that can be added to a simulation space:
- Particle (P)
- Uniform Fields  
    - Uniform Magnetic Field (UMF)
    - Uniform Electric Field (UEF)
- Static Point charge (SPC)
- Sectioned Uniform Fields   
    - Sectioned Uniform Magnetic Field (SUMF)
    - Sectioned Uniform Electric Field (SUEF)
- Wire (W) -- coming soon
- Wire Loop (WL) -- coming soon
- Magnetic dipole (MD) -- coming soono
  

Later, more complex premade combinations of objects will be added. For example: 
- Tokamak Fusion Reactor



### Particle (P)

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
1.67e-27
```

### Uniform Fields
#### Uniform Magnetic Field (UMF)
```
UMF
%% field vector
```
Ensure to account for magnitude when determining the field vector   
  
eg.
```
UMF
[0,0,1]
```
#### Uniform Electric Field (UEF)
```
UEF
%% field vector
```
Ensure to account for magnitude when determining the field vector   
  
eg.
```
UEF
[0,1,0]
```

### Static Point Charge (SPC)

Definition of a SPC is similar to a particle, but does not include *velocity* or *mass*.
```
SPC
%% position vector
%% charge
```

eg.
```
SPC
[3,0,0]
-6e-6
```

### Sectioned Uniform Fields

Uniform fields can be restricted to a section in space. These are called *sectioned* uniform fields.   
For the moment, the spaces are computed based on the larges rectangular prism formed by the corners, but this will be updated to work for more complex 3D shapes.

#### Sectioned Uniform Magnetic Field (SUMF)

```
SUMF
%% field vector
%% 8 coordinates of the coordinates of the space
```
eg.
```
SUMF
[0,0,10]
[-1,-1,-1]
[0,1,1]
[0,0,0]
[0,0,0]
[0,0,0]
[0,0,0]
[0,0,0]
[0,0,0]
```

#### Sectioned Uniform Electric Field (SUEF)

Coming soon.

```
SUEF
%% field vector
%% 8 coordinates of the coordinates of the space
```
eg.
```
SUMF
[0,2,1]
[-1,-2,-1]
[0,1,2]
[0,0,0]
[0,0,0]
[0,0,0]
[0,0,0]
[0,0,0]
[0,0,0]
```

# Animation

## Display configurations

There exist additional animation settings available in the `scene.py` file in the `./animation` folder. Some familiarity with Manim Community may be useful. 
User configuration is found under the `# Simulation configuration and settings` comment at the top of the `plot_particle_path` class and other scene classes. 
  
The start of each animation begins with an optional presentation of the objects. The code will read the config file and display the object settings two by two, although this will cause the animation to take longer.  

This can be toggled on and off by changing `output_ctxt` to `output_ctxt = True` and vice-versa. 

When uniform fields are added, field vectors can be shown (blue for magnetic and orange for electric).  
This can be toggled on and off my changing `show_vecs` and the scale of the vectors can be adjusted via `vector_scale`.  

By default, the object presentation is switched off and the vectors are displayed with 0.2 scale.

## Higher quality rendering

For higher quality rendering, consult Manim Community's documentation. You can run the generic command:   
```
manim -pqh scene.py [class_name]
```

After running `make` and updating `config.txt`, you will need to run the execuatable `./compiled_files/compiled_solver`.
Then, if you are running a Lorentz Motion simulation, run the command:
```
manim -pqh scene.py plot_particle_path
```
For a B Field simulation, run:
```
manim -pqh scene.py disp_b_vec_field
```

