import numpy as np
import matplotlib.pyplot as plt
import uproot4
import os,sys
from tqdm import tqdm

beamN = 1

#fin = uproot4.open("result_data/myNeutrinoFile_pTime_test04_beamON2e6")
#fin = uproot4.open("result_data/myNeutrinoFile_pTime_test12_Z")
fin = uproot4.open("result_myOutputfile_add_time_beam2e4_TflatX2_all.root")
#fin = uproot4.open("result_myOutputFile_add_time_beamOn2e4_Tflat_01.root")
PDG = np.array(fin["neutrinoTree_bD"]["PDGCode"])
time = np.array(fin["neutrinoTree_bD"]["parent_time"])
parPDG = np.array(fin["neutrinoTree_bD"]["parent_PDG"])
energy = np.array(fin["neutrinoTree_bD"]["energy"])
xPos = np.array(fin["neutrinoTree_bD"]["xPos"])
yPos = np.array(fin["neutrinoTree_bD"]["yPos"])
zPos = np.array(fin["neutrinoTree_bD"]["zPos"])


PDG_aD = np.array(fin["neutrinoTree"]["PDGCode"])
energy_aD = np.array(fin["neutrinoTree"]["energy"])





v_e = []
v_e_bar = []
v_mu = []
v_mu_bar = []

from_mu = []
from_pi = []
from_Kaon = []


print(fin["neutrinoTree_bD"].keys())
"""
for i in tqdm(range(len(time))):
    if(len(time[i]))==0: continue
    #print("PDG: ",PDG[i])
    #print("energy: ",energy[i])
    #print("pTime: ",time[i],"\n")

    for j in range(len(time[i])):
        if PDG[i][j] == 12: v_e.append(time[i][j])
        if PDG[i][j] == -12: v_e_bar.append(time[i][j])
        if PDG[i][j] == 14: v_mu.append(time[i][j])
        if PDG[i][j] == -14: v_mu_bar.append(time[i][j])
      
        if parPDG[i][j] == 13 or parPDG[i][j] == -13 : from_mu.append(time[i][j])
        if parPDG[i][j] == 211 or parPDG[i][j] == -211 : from_pi.append(time[i][j])
        if parPDG[i][j] == 321 or parPDG[i][j] == -321 : from_Kaon.append(time[i][j])
"""

array_PDG = np.concatenate(PDG)
array_parPDG = np.concatenate(parPDG)


print("at parent: ",np.unique(array_parPDG))
print("at dauther: ",np.unique(array_PDG))

array_time = np.concatenate(time)
from_mu = array_time[(np.abs(array_parPDG)==13)]
from_pi = array_time[(np.abs(array_parPDG)==211)]
from_Kaon = array_time[(np.abs(array_parPDG)==321)]

print("v_mu of from_mu+ : %d   &   v_mu_bar of from_mu+ : %d"%(np.sum((array_parPDG==-13)&(array_PDG==14)),(np.sum((array_parPDG==-13)&(array_PDG==-14)))))
print("v_mu of from_mu- : %d   &   v_mu_bar of from_mu- : %d"%(np.sum((array_parPDG==13)&(array_PDG==14)),(np.sum((array_parPDG==13)&(array_PDG==-14)))))

print("v_e of from_mu+ : %d   &   v_e_bar of from_mu+ : %d"%(np.sum((array_parPDG==-13)&(array_PDG==12)),(np.sum((array_parPDG==-13)&(array_PDG==-12)))))
print("v_e of from_mu- : %d   &   v_e_bar of from_mu- : %d"%(np.sum((array_parPDG==13)&(array_PDG==12)),(np.sum((array_parPDG==13)&(array_PDG==-12)))))



print("/////////////////////////////////////////////////")
print("v_mu of from_pion+ : %d   &   v_mu_bar of from_pion+ : %d"%(np.sum((array_parPDG==211)&(array_PDG==14)),(np.sum((array_parPDG==211)&(array_PDG==-14)))))
print("v_mu of from_pion- : %d   &   v_mu_bar of from_pion- : %d"%(np.sum((array_parPDG==-211)&(array_PDG==14)),(np.sum((array_parPDG==-211)&(array_PDG==-14)))))

print("v_e of from_pion+ : %d   &   v_e_bar of from_pion+ : %d"%(np.sum((array_parPDG==211)&(array_PDG==12)),(np.sum((array_parPDG==221)&(array_PDG==-12)))))
print("v_e of from_pion- : %d   &   v_e_bar of from_pion- : %d"%(np.sum((array_parPDG==-211)&(array_PDG==12)),(np.sum((array_parPDG==-221)&(array_PDG==-12)))))



print("/////////////////////////////////////////////////")
print("v_mu of from_Kaon+ : %d   &   v_mu_bar of from_Kaon+ : %d"%(np.sum((array_parPDG==321)&(array_PDG==14)),(np.sum((array_parPDG==321)&(array_PDG==-14)))))
print("v_mu of from_Kaon- : %d   &   v_mu_bar of from_Kaon- : %d"%(np.sum((array_parPDG==-321)&(array_PDG==14)),(np.sum((array_parPDG==-321)&(array_PDG==-14)))))

