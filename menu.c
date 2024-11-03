#include <stdio.h>

int menu() {
    int choix = 0;

    while (1) {
        printf("\nQUORIDOR\n");
        printf("\n");
        printf("1 : Jouer\n");
        printf("2 : Reprendre une partie\n");
        printf("3 : Aide\n");
        printf("4 : Tableau des scores\n");
        printf("5 : Quitter\n");
        printf("\nChoix : ");

        scanf("%d", &choix);

        if (choix == 1) {
            printf("\nCHOISIR LE MODE DE JEU\n");
            printf("\n1 : Normal\n");
            printf("2 : Blitz\n");
            printf("3 : Retour \n");
            printf("\nChoix : ");
            scanf("%d", &choix);

            if (choix == 1) {
                printf("Mode Normal sélectionné.\n");
            }
            else if (choix == 2) {
                printf("Mode Blitz sélectionné.\n");
            }
            else if (choix == 3) {
                continue;
            }
            else {
                printf("Choix invalide.\n");
            }
        }
        else if (choix == 2) {
            printf("1 : Reprendre une partie.\n");
            printf(" 2 : Retour\n");
            printf("\nChoix : ");
            scanf("%d", &choix);
            if (choix == 1) {
                printf("Reprendre une partie.\n");
            }
            else if (choix == 2) {
                continue;
            }
            else {
                printf("Choix invalide.\n");
            }
        }
        else if (choix == 3) {
            printf("1 : Règles à mettre après.\n");
            printf(" 2 : Retour\n");
            printf("\nChoix : ");
            scanf("%d", &choix);
            if (choix == 1) {
                printf("Règles à mettre après.\n");
            }
            else if (choix == 2) {
                continue;
            }
            else {
                printf("Choix invalide.\n");
            }
        }
        else if (choix == 4) {
            printf("1 : Tableau des scores.\n");
            printf(" 2 : Retour\n");
            printf("\nChoix : ");
            scanf("%d", &choix);
            if (choix == 1) {
                printf("Tableau des scores.\n");
            }
            else if (choix == 2) {
                continue;
            }
            else {
                printf("Choix invalide.\n");
            }
        }
        else if (choix == 5) {
            printf("Quitter le jeu.\n");
            return 0;
        }
        else {
            printf("Choix invalide.\n");
        }
    }

    return 0;
}

int main() {
    menu();
}
