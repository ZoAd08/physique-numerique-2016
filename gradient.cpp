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


bool equation_droite(double x1, double y1, double x2, double y2)
	{
		double b = 0;
		b = y1 - ((x1*(y2-y1))/(x2-x1));
		if(b >= -0.5 && b <= 0.5  && pow(x1,2) > pow(x2,2))
		{
			return true;
		}
		else
		{
			return false;
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
			x[0][j]=(rand() % radius/2)+(-1)*(rand() % radius/2);
			y[0][j]=(rand() % radius/2)+(-1)*(rand() % radius/2);
			theta = (M_PI*(rand() % 359))/180;
			x[i][j]=x[i-1][j]+taille*cos(theta);
			y[i][j]=y[i-1][j]+taille*sin(theta);
			bool droite;
			droite = equation_droite(x[i-1][j], y[i-1][j], x[i][j], y[i][j]);

			if(droite == true)
			{
				x[i][j]=x[i-1][j]+taille*5*cos(theta);
				y[i][j]=y[i-1][j]+taille*5*sin(theta);
			}

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
		i += 1;
	}
	return sum/dimension;
}








int main()
{
	srand (time(NULL));
	freopen( "marcheur.txt", "w", stdout );
	double r;
	r=f(2000,2,20,200);

	return 0;
}
