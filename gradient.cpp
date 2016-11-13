/*******************************************************************************
 *  @file    gradient.cpp
 *  @author  Benjamin GALLOIS
 *  @date    18/11/2016
 *  @version 1.0
 *  @resume
*******************************************************************************/



#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <ctime>


double* gradient(double x , double y)
{
	static double array[2];
	double concentration = exp(-(pow(x,2) + pow(y,2)));
	array[0] = -(2)*x*exp(-(pow(x,2) + pow(y,2)));
	array[1] = -(2)*y*exp(-(pow(x,2) + pow(y,2)));
	return array;
}

double produit_scalaire(double* vector1 , double* vector2)
{
	return vector1[0]*vector2[0] + vector1[1]*vector2[1];
}

double* vecteur_deplacement(double xa , double ya , double xb , double yb)
{
	static double vecteur_r[2];
	vecteur_r[0]=xb-xa;
	vecteur_r[1]=yb-ya;
	return vecteur_r;
}

double regles_deplacement(double valeur)
{
	if(valeur > 0)
	{
		return 50*valeur + 1;
	}

	if(valeur < 0)
	{
		return 0.5;
	}
	else
	{
		return 0.5;
	}
}



//step = nombre de pas de la marche, taille = longueur d'un pas, radius = rayon de la boîte, marcheur = nombre de marcheurs aléatoires
double f(int step, float taille, int radius, int marcheur)
{
	double x[step][marcheur], y[step][marcheur], theta;
	double a[marcheur];
	for (int i=1 ; i<step; ++i)
	{
		for (int j=0 ; j<marcheur ; ++j)
		{
			x[0][j]=((double)rand()/(double)RAND_MAX)*4. - ((double)rand()/(double)RAND_MAX)*4.;
			y[0][j]=((double)rand()/(double)RAND_MAX)*4. - ((double)rand()/(double)RAND_MAX)*4.;
			theta = (M_PI*(rand() % 359))/180;
			x[i][j]=x[i-1][j]+taille*cos(theta);
			y[i][j]=y[i-1][j]+taille*sin(theta);

			double *deplacement , *vecteurgrad;
			double scalaire;
			deplacement = vecteur_deplacement(x[i-1][j] , y[i-1][j] , x[i][j] , y[i][j]);
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
			printf ( "%.3f \t %.3f \t %.20f \n", x[i][j],y[i][j],scalaire);
			if (i==step-1)
			{
				a[j]=sqrt(pow(x[i][j],2)+pow(y[i][j],2));
	   		 }
		}
	}
	for(int i=0;i<marcheur;++i)
	{

	}
}



double moyenne(double vector[], double dimension)
{
	int i = 0;
	double sum = 0;

	while(i<dimension)
	{
		sum = sum + vector[i];
		i += 1;
	}
	return sum/dimension;
}








int main()
{
	srand (time(NULL));
	freopen( "marcheur.txt", "w", stdout );
	double r;
	r=f(1000,0.2,4,500);

	return 0;
}
