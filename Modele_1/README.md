######################################################
#    physique-numerique-2016                         #
#    @Benjamin GALLOIS & Djinthana DUFOUR.           #
######################################################


###################################################################################################
Mod�lisation du mouvement de bact�ries (runs and tumbles) dans un milieu
homog�ne et dans un gradient de nutriments pour mettre en �vidence "l'effet volcan".
###################################################################################################


***************************************************************************************************
On mod�lise ici la nage des bact�ries par une marche al�atoire � deux dimensions.
La bact�rie effectue une succession d'avanc�es rectilignes de longueur "a"
 appell�es "run", entrecoup� de changement de direction al�atoire. la bact�rie
 est capable de sentir son environnement et de se d�placer dans un gradient
 en allongeant la longueur "a" de son run.

                                  ***

 On mod�lise dans un premier la nage de bact�ries dans un milieu homog�ne �
 sym�trie circulaire de rayon R.
 Le programme multimarcheurs.cpp permet de simuler la marche d'une bact�rie et
 d'en faire la statistique. Le script gnuplot_multimarcheurs permet d'analyser
 les donn�es et de tracer le d�placement carr� moyen pris sur un nombre de
 marches al�atoires donn�es en fonction du nombre de pas,ainsi que le
 d�placement carr� moyen en fonction du nombre de marche al�atoire.

##1marcheurstat.cpp
 Le fichier 1marcheurstat.cpp permet de mod�liser la nage d'un nombre N de
 bact�ries dans un milieu homog�ne � sym�trie circulaire de rayon R. La position initiale
 est d�termin�e al�atoirement. Le fichier analyse.py permet de tracer la marche al�atoire
 des N bact�ries.

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

permet de simuler la nage de N bact�ries dans un gradient
 d'attractant, le pas augmente proportionnellement avec la produit scalaire entre
 le vecteur d�placement de la bact�rie et le gradient du champ de concentration.
 Cela permet de mettre en �vidence "l'effet volcan". On trace les marches al�atoires
 � l'aide du fichier analyse.py.

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
