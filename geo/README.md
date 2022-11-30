This directory contains the beam geometry files and some macros for analyzing them.

The `mlf_beam_geometry.gdml` file is produced by the simulation each time it's run and
contains an up to date version of the beamline geometry. Note that this file is not
version controlled because it the exported file changes each time the code is run. As
a result, you need to run the the simulation before using the `drawMLFGeoGDML.C` in
order to ensure that `mlf_beam_geometry.gdml` exists.

The `mlf_geo_iwai.root` contains the original MLF beamline geometry provided by Iwai-san.
The currently geometry is based on this one. The `navigateIwaiGeo.C` macro loops over
the volumes in the geometry provided by Iwai-san and prints their properties. This was
used to recreate the geometry in the simulation source code.

The remaining two files are macros which allow the two geometries to be plotted using
the root TGeo classes.
