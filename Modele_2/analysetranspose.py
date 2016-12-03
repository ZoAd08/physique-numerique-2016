# -*- coding: cp1252 -*-
'''/*********************************************************************************************
 *  @file    analysetranspose.py
 *  @author  Benjamin GALLOIS & Djinthana Dufour
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

config = np.loadtxt("config.txt")
marcheur = int(config[0,0])
temps = config[0,1]
radius = config[1,0]
gain = "Gain : " + str(config[1,1]) + "\n"
sens = "Comparaison entre " + str(config[2,0]) + " seconde et " + str(config[2,1]) + " seconde" + "\n"
data = np.loadtxt("marcheur.txt")
x=np.zeros((2,marcheur))
y=np.zeros((2,marcheur))
runvstumble = np.zeros((2,marcheur))

x[0,:]=data[0:marcheur,0].transpose()
y[0,:]=data[0:marcheur,1].transpose()
runvstumble[0,:]=data[0:marcheur,2].transpose()
x[1,:]=data[len(data[:,0])-marcheur:len(data[:,0]),0].transpose()
y[1,:]=data[len(data[:,0])-marcheur:len(data[:,0]),1].transpose()
runvstumble[1,:]=data[len(data[:,0])-marcheur:len(data[:,0]),2].transpose()


legend_nbmarcheurs = "Nombre de bacteries : " + str(marcheur) + "\n"
legend_nbpas = "Temps (secondes) : " + str(temps) + "\n"
plt.figure(3)
for i in range(marcheur):
	if runvstumble[1,i] == 0 :
		plt.plot(x[-1,i],y[-1,i],'r.')
	if runvstumble[1,i] == 1 :
		plt.plot(x[-1,i],y[-1,i],'m.')
	plt.plot(x[0,i],y[0,i],'y.')

circle1 = plt.Circle((0, 0), radius, color='b',fill=False)
ax = plt.gca()
ax.add_artist(circle1)
plt.ylim((-radius,radius))
plt.xlim((-radius,radius))
plt.axis('equal')
Init = mlines.Line2D([], [], color='yellow', marker=".",markersize=15, label='Position initiale')
Fin = mlines.Line2D([], [], color='red', marker=".",markersize=15, label='Position finale tumble')
Fin2 = mlines.Line2D([], [], color='magenta', marker=".",markersize=15, label='Position finale run')
plt.legend(handles=[Init,Fin,Fin2])
plt.title(legend_nbmarcheurs + legend_nbpas + gain + sens)
plt.show()
print "--- %s seconds ---" % (time.time() - start_time)
