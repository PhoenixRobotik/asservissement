#ifndef HARDWARE_H
#define HARDWARE_H

#include <setup.h>


void init_hardware();
void set_PWM_moteur_D(int PWM);
void set_PWM_moteur_G(int PWM);
long int get_nbr_tick_D();
long int get_nbr_tick_G();
void attente_synchro();

void allumer_del();
void eteindre_del();

void allumer_autres_del();
void eteindre_autres_del();
void toggle_autres_del();


void motors_stop();

int UART_getc(unsigned char *c);

int arret();

#endif
