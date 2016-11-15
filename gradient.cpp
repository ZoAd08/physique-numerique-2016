/*******************************************************************************
 *  @file    gradient.cpp
 *  @author  Benjamin GALLOIS
 *  @date    18/11/2016
 *  @version 1.0
 *  @resume  Le fichier gradient.cpp permet de simuler la nage de N bactéries dans un gradient
 						 d'attractant, le pas augmente proportionnellement avec la produit scalaire entrecoup
 						 le vecteur déplacement de la bactérie et le gradient du champ de concentration.
 						 Cela permet de mettre en évidence "l'effet volcan". On trace les marches aléatoires
 					 	 à l'aide du fichier analyse.py.
*******************************************************************************/



#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <fstream>
#include <ctime>




//gradient de concentration, renvoie un vecteur à deux composantes
double* gradient(double x , double y)
{
	static double array[2];
	double concentration = exp(-(pow(x,2) + pow(y,2)));
	array[0] = -(2)*x*exp(-(pow(x,2) + pow(y,2)));
	array[1] = -(2)*y*exp(-(pow(x,2) + pow(y,2)));
	return array;
}

//calcule le produit scalaire entre deux vecteurs
double produit_scalaire(double* vector1 , double* vector2)
{
	return vector1[0]*vector2[0] + vector1[1]*vector2[1];
}

//calcule le vecteur déplacement à partir des coordonnées de deux points
double* vecteur_deplacement(double xa , double ya , double xb , double yb)
{
	static double vecteur_r[2];
	vecteur_r[0]=xb-xa;
	vecteur_r[1]=yb-ya;
	return vecteur_r;
}

//régles qui régissent le déplacement d'une bactérie suivant l'orientation de son vecteur déplacement et du gradient
double regles_deplacement(double valeur)
{
	if(valeur > 0)
	{
		return 100*valeur+1;
	}

	if(valeur < 0)
	{
		return 1;
	}
	else
	{
		return 1;
	}
}



//step = nombre de pas de la marche, taille = longueur d'un pas, radius = rayon de la boîte, marcheur = nombre de marcheurs aléatoires
double f(int step, float taille, double radius, int marcheur)
{
	double x[step][marcheur], y[step][marcheur], theta;
	double a[marcheur];
	for (int i=1 ; i<step; ++i)
	{
		for (int j=0 ; j<marcheur ; ++j)
		{
			if(i ==1)
			{
				int compteur = 0;
				while(compteur <= 1 )
				{
					double l = ((double)rand()/(double)RAND_MAX)*(2*radius)-radius;
					double m = ((double)rand()/(double)RAND_MAX)*(2*radius)-radius;
					if((pow(l,2)+pow(m,2) < pow(radius,2)))
					{
						x[0][j] = l;
						y[0][j] = m;
						printf ( "%.3f %.20f \n ", x[0][j],y[0][j]);
						compteur += 1;
					}
					else
					{
							compteur = 0;
					}
				}
			}
			theta = (M_PI*(rand() % 359))/180;
			x[i][j]=x[i-1][j]+taille*cos(theta);
			y[i][j]=y[i-1][j]+taille*sin(theta);

			double *deplacement , *vecteurgrad;
			double scalaire;
			int retard = 0;
			deplacement = vecteur_deplacement(x[i-1-retard][j] , y[i-1-retard][j] , x[i-retard][j] , y[i-retard][j]);
			vecteurgrad = gradient(x[i-1][j] , y[i-1][j]);
			scalaire = produit_scalaire(deplacement , vecteurgrad);
			double rule = regles_deplacement(scalaire);

			x[i][j]=x[i-1][j]+taille*rule*cos(theta);
			y[i][j]=y[i-1][j]+taille*rule*sin(theta);

			if((pow(x[i][j],2)+pow(y[i][j],2)>pow(radius,2)))
			{
				x[i][j]=x[i-1][j];
				y[i][j]=y[i-1][j];
			}
			printf ( "%.3f %.20f \n", x[i][j],y[i][j]);
			if (i==step-1)
			{
				a[j]=sqrt(pow(x[i][j],2)+pow(y[i][j],2));
	   		 }
		}
	}
}



int main()
{
	srand (time(NULL));
	freopen( "marcheur.txt", "w", stdout );
	double r;
	r=f(100,0.1,2,500);
	return 0;
}
