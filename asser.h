#ifndef ASSER_H
#define ASSER_H

#include "trajectoire.h"

//macro pour le calcul de valeur absolue
#define abs(x) ((x) < 0 ? - (x) : (x))
//macro pour le signe
#define sgn(x) ((x) < 0 ? - (1) : (1))

typedef struct
{
	int preced;
	int actuelle;
	long int sum;
} s_erreur;

void init_asser();
void asser(s_consigne consigne);

//appelées de l'extérieur uniquement pour les tests unitaires
int convert2PWM(long int commande);
void ecretage(long int * reponse,long int reponse_preced);

#endif