print("v_e of from_Kaon+ : %d   &   v_e_bar of from_Kaon+ : %d"%(np.sum((array_parPDG==321)&(array_PDG==12)),(np.sum((array_parPDG==321)&(array_PDG==-12)))))
print("v_e of from_Kaon- : %d   &   v_e_bar of from_Kaon- : %d"%(np.sum((array_parPDG==-321)&(array_PDG==12)),(np.sum((array_parPDG==-321)&(array_PDG==-12)))))


print("/////////////////////////////////////////////////")
print("v_mu of from_K0L : %d   &   v_mu_bar of from_K0L : %d"%(np.sum((array_parPDG==130)&(array_PDG==14)),(np.sum((array_parPDG==130)&(array_PDG==-14)))))

print("v_e of from_K0L : %d   &   v_e_bar of from_K0L : %d"%(np.sum((array_parPDG==130)&(array_PDG==12)),(np.sum((array_parPDG==130)&(array_PDG==-12)))))


print("////////////////////////////////////////////////////")
array_energy = np.concatenate(energy)

plt.title("v_e_bar_from_KL")
plt.hist(array_energy[(array_parPDG==130)&(array_PDG==-12)],bins=100,range=[0,300])
plt.yscale('log')
plt.grid()
plt.show()
plt.clf()

plt.title("v_e_bar_from_Kaon-")
plt.hist(array_energy[(array_parPDG==-321)&(array_PDG==-12)],bins=100,range=[0,300])
plt.yscale('log')
plt.grid()
plt.show()
plt.clf()

plt.title("v_e_bar_from_mu-")
plt.hist(array_energy[(array_parPDG==13)&(array_PDG==-12)],bins=100,range=[0,300])
plt.yscale('log')
plt.grid()
plt.show()
plt.clf()

plt.title("v_e_bar_from_pion+")
plt.hist(array_energy[(array_parPDG==211)&(array_PDG==-12)],bins=100,range=[0,300])
plt.yscale('log')
plt.grid()
plt.show()
plt.clf()



plt.title("v_e_bar_all")
plt.hist(array_energy[(array_PDG==-12)],bins=100,range=[0,300])

plt.yscale('log')
plt.grid()
plt.show()
plt.clf()


array_PDG_aD = np.concatenate(PDG_aD)
array_energy_aD = np.concatenate(energy_aD)

plt.title("v_e_bar_all_aD")
plt.hist(array_energy_aD[(array_PDG_aD==-12)],bins=100,range=[0,300])
plt.yscale('log')
plt.grid()
plt.show()
plt.clf()


"""
plt.hist(v_e,bins=100, histtype='step',label='v_e')
plt.hist(v_e_bar,bins=100, histtype='step',label='v_e_bar')
plt.hist(v_mu,bins=100, histtype='step',label='v_mu')
plt.hist(v_mu_bar,bins=100, histtype='step',label='v_mu_bar')
plt.legend()
plt.xlim(0,2000)
plt.grid()
plt.show()
plt.clf()
"""
#############################################   Artificial modify    ########################################################

#import random
#from_mu += ( np.random.normal(50, 15, len(from_mu)) + np.array([random.choice([0,600]) for i in range(len(from_mu))]))
#from_pi += ( np.random.normal(50, 15, len(from_pi)) + np.array([random.choice([0,600]) for i in range(len(from_pi))]))
#from_Kaon += ( np.random.normal(50, 15, len(from_Kaon)) + np.array([random.choice([0,600]) for i in range(len(from_Kaon))]))

##############################################################################################################################

#from_mu = np.array(from_mu)
#from_pi = np.array(from_pi)
#from_Kaon = np.array(from_Kaon)

from_total = np.concatenate([from_mu,from_pi,from_Kaon]) 

nu_ = r'$\nu$'
pi_ = r'$\pi$'
Kaon_ = 'K'
mu_ = r'$\mu$'

plt.figure(figsize=(7,5))
#plt.title("beanON: %d"%beamN,fontsize=25)
#plt.rcParams['font.family'] = 'Times New Roman'
#plt.rcParams['font.style'] = 'italic'
plt.hist(from_mu,bins=200, weights=(1/beamN)*np.ones(from_mu.shape), range=[0,2000], histtype='step',label=nu_+' from '+mu_+' : %d'%(len(from_mu)/beamN), color='red', density=False)
plt.hist(from_pi,bins=200,  weights=(1/beamN)*np.ones(from_pi.shape), range=[0,2000], histtype='step',label=nu_+' from '+pi_+' :%d'%(len(from_pi)/beamN), color='blue', density=False)
plt.hist(from_Kaon,bins=200,  weights=(1/beamN)*np.ones(from_Kaon.shape), range=[0,2000], histtype='step',label=nu_+' from '+Kaon_+' :%d'%(len(from_Kaon)/beamN), color='m', density=False)
plt.hist(from_total,bins=200,  weights=(1/beamN)*np.ones(from_total.shape), range=[0,2000], histtype='step',label=nu_+' from total :%d'%(len(from_total)/beamN), color='black', density=False)
plt.legend()
plt.yscale('log')
plt.ylabel("#"+r"$\nu$"+"/10ns/POT",fontsize=20,loc='top')
#plt.xlim(0,2000)
xtick_list = np.arange(0,2001,100)
plt.xticks(xtick_list,np.array(np.where(xtick_list%500!=0,'',xtick_list),dtype=str))
plt.xlabel("time[ns]",fontsize=20,loc='right')
plt.grid()
plt.show()
plt.clf()


