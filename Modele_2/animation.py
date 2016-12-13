'''/*******************************************************************************
 *  @file    animation.cpp
 *  @author  Benjamin GALLOIS
 *  @date    18/11/2016
 *  @version 1.0
 *  @resume Permet de tracer le mouvement animé des bactéries.
*******************************************************************************/'''



import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time
import numpy as np


#lecture du fichier de config qui defini automatiquement les parametres utilises pour produire les donnees
config = np.loadtxt("config.txt")
marcheur = int(config[0,0])
temps = config[0,1]
radius = config[1,0]
gain = "Gain : " + str(config[1,1]) + "\n"
sens = "Comparaison entre " + str(config[2,0]) + " seconde et " + str(config[2,1]) + " seconde" + "\n"


data = np.loadtxt("marcheur.txt")
x=np.zeros(((int(len(data[:,0])/marcheur)),marcheur))
y=np.zeros(((int(len(data[:,0])/marcheur)),marcheur))

for i in range(len(data[:,0])+1):
	for j in range(marcheur):
		if i < len(data[:,0])/marcheur:
			x[i,j]=data[marcheur*i+j,0]
			y[i,j]=data[marcheur*i+j,1]






#initialisation de la figure

fig = plt.figure(2)
ax = plt.axes(xlim=(-radius, radius), ylim=(-radius, radius),aspect='equal')
time_text = ax.text(0.02, 0.95, '', transform=ax.transAxes)
circle1 = plt.Circle((0, 0), radius, color='b',fill=False)
ax = plt.gca()
ax.add_artist(circle1)
line, = ax.plot([], [], 'ro', ms=5)



#animation du graphique

def animate(i):
    pas = str((i*temps)/(len(x[:,0])))
    line.set_data(x[i,:], y[i,:])
    time_text.set_text('Temps : ' + pas)
    return line, time_text,





#trace de l'animation


ani = animation.FuncAnimation(fig, animate, frames=len(x[:,0]), interval=1e-100, blit=True, repeat=True)

legend_nbmarcheurs = "Nombre de bacteries : " + str(marcheur) + "\n"
legend_nbpas = "Temps : " + str(temps)
plt.title(legend_nbmarcheurs + legend_nbpas)
ani.save('clock.mp4', fps=200, dpi=100)
#plt.show()
