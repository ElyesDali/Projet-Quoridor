#include <stdio.h>
#include "sauvegarde.h"
#include "time.h"


int sauvegarder_partie(const char* save, const Partie* partie) {
    FILE* sauvegarde = fopen("save.txt", "w");
    if (sauvegarde == NULL) {
        printf("Fichier invalide");
        return 0;
    }
    fprintf(sauvegarde, "Joueur actuel: %d\n", partie->joueur_actuel);
    fprintf(sauvegarde, "Nombre de joueurs: %d\n", partie->nb_joueurs);

    for (int i = 0; i < partie->nb_joueurs; i++) {
        fprintf(sauvegarde, "Pion %d: x: %d; y: %d\n", i + 1, partie->position_pion[i].x, partie->position_pion[i].y);
    }

    for (int i = 0; i < 30; i++) {
        if (partie->position_murs[i].type != '\0' && partie->position_murs[i].x >= 0 && partie->position_murs[i].y >= 0) {
            fprintf(sauvegarde, "Mur %d: x: %d; y: %d; type: %c\n", i + 1, partie->position_murs[i].x, partie->position_murs[i].y, partie->position_murs[i].type);
        }
    }

    for (int i = 0; i < partie->nb_joueurs; i++) {
        fprintf(sauvegarde, "Joueur: %d; Barrières restantes: %d\n", i + 1, partie->donnees[i].remainingBarriers);
    }

    printf("Saving game to save.txt...\n");
    fclose(sauvegarde);
    return 1;
}



int charger_partie(const char* save, Partie* partie) {
    FILE* nv_partie = fopen("save.txt", "r");

    if (nv_partie == NULL) {
        printf("Fichier invalide");
        return 0;
    }


    fscanf(nv_partie, "Joueur actuel: %d\n", &partie->joueur_actuel);
    fscanf(nv_partie, "Nombre de joueurs: %d\n", &partie->nb_joueurs);

    for (int i = 0; i < partie->nb_joueurs; i++) {
        fscanf(nv_partie, "Pion %d: x: %d; y: %d\n", &i, &partie->position_pion[i].x, &partie->position_pion[i].y);
    }

    int ipm = 0;
    while (fscanf(nv_partie, "Mur %d: x: %d; y: %d; type: %c\n", &ipm, &partie->position_murs[ipm].x, &partie->position_murs[ipm].y, &partie->position_murs[ipm].type) == 4) {
        if (partie->position_murs[ipm].x >= 0 && partie->position_murs[ipm].y >= 0) {
            ipm++;
            if (ipm >= 30) break; // Limiter à 30 murs
        }
    }

    for (int i = 0; i < partie->nb_joueurs; i++) {
        fscanf(nv_partie, "Joueur: %d; Barrières restantes: %d\n", &i, &partie->donnees[i].remainingBarriers);
    }

    fclose(nv_partie);
    return 1;
}




