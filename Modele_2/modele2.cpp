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
	double x_past[20000];
	double y_past[20000];
	double temps_past[20000];
	double temps;
	double theta_past;
	int iterateur;

	public:
	//constructeur
	bacteria()
	{
    temps = 0;
		temps_past[0] = 0.;
		theta_past = 0;
		iterateur = 1;
		double radius = 1000;
		int compteur = 0;
		while(compteur < 1 )
		{
			double l = ((double)rand()/(double)RAND_MAX)*(2*radius)-radius;
			double m = ((double)rand()/(double)RAND_MAX)*(2*radius)-radius;
			if((pow(l,2)+pow(m,2) < pow(radius,2)))
			{
				x_position = l;
				y_position = m;
				x_past[0] = l;
				y_past[0] = m;
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
		double vitesse = 20; //micronse/seconde
		double pas_normal = 20; //microns
		double sens1 = 3; //secondes
		double sens2 = 1; //secondes
		double a = temps_past[iterateur - 1] - sens1;
		double b = temps_past[iterateur - 1] - sens2;
		double x1,x2,y1,y2,pas;

		if (iterateur <= 10)
		{
			x1 = 0;
			y1 = 0;
			x2 = 0;
			y2 = 0;
		}

		if(iterateur > 10)
		{
			for(int i = 0; i < iterateur ; ++i)
			{
				if(a < temps_past[i])
				{
					x1 = x_past[i]-((temps_past[i]-a)*(vitesse));
					y1 = y_past[i]-((temps_past[i]-a)*(vitesse));
				}
				if(b < temps_past[i])
				{
					x2 = x_past[i]-((temps_past[i]-b)*(vitesse));
					y2 = y_past[i]-((temps_past[i]-b)*(vitesse));
				}
			}
		}
		long double concentration1 = 1000*exp(-0.00005*(pow(x1,2) + pow(y1,2)));
		long double concentration2 = 1000*exp(-0.00005*(pow(x2,2) + pow(y2,2)));
		long double concentration = concentration1 - concentration2;
		if(concentration < 0)
		{
			pas = 1.5*pas_normal;
		}
		if(concentration > 0)
		{
			pas = 0.5*pas_normal;
			//std::cout << "NAN" << std::endl;
		}
		if(concentration == 0)
		{
			pas = pas_normal;
		}
		double phi = 2.0*asin(((double)rand()/(double)RAND_MAX)*(2)-1);
		double theta = - phi + theta_past;
		theta_past = theta;
		x_position += pas*cos(theta);
		y_position += pas*sin(theta);
		if((pow(x_position,2)+pow(y_position,2) > pow(1000,2)))
		{
			x_position -= pas*cos(theta);
			y_position -= pas*sin(theta);
		}
		temps = pas/vitesse;
		temps_past[iterateur] = temps_past[iterateur-1] + temps;
		x_past[iterateur] = x_position;
		y_past[iterateur] = y_position;
		iterateur += 1;
		return temps;
	}

	//enregistrement des coordonnées dans un fichier .txt
	void enregistrement()
	{
		printf ( "%.3f %.20f \n", x_position,y_position);
	}
};


const int nombre_de_bacteries = 1;

int main()
{
	srand (time(NULL));
	freopen( "marcheur.txt", "w", stdout );
  bacteria bac[nombre_de_bacteries];
	double tps[nombre_de_bacteries];

	for(int i = 0; i < nombre_de_bacteries; ++i)
	{
		bac[i].enregistrement();
	}
	double k = 0;
	while(k < 1200)
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
		k += value;
		min = 0;
		value = 0;
	}

  return 0;
}
