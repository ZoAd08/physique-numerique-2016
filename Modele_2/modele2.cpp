/***********************************************************************************
 *  @file    modele2.cpp
 *  @author  Benjamin GALLOIS
 *  @date    18/11/2016
 *  @version 1.0
 *  @resume Déplacement de bactéries dans un gradient de nutriment. Les bactéries
 	    ne sont sensibles qu'à la différence de concentration prise entre deux instants.
************************************************************************************/



#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <fstream>
#include <ctime>
#include <new>
#include <random>



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
	double* theta_past = new double[99999999];
	int iterateur;
	double vitesse = 20; //micronse/seconde
	double pas_normal = 20; //microns
	double sens1 = 3; //3secondes
	double sens2 = 1; //secondes
	double radius = 1000;

	public:
	//constructeur
	bacteria()
	{
    temps = 0;
		temps_past[0] = 0.;
		theta_past[0] = 0;
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

/*Permet de déterminer l'évolution dans le temps d'une bactérie. La simulation commence avec l'apparition aléatoire de la bactérie dans une disque. Elle effectue d'abord une marche aléatoire qui suit une distribution d'angle en accord avec les données expérimentales relevées dans la littérature, en négligeant l'effet du gradient de concentration de nutriment de 9 pas. Après 10 pas, la bactérie effectue une marche aléatoire biaisée, elle compare la valeur du gradient de concentration entre deux instants antérieurs et allonge(resp réduit) son run si elle se déplace vers une zone plus (resp moins) concentrée. La fonction renvoie le temps qu'il reste avant le prochain tumble de la bactérie.
*/
	double evolution()
	{
		double a = temps_past[iterateur - 1] - sens1;
		double b = temps_past[iterateur - 1] - sens2;
		double x1,x2,y1,y2,pas,theta;

		if (iterateur <= 10) 
		{
			x1 = 0;
			y1 = 0;
			x2 = 0;
			y2 = 0;
		}

		if(iterateur > 10) 
		{
			for(int i = iterateur-1; i >= 0 ; --i) //A VERIFIER
			{
				if(a <= temps_past[i])
				{
					x1 = (sqrt(pow(x_past[i]-x_past[i-1],2) + pow(y_past[i]-y_past[i-1],2))- ((temps_past[i]-a)*(vitesse)))*cos(theta_past[i]);
					y1 = (sqrt(pow(x_past[i]-x_past[i-1],2) + pow(y_past[i]-y_past[i-1],2))- ((temps_past[i]-a)*(vitesse)))*sin(theta_past[i]);
				}
				if(b <= temps_past[i])
				{
					x2 = (sqrt(pow(x_past[i]-x_past[i-1],2) + pow(y_past[i]-y_past[i-1],2))- ((temps_past[i]-b)*(vitesse)))*cos(theta_past[i]);
					y2 = (sqrt(pow(x_past[i]-x_past[i-1],2) + pow(y_past[i]-y_past[i-1],2))- ((temps_past[i]-b)*(vitesse)))*sin(theta_past[i]);
				}
			}
		}


		double concentration = 1000*exp(-0.00005*(pow(x1,2) + pow(y1,2))) - 10*exp(-0.00005*(pow(x2,2) + pow(y2,2)));


		//fonction de réponse de la bactérie en fonction de la différence de concentration entre deux instants
		
		std::ranlux24_base generator;
		if(concentration < 0)
		{
			std::exponential_distribution<double> distribution(1/(2*pas_normal));
			pas = distribution(generator);
		}
		else if(concentration > 0)
		{
			std::exponential_distribution<double> distribution(1/(0.5*pas_normal));
			pas = distribution(generator);
		}
		else if(concentration == 0)
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
			theta = - phi + theta_past[iterateur-1]; //angle de projection en coordonnées polaires.
		}
		
		theta_past[iterateur] = theta;
		x_position += pas*cos(theta);
		y_position += pas*sin(theta);
		temps = pas/vitesse;
		
		if((pow(x_position,2)+pow(y_position,2)) > pow(10000,2)) //condition aux limites réflectives
		{
			x_position = radius*cos(theta);
			y_position = radius*sin(theta);
			theta_past[iterateur] = theta + M_PI;
			temps = (1./vitesse)*sqrt(pow(x_position-x_past[iterateur -1],2) + pow(y_position-y_past[iterateur -1],2));
		}
		temps_past[iterateur] = temps_past[iterateur-1] + temps;
		x_past[iterateur] = x_position;
		y_past[iterateur] = y_position;
		iterateur += 1;
		return temps;
	}

//enregistrement de la trajectoire dans un fichier .txt
	void enregistrement()
	{
		printf ( "%.3f %.20f \t %.20u \n", x_position,y_position,0);
	}

//enregistrement de la position finale des bactéries en discernant les bactéries en run (1), et les bactéries en tumble (0)
	void position_finale()
	{
		double x_final, y_final;
		if(temps == 0)
		{
			printf ( "%.3f %.20f \t %.20u \n", x_position,y_position,0);
		}
		
		else //A VERIFIER
		{
			x_final = (sqrt(pow(x_position-x_past[iterateur-1],2) + pow(y_position-y_past[iterateur-1],2)) -vitesse*temps)*cos(theta_past[iterateur]) ;
			y_final = (sqrt(pow(y_position-x_past[iterateur-1],2) + pow(y_position-y_past[iterateur-1],2))-vitesse*temps)*sin(theta_past[iterateur]) ;
			printf ( "%.3f %.20f \t %.20u \n", x_final,y_final,1);
		}	
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
	while(k < 3000)
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
		bac[i].position_finale();
	}

	freopen( "config.txt", "w", stdout );
	printf ( "%.3d %.20f \n", nombre_de_bacteries , k);
  return 0;
}
