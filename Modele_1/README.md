Modèle 1

##1marcheurstat.cpp
Verification de que le mouvement de la bactérie est une marche aléatoire en l'absence de gradient de nutriment.

##multimarcheurs.cpp
Permet de tracer le déplacement moyen "r" à partir d'un nombre "nombre_de_marche" de marches
aléatoires en fonction du nombre de pas "0<It<Nmax", et de le comparer à la racine carrée du nombre de pas. Le déplacement est contraint dans un disque de rayon "radius" avec des conditions aux limites réflectives. Renvoie un fichier texte contenant en colonnes : le nombre de pas, le déplacement moyen par rapport à l'origine, l'écart type.

############################################################################################################################################################################################
Modèle de simulation de nage de bactéries à 2 dimensions dans une boîte circulaire.

##gradient.cpp

#Modèle physique

Le modèle simule la nage de bactéries dans un gradient de nutriments. La bactérie effectue une marche aléatoire, dans ce modèle, sa 
vitesse va dépendre du sens de sa nage. Lorsque la bactérie se déplace dans le sens du croissant gradient, celle ci accélère, lorsque qu'elle s'éloigne, sa vitesse est fixe.

#Simulation

-Les bactéries sont répartis uniformément au début de la simulation
-Lorque que le produit sclaire du vecteur déplacement et du gradient est négatif, la bactérie se déplace de la longueur du pas fixé ("taille")
-Lorque que le produit sclaire du vecteur déplacement et du gradient est positif, la longeur du pas effectuée est proportionelle au produit scalaire (taille*produit scalaire)

#Paramètres de la simulation

On peut changer les paramètres suivant dans la fonction f:

	* Nombre de pas totale
	* Longueur d'un pas
	* Rayon de la boîte
	* Nombre de bactérie

A la fin de la simulation, les coordonnées de tout les déplacements sont enregistrées dans le fichier "marcheur.txt

#Analyse des données (Il faut penser à vérifier que la valeur du rayon de la boîte et le nombre de bactérie soient bien égales à ceux du fichier "gradient.cpp" dans chaque fichier python)

##analyse.py
Permet de tracer la marche aléatoire des bactéries

##analysetranpose.py
Permet de tracer la position initiale et finale de la marche aleatoire de N particules et un histogramme de la distance au carée du point initiale au point finale.

##animation.py
Permet de suivre la trajectoire de toute les bacteries dans la boîte

##densiteradiale.py
Compte le nombre de bactéries et calcule la densité surfacique de bactérie selon un découpage en couronne d'épaisseur constante.
Trace le nombre de bactéries et la densité surfacique en fonction du rayon de l'anneau centrale de la couronne. On observe clairement des anneaux
