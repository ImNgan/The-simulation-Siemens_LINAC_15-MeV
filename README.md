# The-simulation-Siemens_LINAC_15-MeV
This is the simulation of SIEMENS PRIMUS HPD linac head to research neutron production from a linear accelerator
## The steps of simulation includes:
1. Build the geometry of the Siemens linac head.
2. Match the beam profile by comparing PDD and OCR in the simulation and in the experiment at Kien Giang General Hospital.
3. Reasearch and determine the neutron produced from the linac in the simulation.



### The geometry of linac head ###
linac_head.mac:





### The beam profile ###
Run simulation to acquire dose at the phantom determining PDD and OCR curves
Method 1: main_Dose.mac record the entire of process electron source entering.

Method 2: It is saved-time, recomended
- Part 1 (main_PhS.mac): create PhS files storing the information of particles from the electron source to a mirror.
- Part 2 (main_PhS.mac): makes use of this PhS as a source.
