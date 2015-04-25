#include "trajectoire.h"
#include "odometrie.h"
#include "../common_code/debug.h" //à virer
#if USE_SDL
#include "simulation/affichage.h" // à virer
#endif

/*TODO : implémenter le protocole de comunication comme ça
avait été fait dans message.c pour le code présent dans "old"*/


/*---------------------------------------------------------------------------*
 * RECEPTION                                                                 *
 *---------------------------------------------------------------------------*/

void analyse_message()
{
	//fonction appelée depuis la couche basse hardware.c
	//en fonction du message la fonction appele les foctions correspondantes ci-dessous
	// en se passant de se fait des fonctions en "new"
}

void new_alpha_delta(int alpha, int delta)
{
	set_trajectoire_alpha_delta(alpha,delta);
}

void new_xy_relatif(int x, int y)
{
	set_trajectoire_xy_relatif(x,y);
}

void new_xy_absolu(int x, int y)
{
	set_trajectoire_xy_absolu(x,y);
}

void set_mode_tendu()
{
	set_trajectoire_mode(tendu);
}

void set_mode_courbe()
{
	set_trajectoire_mode(courbe);
}

void new_theta(int theta)
{
	set_trajectoire_theta(theta);
}

void new_chemin()
{
	//faire attention à ce que la liste de positions soit inversée
	//(le premier point dans la liste est en réalité le dernier à atteindre)
}


/*---------------------------------------------------------------------------*
 * ENVOI                                                                     *
 *---------------------------------------------------------------------------*/

void send_position_atteinte()
{
	debug(3, "atteint\n");
}
