#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int tube[2];
    char *buffer = "AZERTYUIOP";

    fprintf(stdout, "Création tube \n");
    if (pipe(tube) != 0) {        // Crée un tube
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Fermeture sortie \n");
    close(tube[0]);               // Ferme le côté LECTURE du tube

    fprintf(stdout, "Écriture dans tube \n");
    if (write(tube[1], buffer, strlen(buffer)) != strlen(buffer)) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Fin du programme \n");
    return EXIT_SUCCESS;
}
