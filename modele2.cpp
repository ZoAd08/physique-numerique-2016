/*******************************************************************************
 *  @file    modele2.cpp
 *  @author  Benjamin GALLOIS
 *  @date    18/11/2016
 *  @version 1.0
 *  @resume
*******************************************************************************/



#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <fstream>
#include <ctime>



//renvoie la concentration locale en nutriment
double concentration(double x , double y)
{
	return concentration = exp(-(pow(x,2) + pow(y,2)));
}


//longueur du pas en fonction de la concentration en nutriment
double longueur_pas(double concentration)
{
  return concentration;
}


double f(int temps_maximum, float taille, double radius, int marcheur)
{
  double x[][marcheur], y[][marcheur], theta;
  double a[marcheur];
  for (int j=0 ; j<marcheur ; ++j)
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
