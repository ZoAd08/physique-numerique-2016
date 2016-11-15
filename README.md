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

                                  ***

 Le fichier 1marcheurstat.cpp permet de modéliser la nage d'un nombre N de
 bactéries dans un milieu homogène à symétrie circulaire de rayon R. La position initiale
 est déterminée aléatoirement. Le fichier analyse.py permet de tracer la marche aléatoire
 des N bactéries.

***************************************************************************************************

 Le fichier gradient.cpp permet de simuler la nage de N bactéries dans un gradient
 d'attractant, le pas augmente proportionnellement avec la produit scalaire entrecoup
 le vecteur déplacement de la bactérie et le gradient du champ de concentration.
 Cela permet de mettre en évidence "l'effet volcan". On trace les marches aléatoires
 à l'aide du fichier analyse.py.
