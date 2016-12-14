# -*- coding: cp1252 -*-
'''/*********************************************************************************************
 *  @file    analysetranspose.py
 *  @author  Djinthana Dufour
 *  @date    15/11/2016
 *  @version 1.0
 *  @resume  Permet de tracer la position initiale et finale de la marche aléatoire N particules.

*********************************************************************************************/'''





import numpy as np
import matplotlib.pyplot as plt
import matplotlib.lines as mlines
from numpy import transpose
import time
start_time = time.time()

marcheur = 250
radius = 2.
data = np.loadtxt("marcheur.txt")
x=np.zeros((2,marcheur))
y=np.zeros((2,marcheur))

x[0,:]=data[0:marcheur,0].transpose()
y[0,:]=data[0:marcheur,1].transpose()
x[1,:]=data[len(data[:,0])-marcheur:len(data[:,0]),0].transpose()
y[1,:]=data[len(data[:,0])-marcheur:len(data[:,0]),1].transpose()


legend_nbmarcheurs = "Nombre de bacteries : " + str(marcheur) + "\n"
legend_nbpas = "Nombre de pas : " + str((len(data[:,0])/marcheur)-1)
plt.figure(3)
for i in range(marcheur):
	plt.plot(x[0,i],y[0,i],'b.')
	plt.plot(x[-1,i],y[-1,i],'r.')

circle1 = plt.Circle((0, 0), radius, color='b',fill=False)
ax = plt.gca()
ax.add_artist(circle1)
plt.ylim((-radius,radius))
plt.xlim((-radius,radius))
plt.axis('equal')
Init = mlines.Line2D([], [], color='blue', marker=".",markersize=15, label='Position initiale')
Fin = mlines.Line2D([], [], color='red', marker=".",markersize=15, label='Position finale')
plt.legend(handles=[Init,Fin])
plt.title(legend_nbmarcheurs + legend_nbpas)
plt.show()
print "--- %s seconds ---" % (time.time() - start_time)
