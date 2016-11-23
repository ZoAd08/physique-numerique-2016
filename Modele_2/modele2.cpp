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
#include <new>



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



//creation d'un objet bactérie qui est entièrement déterminé par sa position ainsi que par le temps avant son prochain tumble
class bacteria
{
	private:
	double x_position;
	double y_position;
	double* x_past = new double[99999999];
	double* y_past = new double[99999999];
	double* temps_past = new double[99999999];
	long double temps;
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
		while(compteur < 1 ) //distribution au hasard dans un disque de rayon = radius
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

	//evolution dans le temps d'une bactérie, renvoie le temps avant le prochain tumble
	double evolution()
	{
		double vitesse = 20; //micronse/seconde
		double pas_normal = 20; //microns
		double sens1 = 3.5; //3secondes
		double sens2 = 1.5; //secondes
		double a = temps_past[iterateur - 1] - sens1;
		double b = temps_past[iterateur - 1] - sens2;
		double x1,x2,y1,y2,pas,theta;

		if (iterateur <= 10) //initialisation de la simulation avec une marche aléatoire de 9 pas sans mémoire
		{
			x1 = 0;
			y1 = 0;
			x2 = 0;
			y2 = 0;
		}

		if(iterateur > 10) //prise en compte du gradient de concentration par la bactérie
		{
			for(int i = iterateur-1; i >= 0 ; --i) 
			{
				if(a <= temps_past[i])
				{
					x1 = x_past[i]-((temps_past[i]-a)*(vitesse));
					y1 = y_past[i]-((temps_past[i]-a)*(vitesse));
				}
				if(b <= temps_past[i])
				{
					x2 = x_past[i]-((temps_past[i]-b)*(vitesse));
					y2 = y_past[i]-((temps_past[i]-b)*(vitesse));
				}
			}
		}


		double concentration = 10*exp(-0.00005*(pow(x1,2) + pow(y1,2))) - 10*exp(-0.00005*(pow(x2,2) + pow(y2,2)));


		//fonction de réponse de la bactérie en fonction de la différence de concentration à deux instants
		if(concentration < 0)
		{
			pas = 2.*pas_normal;
		}
		if(concentration > 0)
		{
			pas = 0.5*pas_normal;
		}
		if(concentration == 0)
		{
			pas = pas_normal;
		}
		if(iterateur == 1)
		{
			theta = ((double)rand()/(double)RAND_MAX)*(2*M_PI);	
		}
		if(iterateur > 1)
		{
			double phi = 2.0*asin(((double)rand()/(double)RAND_MAX)*(2)-1); //distribution de l'angle entre deux directions de run après un tumble
			theta = - phi + theta_past; //angle de projection en coordonnées polaires.
		}
		theta_past = theta;
		x_position += pas*cos(theta);
		y_position += pas*sin(theta);

		if((pow(x_position,2)+pow(y_position,2) > pow(100000,2))) //condition aux limites réflective
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


const int nombre_de_bacteries = 500;

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
	while(k < 5000)
	{
		int min = minimum(tps , nombre_de_bacteries);
		long double value = tps[min];
		for (int i = 0; i < nombre_de_bacteries; ++i)
		{
			tps[i] -= value;
		}
		tps[min] += bac[min].evolution();

/*
		for (int i = 0; i < nombre_de_bacteries; ++i) //permet d'enregistrer toutes les trajectoires (lent)
		{
			bac[i].enregistrement();
		}

*/
		k += value;
		
		min = 0;
		value = 0;
	}
	for(int i = 0; i < nombre_de_bacteries; ++i)
	{
		bac[i].enregistrement();
	}

  return 0;
}
