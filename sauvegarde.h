
#include <stdio.h>

#include "Barriere.h"
#include "Plato.h"
#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

typedef struct {
    Case position_pion[4]; // Les positions de tous les pions
    Barriere position_murs[30]; // On charge toutes les positions des barrières placées
    Player donnees[4]; // On récupère les barrières restantes
    int joueur_actuel; // Le joueur dont c'est le tour
    int nb_joueurs;
}Partie;

int sauvegarder_partie(const char* FILE, const Partie* partie);
int charger_partie(const char* FILE, Partie* partie);


#endif //SAUVEGARDE_H
