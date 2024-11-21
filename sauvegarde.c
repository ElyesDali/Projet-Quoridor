#include <stdio.h>
#include "sauvegarde.h"


void sauvegarder_partie(const char* save, const Partie* partie) {
    FILE* sauvegarde = fopen("../save.txt", "w");
    if (sauvegarde == NULL) {
        printf("Fichier invalide");
        return 0;
    }
    fprintf(sauvegarde, "%d", partie->tour_actuel);

    fprintf(sauvegarde, "%d", partie->nb_joueurs);

    for (int i = 0; i < nb_joueurs; i++) {
        fprintf(sauvegarde, "Pion %d: x: %d; y:%d", i, partie->position_pion[i].x, partie->position_pion[i].y); // On récupère les positions des pions
    }

    do {
        fprintf(sauvegarde, "Mur %d: x: %d; y: %d; type: %c",i, partie->position_murs[i].x, partie->position_murs[i].y, partie-> position_murs[i].type); // On récupère les positions de tous les murs placés
    }while(murs_places[i] != " " );

    for (int i = 0; i < nb_joueurs; i++) {
        fprintf(sauvegarde, "ID Joueur: %d; Barrières restantes: %d", &partie->donnees[i].player_ID, &partie->donnees[i].remainingBarriers); // On récupère les murs restants de chaque joueur
    }

    fclose(save);
    return 1;
}



void charger_partie(const char* save, Partie* partie) {

    FILE* nv_partie = fopen("../save.txt", "r");

    if (nv_partie == NULL) {
        printf("Fichier invalide");
        return 0;
    }


    fscanf(nv_partie,"%d", &partie->tour_actuel); // La personne dont c'est le tour

    for (int i = 0; i < nb_joueurs; i++) {
        fscanf(nv_partie, "Pion %d: x: %d; y:%d", i, &partie->position_pion[i].x, &partie->position_pion[i].y); // On récupère les positions des pions
    }

    do{
        fscanf(nv_partie, "Mur %d: x: %d; y: %d; type: %c",i, &partie->position_murs[i].x, &partie->position_murs[i].y, &partie-> position_murs[i].type); // On récupère les positions de tous les murs placés
        }while(position_murs[i] != "\0");

    }

    for (int i = 0; i < nb_joueurs; i++) {
        fscanf(nv_partie, "ID Joueur: %d; Barrières restantes: %d", &partie->donnees[i].player_ID, &partie->donnees[i].remainingBarriers); // On récupère les murs restants de chaque joueur
    }

    fclose(save);
    return 1;




}