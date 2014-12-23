#ifndef TRAJECTOIRE_H
#define TRAJECTOIRE_H

typedef enum
{
	alpha_delta,
	xy_absolu,
	xy_relatif,
	liste_xy,
	theta,
	stop,
	null

} e_type_trajectoire;

typedef struct
{
	e_type_trajectoire type;
	int alpha;
	int delta;
	int x_absolu;
	int y_absolu;
	int x_relatif;
	int y_relatif;
	int liste_xy;

}s_trajectoire;

typedef struct
{
	int alpha;
	int delta;
} s_consigne;

void start();
void update_consigne();

void set_trajectoire_alpha_delta(int alpha, int delta);
void set_trajectoire_xy_relatif(int x, int y);
void set_trajectoire_xy_absolu(int x, int y);
void set_trajectoire_theta(int theta);

void make_trajectoire_alpha_delta(int new_alpha, int new_delta);
void make_trajectoire_xy_relatif(int x_voulu, int y_voulu);
void make_trajectoire_xy_absolu(int x_voulu, int y_voulu);
void make_trajectoire_theta(int theta_voulu);

void init_trajectoire();

void set_consigne_alpha_delta();

//TODO : à virer (utile uniquement pour du debug)
int get_delta_voulu();
int get_alpha_voulu();

#endif