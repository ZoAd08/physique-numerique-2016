Modèle de simulation de nage de bactéries à 2 dimensions dans une boîte circulaire.



Modèle physique.

Le modèle simule la nage de bactéries dans un gradient de nutriments. La bactérie effectue une marche aléatoire dont la 
longueur du pas dépend de la différence de concentration que la bactérie resssent en comparant la concentration entre deux instants.



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

	** Régler la variable "type" sur 1 et le nombre de réalisation à prendre en compte pour faire la moyenne dans le fichier modele2.cpp puis exécuter le fichier, visualiser les données avec le fichier densiteradiale.cpp

* Pour chaque simulation, le programme renvoie un fichier de configuration.

					##################################################################################################
					# Nombre de bactéries									Durée de la simulation 					 #
					# Rayon de la boîte	 									Gain                                     #
					# Temps 1												Temps 2 (où la bactérie sens le gradient)#
					# Pas moyen de la bactérie 1	 						0.00000000000000000000 				     #
					##################################################################################################