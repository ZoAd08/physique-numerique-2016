import numpy as np
import matplotlib.pyplot as plt

marcheur = 50
data = np.loadtxt("marcheur.txt")
x=np.zeros(((int(len(data[:,0])/marcheur)),marcheur))
y=np.zeros(((int(len(data[:,0])/marcheur)),marcheur))



for i in range(len(data[:,0])):
	for j in range(marcheur):
		if i < len(data[:,0])/marcheur:
			x[i,j]=data[marcheur*i+j,0]
			y[i,j]=data[marcheur*i+j,1]
		
		
plt.figure(1)
for i in range(marcheur):
	plt.plot(x[-1,i],y[-1,i],'o')
	
plt.show()
