# PhysicsSimCA

**Description:**
  - Pseudo-physics simulator using cellular automata written in C using the CSFML library (Not real physics equations are really being used, just some rules that behave similarly to actual physics).
  - The simulation keeps track of a bunch of cells  (cells can be added and removed by the user) that behave differently depending on their material and neighbours creating fluid like simulation.
  - In the current version there are 3 materials to be used/simulated: sand, water and a genereic solid material.
  
**Requirements:**
  1. Unix based operating system
  2. GCC (c11) compiler
  3. CSFML library (https://www.sfml-dev.org/download/csfml/)
  
**Building and running**
  - Build the program using the included Makefile
  - The generated executable is called sim.out

      
 **Controls:**
   - On the top left corner 1 of 3 materials or an earsing tool (black button) can be selected.
   - Use the left mouse button to spawn cells.
