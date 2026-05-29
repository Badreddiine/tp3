#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

// Données à sauvegarder
char donnees[] = "Données importantes à sauvegarder\n";

void gestionnaire_sigint(int sig) {
    printf("\nSignal SIGINT reçu ! Sauvegarde en cours...\n");
    
    // Ouvre/crée le fichier (remplace s'il existe)
    FILE *fichier = fopen("sauvegarde.txt", "w");
    if (fichier == NULL) {
        perror("Erreur ouverture fichier");
        exit(EXIT_FAILURE);
    }
    
    fprintf(fichier, "%s", donnees);
    fclose(fichier);
    
    printf("Données sauvegardées dans sauvegarde.txt\n");
    exit(0);
}

int main(void) {
    // Modifier le comportement de SIGINT
    signal(SIGINT, gestionnaire_sigint);
    
    printf("Programme en cours... Appuyez Ctrl+C pour sauvegarder et quitter.\n");
    
    // Boucle infinie qui attend le signal
    while (1) {
        pause();
    }
    
    return 0;
}
