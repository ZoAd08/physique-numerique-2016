# -*- coding: utf-8 -*-
'''/*********************************************************************************************
 *  @file    densiteradiale.py
 *  @author  Djinthana Dufour & Benjamin Gallois
 *  @date    17/11/2016
 *  @version 1.0
 *  @resume  Permet de tracer la densite de bacteries en fonction du rayon
*********************************************************************************************/'''


import numpy as np
import scipy.spatial as sp
import matplotlib.pyplot as plt
from numpy import transpose
from scipy.spatial import KDTree
from scipy.optimize import curve_fit
from scipy.optimize import fsolve
from scipy.optimize import newton



#lecture du fichier de config qui defini automatiquement les parametres utilises pour produire les donnees
config = np.loadtxt("config.txt")
marcheur = int(config[0,0])
temps = config[0,1]
radius = config[1,0]
gain = "Gain : " + str(config[1,1]) + "\n"
sens = "Comparaison entre " + str(config[2,0]) + " seconde et " + str(config[2,1]) + " seconde" + "\n"
pas=radius / 20.



#lecture des donnees
data = np.loadtxt("marcheur.txt")
points=np.zeros((marcheur,2))
densite=np.zeros(((len(data[:,0])/marcheur)+2,int(radius/pas)))
R = []



#comptage du nombre de bacteries par couronne
for j in range(1,(len(data[:,0])/marcheur)):
    x=np.zeros(marcheur)
    y=np.zeros(marcheur)
    x=data[marcheur*j:(marcheur)*(j+1),0].transpose()
    y=data[marcheur*j:(marcheur)*(j+1),1].transpose()
    points = zip(x,y)
    T=KDTree(points)
    m = 0
    for i in np.linspace(0,radius-pas,radius/pas):
        densite[j-1,m]=((len(T.query_ball_point([0,0],r= i + pas)) - len(T.query_ball_point([0,0],r= i)))/(np.pi*(2*i*pas+pas**2)))
        m = m +1
        

for l in np.linspace(0,radius-pas,radius/pas):
        R.append((l + 0.5*pas))



for k in range(int(radius/pas)):
    densite[-2,k]=np.mean(densite[0:-3,k])
    densite[-1,k]=np.std(densite[0:-3,k])



def fitfunc(x,a,b,c,d,e):
	return (a*x**2+b*x+c)*np.exp(-d*x)+e

def derifitfunc(x,a,b,c,d,e):
    return (a*x**2+b*x+c)*np.exp(-d*x)*(-d) + (2*a*x+b)*np.exp(-d*x)

n = 0
for m in range(len(densite[-2,:])):
    if densite[-2,m] == 0:
        n = m
    if densite[-3,m] ==0:
        densite[-3,m] = 0.01

popt, pcov = curve_fit(fitfunc, R[n+1:-1], densite[-2,n+1:-1],p0=[-2.0e-9,9.0e-7,-0.0008,0.0013,0.0007],sigma= densite[-3,n+1:-1])


x=np.linspace(0,radius,100)

maximum = newton(derifitfunc, 360, args=(popt[0],popt[1],popt[2],popt[3],popt[4]), tol=10**(-10),maxiter=1000)
print maximum

def solve(x):
	return fitfunc(x,popt[0],popt[1],popt[2],popt[3],popt[4]) - maximum

root = fsolve(solve,[200,700])
print root




'''
out = "\n"+ str(root[0]) + " " + str(0) + " " + str(root[1])
fichier = open("output.txt", "a")
fichier.write(out)
fichier.close()
'''

#trace de la courbe
plt.figure()
plt.plot(x,fitfunc(x,popt[0],popt[1],popt[2],popt[3],popt[4]))
plt.plot(x,np.ones(len(x))*0.5*(fitfunc(maximum,popt[0],popt[1],popt[2],popt[3],popt[4])))
plt.errorbar(R, densite[-2,:], yerr = densite[-1,:], fmt = 'r.', label="Densite surfacique de bacteries")
plt.xlabel("Rayon")
plt.ylabel("Densite")
plt.legend()
plt.show()
