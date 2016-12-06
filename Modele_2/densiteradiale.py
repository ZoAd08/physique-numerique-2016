# -*- coding: utf-8 -*-
'''/*********************************************************************************************
 *  @file    densiteradiale.py
 *  @author  Djinthana Dufour
 *  @date    17/11/2016
 *  @version 1.0
 *  @resume  Permet de tracer la densite de bacteries en fonction du rayon
*********************************************************************************************/'''


import numpy as np
import scipy.spatial as sp
import matplotlib.pyplot as plt
from numpy import transpose
from scipy.spatial import KDTree

config = np.loadtxt("config.txt")
marcheur = int(config[0,0])
temps = config[0,1]
radius = config[1,0]
gain = "Gain : " + str(config[1,1]) + "\n"
sens = "Comparaison entre " + str(config[2,0]) + " seconde et " + str(config[2,1]) + " seconde" + "\n"
pas=radius / 100.

data = np.loadtxt("marcheur.txt")
x=np.zeros(marcheur)
y=np.zeros(marcheur)
points=np.zeros((marcheur,2))
densite=np.zeros((len(data[:,0])/marcheur)+2,radius/pas)

for j in range(1,(len(data[:,0])/marcheur)-1)):

    x=data[marcheur*j:(marcheur-1)*(j+1)),0].transpose()
    y=data[marcheur*j:(marcheur-1)*(j+1),1].transpose()

    points=zip(x,y)
    nb_points = []
    R = []
    T=KDTree(points)

    for i in np.linspace(0,radius-pas,radius/pas):
        densite[j,i]=((len(T.query_ball_point([0,0],r= i + pas)) - len(T.query_ball_point([0,0],r= i)))/(np.pi*(2*i*pas+pas**2)))
        R.append((i + 0.5*pas))

for l in np.linspace(0,radius-pas,radius/pas):
        R.append((l + 0.5*pas))

for k in range(radius/pas):
    densite[-2,k]=mean(densite[0:-3,k])
    densite[-1,k]=std(densite[0:-3,k])

moyenne

plt.figure(4)
p2=plt.plot(R,densite[-2,:], 'r-.o',label="Densite surfacique de bacteries", linewidth=2.0)
plt.xlabel("Rayon")
plt.legend()
plt.show()
