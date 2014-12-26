#include "trajectoire.h"
#include "odometrie.h"
#include "reglages.h"
#include "asser.h"
#include "debug/affichage.h" //à virer
#include <math.h> //utiliser un tableau pour acos ??
#include <stdio.h> //TODO : à virer

//et encore de vilaines variables globales !
static s_trajectoire trajectoire;
static s_consigne consigne;

//TODO : implementer l'idée suivante pour les listes de points :
//quand on doit passer sur une liste de points donner une consigne beta constante
//et recalculer uniquement alpha sauf pour le dernier point où il faut ralentir
//de cette manière on ne ralentira pas en passant sur chaque points

void start()
{
	while(!sdl_manage_events())
	{
		update_consigne();
		asser(consigne);
		//actualise_position ici
	}
}

void update_consigne()
{
	switch (trajectoire.type)
	{
		case alpha_delta :
			make_trajectoire_alpha_delta(trajectoire.alpha,trajectoire.delta);
			trajectoire.type=null;
			break;
		case theta :
			make_trajectoire_theta(theta);
			trajectoire.type=null;
			break;
		case xy_absolu :
			make_trajectoire_xy_absolu(trajectoire.x_absolu,trajectoire.y_absolu);
			break;
		case xy_relatif :
			make_trajectoire_xy_relatif(trajectoire.x_relatif,trajectoire.y_relatif);
			break;
		case chemin :
			make_trajectoire_chemin(trajectoire.chemin);
			break;
		case stop :
			//TODO
			break;
		case null :
			break;
	}
}

void make_trajectoire_alpha_delta(int new_alpha, int new_delta)
{
	set_consigne_alpha_delta(new_alpha,new_delta);
	trajectoire.type=null;
}

void make_trajectoire_theta(int theta_voulu)
{
	int new_alpha=theta_voulu-get_theta_actuel();
	set_consigne_alpha_delta(new_alpha,0);
	trajectoire.type=null;
}

void make_trajectoire_xy_absolu(int x_voulu, int y_voulu)
{
	make_trajectoire_xy_relatif(x_voulu-get_x_actuel(),y_voulu-get_y_actuel());
}

void make_trajectoire_xy_relatif(int x_voulu, int y_voulu)
{
	int new_alpha;
	int new_delta;
	calcul_alpha_delta_restant(x_voulu, y_voulu, &new_alpha, &new_delta);

	//évite que le robot ne tourne pour rien quand il a atteint xy avec la précision voulue
	if (new_delta<-PRECISION_DELTA || PRECISION_DELTA<new_delta)
	{
		set_consigne_alpha_delta(new_alpha,new_delta);
	}
	else
	{
		trajectoire.type=null;
	}
}

void make_trajectoire_chemin(s_liste liste_positions)
{
	//si il ne reste plus qu'un point la trajectoire n'est plus du même type
	if (trajectoire.chemin.taille==1)
	{
		trajectoire.type=xy_absolu;
		trajectoire.x_absolu=liste_positions.point[0].x;
		trajectoire.y_absolu=liste_positions.point[0].y;
		return;

	}

	//calcul de la consigne
	int new_alpha;
	int new_delta;
	int x_voulu=liste_positions.point[liste_positions.taille-1].x-get_x_actuel();
	int y_voulu=liste_positions.point[liste_positions.taille-1].y-get_y_actuel();
	calcul_alpha_delta_restant(x_voulu, y_voulu, &new_alpha, &new_delta);
	int sgn_delta=(new_delta > 0) - (new_delta < 0);

	//gestion du changement de point "cible"
	if (new_delta<-PRECISION_DELTA || PRECISION_DELTA<new_delta)
	{
		set_consigne_alpha_delta(new_alpha,sgn_delta*CONSTANTE_DELTA);
	}
	else
	{
		trajectoire.chemin.taille-=1;
	}
}

void calcul_alpha_delta_restant(int x_voulu, int y_voulu, int * new_alpha, int * new_delta)
{
	//x et y sont relatifs mais l'orientation de des axes reste absolue

	//voir si pas meilleur moyen pour le calcul de sqrt
	*new_delta=(int)sqrt((double)(x_voulu*x_voulu+y_voulu*y_voulu));
	int sgn_x=(x_voulu > 0) - (x_voulu < 0);
	//TODO : réfléchir ce que implique sgn_x=0 -> possibilité d'entrainer des choses bizarres
	 //voir si pas meilleur moyen pour le calcul de acos (tableau ?)
	int theta_voulu=(int)(1000.0*acos((double)(y_voulu)/(double)(*new_delta))*(-1.0*sgn_x));
	*new_alpha=theta_voulu-get_theta_actuel();

	//on borne *new_alpha (à tester) entre pi et -pi
	*new_alpha=*new_alpha%((int)(DEUX_PI*1000.0));
	if (*new_alpha>(int)((DEUX_PI*1000.0)/2.0))
	{
		*new_alpha-=(int)(DEUX_PI*1000.0);
	}
	else if (*new_alpha<-(int)((DEUX_PI*1000.0)/2.0))
	{
		*new_alpha+=(int)(DEUX_PI*1000.0);
	}

	//TODO : gestion point non atteignable
	//(si l'on demande un point trop prés du robot et à la perpendiculaire de la direction du robot il se met à tourner)
	
	//gestion de la marche arrière
	if (*new_alpha>1571) //1571~=(pi/2)*1000
	{
		*new_alpha-=3142; //3142~=pi*1000
		*new_delta=-*new_delta;
	}
	else if (*new_alpha<-1571) //1571~=(pi/2)*1000
	{
		*new_alpha+=3142; //3142~=pi*1000
		*new_delta=-*new_delta;
	}
}

void set_trajectoire_alpha_delta(int alpha, int delta)
{
	trajectoire.type=alpha_delta;
	trajectoire.alpha=alpha;
	trajectoire.delta=delta;
}

void set_trajectoire_xy_relatif(int x, int y)
{
	trajectoire.type=xy_relatif;
	trajectoire.x_relatif=x;
	trajectoire.y_relatif=y;
}

void set_trajectoire_xy_absolu(int x, int y)
{
	trajectoire.type=xy_absolu;
	trajectoire.x_absolu=x;
	trajectoire.y_absolu=y;
}

void set_trajectoire_theta(int theta)
{
	trajectoire.type=theta;
	trajectoire.alpha=theta-get_theta_actuel();
}

void set_trajectoire_chemin(s_liste liste_positions)
{
	trajectoire.type=chemin;
	trajectoire.chemin=liste_positions;
}

void set_consigne_alpha_delta(int alpha, int delta)
{
	consigne.alpha=alpha+get_alpha_actuel();
	consigne.delta=delta+get_delta_actuel();
}

void init_trajectoire()
{
	trajectoire.type=null;
	trajectoire.delta=0;
	trajectoire.alpha=0;
}

//TODO : à virer (utile uniquement pour du debug)
int get_delta_voulu()
{
	return consigne.delta;
}

int get_alpha_voulu()
{
	return consigne.alpha;
}
