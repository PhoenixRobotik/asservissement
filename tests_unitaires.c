#include "tests_unitaires.h"
#include "hardware.h"
#if PIC_BUILD
#	if   GROS
#		include "reglages_gros.h"
#	elif PETIT
#		include "reglages_petit.h"
#	endif
#else
#	include "reglages_PC.h"
#endif

#include "../common_code/communication/s2a_emission.h"

#include "asser.h"
#include "odometrie.h"
#include "trajectoire.h"

void test_moteur_D(long int vitesse)
{
        int PWM_D=convert2PWM(vitesse);
        set_PWM_moteur_D(PWM_D);
}

void test_moteur_G(long int vitesse)
{
        int PWM_G=convert2PWM(vitesse);
        set_PWM_moteur_G(PWM_G);
}

void test_codeur_D()
{
    while(get_nbr_tick_D()==0){;}
    allumer_del();
}

void test_codeur_G()
{
    while(get_nbr_tick_G()==0){;}
    allumer_del();
}

void test_vitesse(long int vitesse)
{
	int PWM_G=convert2PWM(COEFF_MOTEUR_G*vitesse);
	int PWM_D=convert2PWM(COEFF_MOTEUR_D*vitesse);
	set_PWM_moteur_D(PWM_D);
	set_PWM_moteur_G(PWM_G);
}

void test_ecretage()
{
	long int commande;
	long int commande_preced=0;
	while(commande_preced!=MAX_VITESSE)
	{
		commande=MAX_VITESSE;
		ecretage(&commande,commande_preced);
		test_vitesse(commande);
		commande_preced=commande;
	}
	long int i;
	for(i=0;i<2000000;i++) {};
	while(commande_preced!=0)
	{
		commande=0;
		ecretage(&commande,commande_preced);
		test_vitesse(commande);
		commande_preced=commande;
	}
}

void test_distance(long int distance, long int vitesse)
{
	long int nbr_tick_D;
	long int nbr_tick_G;
	long int distance_actuelle=0;

	//si la distance est négative il faut changer de sens !
	if (distance<0)
	{
		vitesse=-vitesse;
	}

	test_vitesse(vitesse);
	while(abs(distance_actuelle)<abs(distance))
	{
		nbr_tick_D=get_nbr_tick_D();
		nbr_tick_G=get_nbr_tick_G();
		nbr_tick_D*=COEFF_CODEUR_D;
		nbr_tick_G*=COEFF_CODEUR_G;
		distance_actuelle=delta_mm(nbr_tick_D,nbr_tick_G);
	}
	test_vitesse(0);

}

void test_angle(long int angle, long int vitesse)
{
	long int nbr_tick_D;
	long int nbr_tick_G;
	long int angle_actuel=0;

	//si l'angle est négatif il faut changer de sens !
	if (angle<0)
	{
		vitesse=-vitesse;
	}

	int PWM=convert2PWM(vitesse);
	set_PWM_moteur_D(PWM);
	set_PWM_moteur_G(-PWM);

	while(abs(angle_actuel)<abs(angle))
	{
		nbr_tick_D=get_nbr_tick_D();
		nbr_tick_G=get_nbr_tick_G();
		nbr_tick_D*=COEFF_CODEUR_D;
		nbr_tick_G*=COEFF_CODEUR_G;
		angle_actuel=alpha_millirad(nbr_tick_D,nbr_tick_G);
	}
	test_vitesse(0);
}

void test_asser_alpha_delta(int alpha, int delta)
{
	set_trajectoire_alpha_delta(alpha,delta);
	start();
}

void test_asser_theta(int theta)
{
	set_trajectoire_theta(theta);
	start();
}

void test_asser_xy_relatif_courbe(int x, int y)
{
	set_trajectoire_mode(courbe);
	set_trajectoire_xy_relatif(x,y);
	start();
}

void test_asser_xy_absolu_courbe(int x, int y)
{
	set_trajectoire_mode(courbe);
	set_trajectoire_xy_absolu(x,y);
	start();
}

void test_asser_xy_relatif_tendu(int x, int y)
{
	set_trajectoire_mode(tendu);
	set_trajectoire_xy_relatif(x,y);
	start();
}

void test_asser_xy_absolu_tendu(int x, int y)
{
	set_trajectoire_mode(tendu);
	set_trajectoire_xy_absolu(x,y);
	start();
}

void test_asser_chemin(s_liste chemin)
{
	set_trajectoire_chemin(chemin);
	start();
}
