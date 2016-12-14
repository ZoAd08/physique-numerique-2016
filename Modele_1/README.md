######################################################
#    physique-numerique-2016                         #
#    @Benjamin GALLOIS & Djinthana DUFOUR.           #
######################################################


###################################################################################################
Modélisation du mouvement de bactéries (runs and tumbles) dans un milieu
homogène et dans un gradient de nutriments pour mettre en évidence "l'effet volcan".
###################################################################################################


***************************************************************************************************
On modélise ici la nage des bactéries par une marche aléatoire à deux dimensions.
La bactérie effectue une succession d'avancées rectilignes de longueur "a"
 appellées "run", entrecoupé de changement de direction aléatoire. la bactérie
 est capable de sentir son environnement et de se déplacer dans un gradient
 en allongeant la longueur "a" de son run.

                                  ***

 On modélise dans un premier la nage de bactéries dans un milieu homogène à
 symétrie circulaire de rayon R.
 Le programme multimarcheurs.cpp permet de simuler la marche d'une bactérie et
 d'en faire la statistique. Le script gnuplot_multimarcheurs permet d'analyser
 les données et de tracer le déplacement carré moyen pris sur un nombre de
 marches aléatoires données en fonction du nombre de pas,ainsi que le
 déplacement carré moyen en fonction du nombre de marche aléatoire.

##1marcheurstat.cpp
 Le fichier 1marcheurstat.cpp permet de modéliser la nage d'un nombre N de
 bactéries dans un milieu homogène à symétrie circulaire de rayon R. La position initiale
 est déterminée aléatoirement. Le fichier analyse.py permet de tracer la marche aléatoire
 des N bactéries.

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

permet de simuler la nage de N bactéries dans un gradient
 d'attractant, le pas augmente proportionnellement avec la produit scalaire entre
 le vecteur déplacement de la bactérie et le gradient du champ de concentration.
 Cela permet de mettre en évidence "l'effet volcan". On trace les marches aléatoires
 à l'aide du fichier analyse.py.

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
