
#include <stdio.h>
#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

typedef struct {
    Case position_pion[4]; // Les positions de tous les pions
    Barriere position_murs[50]; // On charge toutes les positions des barrières placées
    Player donnees[4]; // On récupère les barrières restantes et l'ID du joueur
    int tour_actuel; // Le joueur dont c'est le tour
}Partie;

void sauvegarder_partie(FILE* save, const Partie* partie);
void charger_partie(FILE* save, Partie* partie);


#endif //SAUVEGARDE_H
