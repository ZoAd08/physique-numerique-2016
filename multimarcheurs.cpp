/*******************************************************************************
 *  @file    multimarcheurs.cpp
 *  @author  Benjamin GALLOIS
 *  @date    18/11/2016
 *  @version 1.5
 *  @resume  Permet de tracer le déplacement moyen "r" à
 						 partir d'un nombre "nombre_de_marche" de marches
					 	 aléatoires en fonction du nombre de pas "0<It<Nmax", et
					 	 de le comparer à la racine carrée du nombre de pas.
						 Le déplacement est contraint dans un disque de rayon "radius"
						 avec des conditions aux limites réflectives. Renvoie un fichier
						 texte contenant en colonnes : le nombre de pas, le déplacement
						 moyen par rapport à l'origine, la std.
*******************************************************************************/





#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <ctime>


//step = nombre de pas de la marche, taille = longueur d'un pas, radius = rayon de la boîte
double f(int step, float taille, float radius)
{
	double x[step], y[step],theta;
	x[0]=0;
	y[0]=0;
	for (int i=1 ; i<step; ++i)
	{
		theta = (M_PI*(rand() % 359))/180; //précision de un degré sur la marche aléatoire
		x[i]=x[i-1]+taille*cos(theta);
		y[i]=y[i-1]+taille*sin(theta);

		if((pow(x[i],2)+pow(y[i],2)>pow(radius,2))) //condition aux limites réflectives
		{
			x[i]=x[i-1];
			y[i]=y[i-1];
		}
		//printf ( "%.3f \t %.3f \n", x[i],y[i]); //Permet de visualiser la marche aléatoire
    if(i==step-1)
    {
			double r;
			return r=sqrt(pow(x[i],2)+pow(y[i],2));
   	}
	}
}


//calcule la moyenne d'un vecteur de dimension connue
double moyenne(double vector[], double dimension)
{
	int i = 0;
	double sum = 0;

	while(i<dimension)
	{
		sum += pow(vector[i],1);
		i += 1;
	}
	return sum/dimension;
}


//calcule la std d'un vecteur de dimension et de moyenne connue
double err(double vector[], double dimension, double mean)
{
	int i = 0;
	double sum = 0;
	while(i<dimension)
	{
		sum += pow((vector[i]-mean),2);
		i += 1;
	}
	return sqrt(sum/dimension);
}


int main()
{
	srand (time(NULL));
	freopen( "output.txt", "w", stdout );
	int it = 10;
	int b,int_nombre_de_marche;
	int Nmax = 5000;
	double r[Nmax],c,nombre_de_marche;

	nombre_de_marche = 1000;
	int_nombre_de_marche = nombre_de_marche;

	while(it < Nmax)
	{
		double sum[int_nombre_de_marche],error[int_nombre_de_marche];
		b=0;
	    	while(b < nombre_de_marche)
		{
		    sum[b] = f(it,1,10000000000);
		    b += 1;
		}
		c = b;
		r[it] = moyenne(sum,nombre_de_marche);
		error[it] = err(sum,nombre_de_marche,r[it]);
		printf ("%.4u \t %.3f \t %.3f \n",it,r[it],error[it]);
		if(it<1000)
		{
				it += 20;
		}
		else
		{
				it += 80;
		}

	}


	return 0;
}
