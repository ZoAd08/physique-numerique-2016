/*******************************************************************************
 *  @file    modele2.cpp
 *  @author  Benjamin GALLOIS
 *  @date    18/11/2016
 *  @version 1.0
 *  @resume Déplacement de bactéries dans un gradient de nutriment. Les bactéries
 						ne sont sensibles qu'à la concentration. La longueur de leur run est
						proportionnelle à la concentration.
*******************************************************************************/



#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <fstream>
#include <ctime>


//détermine l'indice correspondant à la valeur minimale d'un array.
int minimum(double array[] , int dimension)
{
	double min = array[0];
	int a = 0;
	if(dimension == 1)
	{
			a = 0;
	}
	else
	{
		for(int i = 1 ; i < dimension ; ++i)
		{
				if(array[i] < min)
				{
					min = array[i];
					a = i;
				}
		}
	}
	return a;
}



//creation d'un objet bactérie qui est entièrement déterminé par sa position ainsi
//que par le temps avant son prochain tumble
class bacteria
{
	private:
	double x_position;
	double y_position;
	double x_past;
	double y_past;
	double temps_past;
	double temps;

	public:
	//constructeur
	bacteria()
	{
    temps = 0;
		temps_past = 1;
		double radius = 5;
		int compteur = 0;
		while(compteur < 1 )
		{
			double l = ((double)rand()/(double)RAND_MAX)*(2*radius)-radius;
			double m = ((double)rand()/(double)RAND_MAX)*(2*radius)-radius;
			if((pow(l,2)+pow(m,2) < pow(radius,2)))
			{
				x_position = l;
				y_position = m;
				x_past = l;
				y_past = m;
				compteur += 1;
			}
			else
			{
					compteur = 0;
			}
		}
  }

	//evolution dans le temps d'une bactérie
	double evolution()
	{
		double vitesse = 1;
		double retard = 1;
		x_past = x_position;
		y_past = y_position;
		double concentration = exp(-0.1*(pow(x_position-(retard/temps_past)*(x_position-x_past),2) + pow(y_position-(retard/temps_past)*(y_position-y_past),2)));
		double pas = 1.5*concentration + 0.01 ;
		double theta = (M_PI*(rand() % 359))/180;
		x_position += pas*cos(theta);
		y_position += pas*sin(theta);
		if((pow(x_position,2)+pow(y_position,2) > pow(5.,2)))
		{
			x_position -= pas*cos(theta);
			y_position -= pas*sin(theta);
		}
		temps = pas/vitesse;
		temps_past = temps;
		return temps;
	}

	//enregistrement des coordonnées dans un fichier .txt
	void enregistrement()
	{
		printf ( "%.3f %.20f \n", x_position,y_position);
	}
};


int main()
{
	srand (time(NULL));
	freopen( "marcheur.txt", "w", stdout );
	int nombre_de_bacteries = 200;
  bacteria bac[nombre_de_bacteries];
	double tps[nombre_de_bacteries];

	for(int i = 0; i < nombre_de_bacteries; ++i)
	{
		bac[i].enregistrement();
	}
	int k = 0;
	while(k < 10000)
	{
		int min = minimum(tps , nombre_de_bacteries);
		double value = tps[min];
		for (int i = 0; i < nombre_de_bacteries; ++i)
		{
			tps[i] -= value;
		}
		tps[min] += bac[min].evolution();
		for (int i = 0; i < nombre_de_bacteries; ++i)
		{
			bac[i].enregistrement();
		}
		min = 0;
		value = 0;
		k += 1;
	}

  return 0;
}
