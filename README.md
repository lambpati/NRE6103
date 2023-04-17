# NRE6103
Computational Transport Theory Project for NRE 6103 at Georgia Institute of Technology. This code calculates scalar flux and eigenvalues for heterogeneous materials within slab geometry without energy reliance.

## Requirements
Have the latest version of CMake installed. For directions on how to install, refer to the CMake [website](https://cmake.org/install/)

## Building
To build with modern CMake from console, use 
`cmake -S . -B build`
For a majority of IDEs, the CMakeLists.txt can be detected and built using IDE specific functions automatically.
## Making
To make on Linux or variants (Cygwin etc.)
`cd build` to enter the build directory
`make all` to make code.
IDEs commonly handle this process itself when selecting run on a .cc file.
## Running
To run, simply run a compiled binary.
On Linux from the `build` directory simply run
`./MonteCarlo1D`
On Windows,from the `build` directory run
`.\MonteCarlo1D.exe`
In an IDE will handle this process automatically by selecting a .cc file when running.
## Running examples
Example problems (problem1.txt -> fixed source, problem2a.txt -> eigenvalue, problem2b_benchmark.txt -> absorption cross section perturbed 2a) are contained within the `examples` directory under the main library path.
Run using the process highlighted above and when prompted, enter the file name you wish to run.
For ease of use, the number of particles, mesh size (resolution), generations, and skipped generations are predefined in the `main.cc` file.
For fixed source problems, the particle count is 1,000,000 with a resolution of 1,000.
For eigenvalue problems, the particle count is 10,000 per generation for 100 generations, skipping the first 20 generations before determining K_eff.
If chosing an eigenvalue problem, at the end of the Monte Carlo simulation, the user will be prompted for a change in the absorption cross section in material 3 (defined in problem2a.txt).
This value should be in decimal form and can be positive or negative. Giving a non-zero value for the change in absorption cross section will result in calculation of the perturbed K_eff.
## Example file input structure
Input files are constructed relatively similar to MCNP or SCALE, except for the exclusion of material properties, only using raw macroscopic cross sections.
An example file structure (problem1.txt) is constructed as follows to showcase the structure of an input file:
```
// PROBLEM 1
// Solve the flux distribution for the problem shown in Fig. 1. The cross sections and
// other parameters are listed in Table 1. Vacuum boundary conditions are imposed on
// both the left and right surfaces.

// solution type
FLUX

//boundaries (SPECULAR vs VACUUM)
BOUNDARIES
LEFT VACUUM
RIGHT VACUUM

//data (REGION SIG_A SIG_S SIG_F V_SIG_F S X_MIN X_MAX)
DATA
1 0 10 0 0 0 0 4
2 1.5 0 0 0 0 4 8
3 50 0 0 0 50 8 13
4 0 0 0 0 0 13 16
5 0.2 0.4 0.15 0.4 0 16 20
```
Eigenvalue problems have the same structure but the source term (S) can be defined as any numeric value and will not be taken into account.
For now, particles, mesh size (resolution), generations, and skipped generations are predefined at the top of `main.cc`. To change these parameters the library must be rebuilt following changes.
