######################################################
#    physique-numerique-2016                         #
#    @Benjamin GALLOIS & Djinthana DUFOUR.           #
######################################################


Modèle de simulation de nage de bactéries à 2 dimensions dans une boîte circulaire.



Modèle physique.

Le modèle simule la nage de bactéries dans un gradient de nutriments. La bactérie effectue une marche aléatoire dont la 
longueur du pas dépend de la différence de concentration que la bactérie ressent en comparant la concentration entre deux instants antérieurs.



Modèle de la simulation.

Le simulation commence avec une marche aléatoire sans gradient de concentration pour initialiser la simulation. Après 10 pas, la bactérie commence à sentir le gradient de concentration et à faire des comparaisons temporelles de concentration qui font changer la longueur de son pas.



Principe.

* On initialise une liste qui contient le temps avant le prochain tumble pour chaque bactérie.
* On calcule le minimum de la liste qui représente la bactérie qui fera un tumble en premier, puis on soustrait ce minimum à chaque élément de la liste.
* On calcule la durée avant le prochain tumble de cette bactérie et on l'ajoute à son élément dans la liste.
* On répète ces opérations jusqu'à un temps où on veux arrêter la simulation. 



Calcule de la durée du prochaine tumble.

* La durée avant le prochain tumble est déterminée grâce à la taille d'un pas, la vitesse de la bactérie étant considérée constante. On détermine la taille d'un pas en fonction de la différence de concentration, prise à deux instants antérieurs (fonction de réponse de la bactérie). Le concentration en nutriment est une gausienne à deux dimensions dont la distance caractéristique et l'amplitude sont ajustables.



Paramètres de la simulation.

** Paramètre d'une bactérie à modifier dans les attributs de la class "bacteria".

	* Vitesse d'une bactérie.
	* Les instants où la bactérie sent le gradient.
	* La distance moyenne d'un pas quand la bactérie n'est pas dans un gradient.
	* Fonction de réponse de la bactérie.

** Paramètre de l'environnement à modifier dans la class "bacteria".

	* Intensité et distance caractéristique du gradient de nutriments.

** Paramètre de la simulation à modifier dans "main()".

	* Nombre de bactéries.
	* Durée de la simulation.
	* Données que la simulation enregistre dans le fichier marcheur.txt
	* Nombre de coordonnées à exporter.



Utilisation de la simulation.

* Tracer de la trajectoire des bactéries.

	** Régler la variable "type" sur 0 dans le fichier modele2.cpp puis exécuter le fichier, visualiser les données avec le fichier analyse.py. 

* Tracer la position finale et initiale des bactéries.

	** Régler la variable "type" sur 1 dans le fichier modele2.cpp puis exécuter le fichier, visualiser les données avec le fichier analysetranspose.py

* Tracer la densité de bactéries en fonction du rayon.

	** Régler la variable "type" sur 3 et le nombre de réalisation à prendre en compte pour faire la moyenne dans le fichier modele2.cpp puis exécuter le fichier, visualiser les données avec le fichier densiteradiale.py. On peut aussi visualiser les données exportées par densiteradiale.py grâce au script gnuplot_time.

* Pour chaque simulation, le programme renvoie un fichier de configuration.

					##################################################################################################
					# Nombre de bactéries									Durée de la simulation 					 #
					# Rayon de la boîte	 									Gain                                     #
					# Temps 1												Temps 2 (où la bactérie sens le gradient)#
					# Pas moyen de la bactérie 1	 						0.00000000000000000000 				     #
					##################################################################################################


* Tracer la variation des rayons en fonction des paramètres : Le fichier densiteradiale.py permet de calculer et d'exporter le rayon interne externe et maximal de l'anneau dans un fichier output.txt. Il est nécessaire de régler la position approximitative du maximum dans la fonction Newton et celles des largeurs à mis hauteurs pour que l'algorithme converge, ainsi que le tirage aléatoire des moyennes. On peut ensuite tracer la statistique des rayons sur plusieurs simulation avec le fichier output.py.


* Animation des bactéries.

	** Régler la variable "type" sur 0 dans le fichier modele2.cpp puis exécuter le fichier, visualiser les données avec le fichier animation.py. Attention !!! La durée de la simulation entre 2 images n'est pas constante, ce qui entraîne des artéfacts de visualisation (bactéries qui accélerent etc...).




#Liste des fichiers

* Production des données (C++) :

	- modele2.cpp (Benjamin Gallois) : production des données et exportation dans des fichiers.txt.


* Analyse/visualisation des données (python et Gnuplot) :
	
	- animation.py (Benjamin Gallois) : créer une animation dela simulation.
	- analyse.py (Benjamin Gallois & Djinthana Dufour) : permet de tracer l'ensemble des trajectoires des bactéries.
	- analysetranspose.py (Djinthana Dufour): permet de tracer la position initiale et la position finale des bactéries.
	- densiteradiale.py (Benjamin Gallois & Djinthana Dufour) : permet de tracer la densité de bactérie en fonction du rayon de la boîte, le comptage s'effectuant en couronnes d'épaisseurs constantes, d'ajuster la courbe obtenue, d'en trouver le maximum ainsi que l'abscisse des largeurs à mis hauteur, permet ensuite d'exporter les données traitées dans des fichiers .txt pour en faire une statistique.
	- output.py (Benjamin Gallois) : permet de faire la statistique de plusieurs simulation et de la tracer sur un diagramme à barres.
	- gnuplot_time (Benjamin Gallois) : permet de tracer sur un même graphique la densité radiale pour plusieurs jeux de paramètres.


#On a reussi à simuler le déplacement d'un ensemble de bactéries dans un gradient d'attractant en partant d'un modèle où le déplacement peut être modélisé comme une marche aléatoire dont la taille du pas dépend de concentration que la bactérie compare à deux instants antérieurs de sa trajectoire (Segall JE, Block SM, Berg HC. Temporal comparisons in bacterial chemotaxis. Proc Natl Acad Sci U S A. 1986 Dec;83(23):8987–8991). En ajustant les paramètres de la simulation aux données de la littératures (Berg, H.C., E. coli in Motion. (Springer-Verlag, NY, 2004) (Berg, H.C., Random Walks in Biology. (Princeton, Princeton, 1983). Expanded edition, 1993) on a pu mettre en évidence un effet volcan, c'est à dire un anneaux de concentration de bactéries autour d'un maximum de concentration en attractant. La visualisation et l'étude des données nous ont permis de relier les caractéritiques de l'anneau (rayon intérieur, maximal et extérieur) aux paramètres de la simulation.