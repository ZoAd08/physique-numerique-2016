'''/*******************************************************************************
 *  @file    analyse.cpp
 *  @author  Benjamin GALLOIS
 *  @date    18/11/2016
 *  @version 1.2
 *  @resume  Permet de tracer la marche aleatoire de N particules en prennant
 			 le fichier .txt du fichier 1marcheurstat.cpp
*******************************************************************************/'''





import numpy as np
import matplotlib.pyplot as plt
import matplotlib.lines as mlines

marcheur = 1000
radius = 4.
data = np.loadtxt("marcheur.txt")
x=np.zeros(((int(len(data[:,0])/marcheur)),marcheur))
y=np.zeros(((int(len(data[:,0])/marcheur)),marcheur))



for i in range(len(data[:,0])+1):
	for j in range(marcheur):
		if i < len(data[:,0])/marcheur:
			x[i,j]=data[marcheur*i+j,0]
			y[i,j]=data[marcheur*i+j,1]


plt.figure(1)
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
plt.show()
