#define MAX_SPEED 3999	// Entrée max des PWMs = 2*Période des PWMs
						// Fréquence des PWMs = 20 kHz
#define MIN_SPEED 900	// Entrée min sauf pour l'arrêt

void init();
void init_osc();
void io_init();
void PWM1_init ();
void QEI_init ();
void timer_init();
void UART_init();
void set_PWM_moteur_D(int PWM);
void set_PWM_moteur_G(int PWM);
void motors_stop(void); // Arrete les moteurs
long get_nbr_tick_D();
long get_nbr_tick_G();
void reset_nbr_tick();
int doit_attendre();
void allumer_del(void);
void eteindre_del(void);
void pause_ms(unsigned short n);
void pause_s(unsigned short n);

/*---------------------------------------------------------------------------*
 * Couche basse uart                                                         *
 *---------------------------------------------------------------------------*/

#define INT_UART_TX
#define RX_BUFFER_SIZE 16
#define TX_BUFFER_SIZE 64

/* Functions headers */

void UART_putc(unsigned char c);
void UART_send_tab(unsigned char *addr, unsigned char size);

/* Retourne le nombre d'octets lus */
int UART_getc(unsigned char *byte);