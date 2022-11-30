import numpy as np
import matplotlib.pyplot as plt
import uproot4
import os,sys
from tqdm import tqdm
from matplotlib.colors import LogNorm



beamN = 1

#fin = uproot4.open("result_data/myNeutrinoFile_pTime_test04_beamON2e6")
#fin = uproot4.open("result_data/myNeutrinoFile_pTime_test12_Z")
fin = uproot4.open("myOutputfile_add_time_beam2e4_TflatX2_all.root")
#fin = uproot4.open("result_myOutputFile_add_time_beamOn2e4_Tflat_01.root")
array_PDG = np.array(fin["parentTree"]["PDGCode"])
#time = np.array(fin["parentTree"]["parent_time"])
#energy = np.array(fin["parentTree"]["energy"])
array_xPos = np.array(fin["parentTree"]["xPos"])
array_yPos = np.array(fin["parentTree"]["yPos"])
array_zPos = np.array(fin["parentTree"]["zPos"])


#PDG_aD = np.array(fin["neutrinoTree"]["PDGCode"])
#energy_aD = np.array(fin["neutrinoTree"]["energy"])




#array_PDG = np.concatenate(PDG)

print("///// 2d hist")

#array_xPos = np.concatenate(xPos)
#array_yPos = np.concatenate(yPos)
#array_zPos = np.concatenate(zPos)


PDGN = 130

array_xPos_Ks = array_xPos[(array_PDG==PDGN)]
array_yPos_Ks = array_yPos[(array_PDG==PDGN)]
array_zPos_Ks = array_zPos[(array_PDG==PDGN)]

#array_xPos_Ks = array_xPos
#array_yPos_Ks = array_yPos
#array_zPos_Ks = array_zPos




print(len(array_xPos_Ks))

x_L = 2e3
y_L = 2e3
z_L = 2e3
r_L = 2e3
"""
plt.scatter(array_xPos_Ks,array_zPos_Ks,color='red',alpha=.5)
plt.xlabel("X")
plt.ylabel("Z")
plt.grid()
plt.show()
plt.clf()

plt.scatter(np.hypot(array_xPos_Ks,array_zPos_Ks),array_yPos_Ks,color='blue',alpha=.5)
plt.xlabel("R")
plt.ylabel("Y")
plt.grid()
plt.show()
plt.clf()
"""
fig = plt.figure(figsize=(7,10))
fig.tight_layout()
plt.subplot(2,1,1)
plt.hist2d(array_xPos_Ks,array_zPos_Ks,bins=[200,200], range=[[-x_L,x_L],[-z_L,z_L]],norm = LogNorm())
plt.colorbar()
plt.grid()
plt.xlabel('X [mm]',fontsize=15)
plt.ylabel('Z [mm]',fontsize=15)
#plt.show()

plt.subplot(2,1,2)
#plt.figure(figsize=(8,6))
plt.hist2d(np.hypot(array_xPos_Ks,array_zPos_Ks),array_yPos_Ks,bins=[200,200], range=[[0,r_L],[-y_L,y_L]],norm = LogNorm())
plt.colorbar()
plt.grid()
plt.xlabel('R [mm]',fontsize=15)
plt.ylabel('Y [mm]',fontsize=15)
plt.show()



print("///// 2d hist end")


