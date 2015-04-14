#ifndef RECEPTION_H
#define RECEPTION_H

/** Analyse le texte en provenance de l'uart. Transmet les commandes au robot.
 *
 * \note Fonction a exécuter lors des interruption en provenance de l'uart
 * \bug Les nombres négatifs ne sont pas pris en compte
 * \todo Ajouter une fonction stop() pour arrêter le robot sur place
 * \todo Ajouter une fonction update() pour mettre à jour toutes les variables
 *     (x,y, alpha, delta et theta) en fonction de l'état actuel réél du robot
 * \todo Ajouter une fonction info() qui transmet (uart, printf ou autre) l'état
 *     actuel du robot (position et angle au moins)
 *
 * x=value       : mise à jour de la variable x (coordonnée en cm)
 * y=value       : mise à jour de la variable y (coordonnée en cm)
 * alpha=value   : mise à jour de la variable alpha (angle relatif en degré)
 * delta=value   : mise à jour de la variable delta (distance en cm)
 * theta=value   : mise à jour de la variable theta (angle absolu en degré)
 *
 * q             : quitte la simulation
 * alpha_delta() : new_alpha_delta(alpha, delta);
 * xy_relatif()  : new_xy_relatif(x,y);
 * xy_absolu()   : new_xy_absolu(x,y);
 * theta()       : new_theta(theta);
 *
 * \exemple
 *
 * x=300
 * y=400
 * xy_relatif() # le robot avance de 300 en x, 400 en y
 * xy_relatif() # le robot avance de nouveau de 300 en x, 400 en y
 */
void uart_interrupt(char uart_char);


#endif /* RECEPTION_H */
