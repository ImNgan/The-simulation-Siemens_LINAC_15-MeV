# The-simulation-Siemens_LINAC_15-MeV
This is the simulation of SIEMENS PRIMUS HPD linac head to research neutron production from a linear accelerator.
## The steps of simulation includes:
1. Building the geometry of the Siemens linac head.
2. Matching the beam profile by comparing PDD and OCR in the simulation and in the experiment at Kien Giang General Hospital.
3. Reasearching and determining the neutron produced from the linac in the simulation.



### The geometry of linac head ###
**The linac head** (linac_head.mac):
- Envelope window (linac_envelope.mac)
- Target (linac_target.mac)
- Flattening filter (linac_flattening_filter_15MV.mac)
- Primary collimator (linac_primary_collimator_15MV.mac)
- Absorber (linac_absorber_15MV.mac)
- X-ray dose chamber (linac_xray_dose_chamber.mac)
- Mirror (linac_mirror.mac)
- Secondary collimator (linac_secondary_collimator.mac)


### The beam profile ###
*Gaining dose at the phantom to determine PDD and OCR curves.*

Method 1: main_Dose.mac record the entire of process electron source entering.

Method 2: It is saved-time, recomended
- Part 1 (main_PhS.mac): creates PhS files storing the information of particles from the electron source to a mirror.
- Part 2 (main_PhS.mac): makes use of this PhS as a source.
