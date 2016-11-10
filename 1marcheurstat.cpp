/*******************************************************************************
 *  @file    1marcheurstat.cpp
 *  @author  Benjamin GALLOIS
 *  @date    18/11/2016
 *  @version 1.0
 *  @resume  Permet de tracer la marche aléatoire d'un nombre N de bactérie.
 						 Renvoie un fichier texte contenant les positions x et y dans deux
						 colones, les lignes sont dans l'ordre des particules (x0 particule1
					  x0 particule2 etc...)
*******************************************************************************/



#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <ctime>



//step = nombre de pas de la marche, taille = longueur d'un pas, radius = rayon de la boîte, marcheur = nombre de marcheurs aléatoires
double f(int step, float taille, float radius, int marcheur)
{
	double x[step][marcheur], y[step][marcheur], theta;
	double a[marcheur];
	for (int i=1 ; i<step; ++i)
	{
		for (int j=0 ; j<marcheur ; ++j)
		{
			x[0][j]=0;
			y[0][j]=0;
			theta = (M_PI*(rand() % 359))/180;
			x[i][j]=x[i-1][j]+taille*cos(theta);
			y[i][j]=y[i-1][j]+taille*sin(theta);

			if((pow(x[i][j],2)+pow(y[i][j],2)>pow(radius,2)))
			{
				x[i][j]=x[i-1][j];
				y[i][j]=y[i-1][j];
			}
			printf ( "%.3f \t %.3f \n", x[i][j],y[i][j]);
			if (i==step-1)
			{
				a[j]=sqrt(pow(x[i][j],2)+pow(y[i][j],2));
	   		 }
		}
	}
	for(int i=0;i<marcheur;++i)
	{
	//printf ( "%.3u \t %.3f \n", i,a[i]);
	}
}



double moyenne(double vector[], double dimension)
{
	int i = 0;
	double sum = 0;

	while(i<dimension)
	{
		sum = sum + vector[i];
		i = i+1;
	}
	return sum/dimension;
}



double err(double vector[], double dimension, double mean)
{
	int i = 0;
	double sum = 0;
	while(i<dimension)
	{
		sum = sum + pow((vector[i]-mean),2);
		i = i+1;
	}
	return sqrt(sum/dimension);
}


int main()
{
	srand (time(NULL));
	freopen( "marcheur.txt", "w", stdout );
	double r;
	r=f(10000,0.1,100000,50);

	return 0;
}
