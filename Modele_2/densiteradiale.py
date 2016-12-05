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
x=np.zeros((2,marcheur))
y=np.zeros((2,marcheur))
points=np.zeros((marcheur,2))


x[0,:]=data[0:marcheur,0].transpose()
y[0,:]=data[0:marcheur,1].transpose()
x[1,:]=data[len(data[:,0])-marcheur:len(data[:,0]),0].transpose()
y[1,:]=data[len(data[:,0])-marcheur:len(data[:,0]),1].transpose()

points=zip(x[1,:],y[1,:])
nb_points = []
densite = []
R = []
T=KDTree(points)

for i in np.linspace(0,radius-pas,radius/pas):
    nb_points.append(len(T.query_ball_point([0,0],r= i + pas)) - len(T.query_ball_point([0,0],r= i)))
    densite.append((len(T.query_ball_point([0,0],r= i + pas)) - len(T.query_ball_point([0,0],r= i)))/(np.pi*(2*i*pas+pas**2)))
    R.append((i + 0.5*pas))

#densite=zip(R,nb_points)
# print densite

plt.figure(4)
#p1=plt.plot(R,nb_points, 'b-.o', label="Nombre de bacteries", linewidth=2.0)
p2=plt.plot(R,densite, 'r-.o',label="Densite surfacique de bacteries", linewidth=2.0)
plt.xlabel("Rayon")
plt.legend()
plt.show()
