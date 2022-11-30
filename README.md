This repository contains a Geant4 Application designed to simulate the
interaction of the 3 GeV proton beam at the J-PARC MLF with the mercurcy
target and surrounding material. The beamline geometry is based on an earlier
geometry produced by Eito Iwai for JSNS2.

To build the simulation code, execute the following commands:

```
$ cd build
$ cmake ..
$ make
```

This will create the `mlf_beam_sim` executable in the main directory. This
executable can be run interactively (with no arguments) or in batch mode by
providing a macro (examples are included in the `mac/` directory). In addition,
you can set the output ROOT filename by passing the `-o` option to `mlf_beam_sim`.
Note that if you set the output filename in the macro, it will override the
command line option. All command line options must be specified before the name
of the macro which should come last. For example,

```
./mlf_beam_sim -o myOuputFile.root mac/runBeam.mac
```

The ouptut is a ROOT file containing a TTree with all of the properties of
neutrino parents when they decayed in the simulation world and a histogram
showing the 2D distribution of the protons incident on the target surface.

To get the neutrino fluxes, you must separately run the `decay_parents`
executable which takes three arguments: an input ROOT file from the beam simulation,
and output file where the neutrino properties and flux histograms should be written,
and an integer representing the number of times each neutrino parent should be
decayed. For example, running

```
./decay_parents myOutputFile.root myNeutrinoFile.root 10
```

would decay the parent particles in the `myOutputFile.root` file 10
times each. The resulting neutrino properties would be stored in a tree in the
file `myNeutrinoFile.root`. Only neutrinos which would pass through the JSNS2
detector are stored in the neutrino property tree. Because each parent is decayed
many times, there can be multiple neutrinos that reach the JSNS2 detector for
each parent. As a result, the neutrino properties are stored in vectors with one
entry for each neutrino. This allows the neutrino properties to be matched up
with the parent properties in subsequent analysis.

The `ana/analyzeParents.C` and `ana/analyzeNeutrinos.C` macros give very simple 
examples of how to access the parent and neutrino properties. 
