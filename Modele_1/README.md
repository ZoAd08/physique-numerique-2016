Mod�le 1

##1marcheurstat.cpp
Verification de que le mouvement de la bact�rie est une marche al�atoire en l'absence de gradient de nutriment.

##multimarcheurs.cpp
Permet de tracer le d�placement moyen "r" � partir d'un nombre "nombre_de_marche" de marches
al�atoires en fonction du nombre de pas "0<It<Nmax", et de le comparer � la racine carr�e du nombre de pas. Le d�placement est contraint dans un disque de rayon "radius" avec des conditions aux limites r�flectives. Renvoie un fichier texte contenant en colonnes : le nombre de pas, le d�placement moyen par rapport � l'origine, l'�cart type.

############################################################################################################################################################################################
Mod�le de simulation de nage de bact�ries � 2 dimensions dans une bo�te circulaire.

##gradient.cpp

#Mod�le physique

Le mod�le simule la nage de bact�ries dans un gradient de nutriments. La bact�rie effectue une marche al�atoire, dans ce mod�le, sa 
vitesse va d�pendre du sens de sa nage. Lorsque la bact�rie se d�place dans le sens du croissant gradient, celle ci acc�l�re, lorsque qu'elle s'�loigne, sa vitesse est fixe.

#Simulation

-Les bact�ries sont r�partis uniform�ment au d�but de la simulation
-Lorque que le produit sclaire du vecteur d�placement et du gradient est n�gatif, la bact�rie se d�place de la longueur du pas fix� ("taille")
-Lorque que le produit sclaire du vecteur d�placement et du gradient est positif, la longeur du pas effectu�e est proportionelle au produit scalaire (taille*produit scalaire)

#Param�tres de la simulation

On peut changer les param�tres suivant dans la fonction f:

	* Nombre de pas totale
	* Longueur d'un pas
	* Rayon de la bo�te
	* Nombre de bact�rie

A la fin de la simulation, les coordonn�es de tout les d�placements sont enregistr�es dans le fichier "marcheur.txt

#Analyse des donn�es (Il faut penser � v�rifier que la valeur du rayon de la bo�te et le nombre de bact�rie soient bien �gales � ceux du fichier "gradient.cpp" dans chaque fichier python)

##analyse.py
Permet de tracer la marche al�atoire des bact�ries

##analysetranpose.py
Permet de tracer la position initiale et finale de la marche aleatoire de N particules et un histogramme de la distance au car�e du point initiale au point finale.

##animation.py
Permet de suivre la trajectoire de toute les bacteries dans la bo�te

##densiteradiale.py
Compte le nombre de bact�ries et calcule la densit� surfacique de bact�rie selon un d�coupage en couronne d'�paisseur constante.
Trace le nombre de bact�ries et la densit� surfacique en fonction du rayon de l'anneau centrale de la couronne. On observe clairement des anneaux
