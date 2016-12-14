'''/*********************************************************************************************************************************************************************
 *  @file    densiteradiale.py
 *  @author  Benjamin Gallois
 *  @date    13/12/2016
 *  @version 1.0
 *  @resume  Permet de tracer un diagramme a barres a partir d'un fichier .txt contenant en colonnes : le rayon interieur, le rayon maximal et le rayon exterieur.
 			 Et 5N lignes qui contiennent les résultats pour N simulations independantes. Le programme fait la moyenne et l'ecart type puis trace le diagramme avec les incertitudes.

***********************************************************************************************************************************************************************/'''





import numpy as np
import matplotlib.pyplot as plt



ind = np.arange(5) 
width = 0.2
N=3 #nombre de simulations independante pour chaque parametre teste
data = np.loadtxt("output.txt")
moyenneint = []
incertitudeint=[]
moyenne = []
incertitude=[]
moyenneext = []
incertitudeext=[]



for i in range(len(data[:,1])/N):
	moyenneint.append(np.mean(data[N*i:N*i+N,0]))
	moyenne.append(np.mean(data[N*i:N*i+N,1]))
	moyenneext.append(np.mean(data[N*i:N*i+N,2]))
	incertitudeint.append(np.std(data[N*i:N*i+N,0]))
	incertitude.append(np.std(data[N*i:N*i+N,1]))
	incertitudeext.append(np.std(data[N*i:N*i+N,2]))



fig, ax = plt.subplots()	
rects1 = ax.bar(ind, moyenneint, width, color='r', yerr=incertitudeint)
rects2 = ax.bar(ind+ width, moyenne, width, color='y', yerr=incertitude)
rects3 = ax.bar(ind+ 2*width, moyenneext, width, color='b', yerr=incertitudeext)
ax.grid(True)
ax.set_ylabel('Rayon')
ax.set_xticks(ind + width)
ax.set_xticklabels(('1-0', '2-0', '3-0', '8-0', '16-0'))
ax.set_ylim([0,1750])
ax.legend((rects1[0], rects2[0],rects3[0]), ('Rayon interieur', 'Rayon maximal', 'Rayon exterieur'))




def label(rects):
    for rect in rects:
        height = rect.get_height()
        ax.text(rect.get_x() + rect.get_width()/2., 70+height,
                '%d' % int(height),
                ha='center', va='bottom')

label(rects1)
label(rects2)
label(rects3)

plt.show()
