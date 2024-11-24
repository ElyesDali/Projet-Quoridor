
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JOUEURS 4
#define MAX_NOM 50
#define nbJoueurs 4

// Structure pour représenter un joueur
typedef struct {
    char nom[MAX_NOM];
    int classement;
    int victoires;
    int nbpartiesjouees;
} Player;


// Fonction pour initialiser les statistiques des joueurs
void initialiserClassement(Player players[], int nb_joueurs) {
    for (int i = 0; i < nb_joueurs; i++) {
        players[i].classement = i + 1;
        players[i].victoires = 0;
        players[i].nbpartiesjouees = 0;
    }
}

// Fonction pour mettre à jour les statistiques d'un joueur après une victoire
void miseAJourJoueur(Player players[], int nb_joueurs, int gagnant) {
    for (int i = 0; i < nb_joueurs; i++) {
        players[i].nom[strcspn(players[i].nom, "\n")] = '\0'; // Enlever le '\n' après fgets
    }
    players[gagnant].victoires++; // Incrémentation des victoires du gagnant
    for (int i = 0; i < nb_joueurs; i++) {
        players[i].nbpartiesjouees++; // Incrémentation des parties jouées pour tous les joueurs
    }
}

// Fonction pour trier les joueurs par nombre de victoires
void trierClassement(Player players[], int nb_joueurs) {
    for (int i = 0; i < nb_joueurs - 1; i++) {
        for (int j = 0; j < nb_joueurs - i - 1; j++) {
            if (players[j].victoires < players[j + 1].victoires) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
    // Mise à jour des classements
    for (int i = 0; i < nb_joueurs; i++) {
        players[i].classement = i + 1;
    }
}

// Fonction pour afficher le classement des joueurs
void afficherClassement(Player players[], int nb_joueurs) {
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║           CLASSEMENT FINAL            ║\n");
    printf("╠══════╦════════════════════╦═══════════╦════════════════╣\n");
    printf("║ Rang │ Nom                │ Victoires │ Parties jouées ║\n");
    printf("╠══════╬════════════════════╬═══════════╬════════════════╣\n");
    for (int i = 0; i < nb_joueurs; i++) {
        printf("║ %-4d │ %-18s │ %-9d │ %-14d ║\n", i + 1, players[i].nom, players[i].victoires, players[i].nbpartiesjouees);
    }
    printf("╚════════════════════════════════════════════════════════╝\n");
}

// Fonction pour sauvegarder les données dans un fichier
void sauvegarderDonnees(Player players[], int nb_joueurs) {
    FILE *fichier = fopen("leaderboard.txt", "w");
    for (int i = 0; i < nb_joueurs; i++) {
        fprintf(fichier, "%s %d %d\n", players[i].nom, players[i].victoires, players[i].nbpartiesjouees);
    }
    fclose(fichier);
}
    printf("\n");
}
void leaderboard();
initialiserClassement(Player players[], int nb_joueurs)
for (int i = 0; i < nb_joueurs; i++) {
        if (victoire(PlayerX[i], PlayerY[i], i + 1)) {
            miseAJourJoueur(players, nb_joueurs, i); // Mise à jour des statistiques
            trierClassement(players, nb_joueurs);    // Trier les joueurs
            afficherClassement(players, nb_joueurs); // Afficher le classement
            sauvegarderDonnees(players, nb_joueurs); // Sauvegarder les données
            return; // Quitter dès qu'un gagnant est trouvé
        }
    }
