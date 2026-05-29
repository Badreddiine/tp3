#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int p1[2], p2[2];  // p1: père→fils, p2: fils→père
    pid_t pid;
    int entiers[5] = {1, 2, 3, 4, 5};
    int valeur, double_val;

    // Créer les deux tubes
    if (pipe(p1) != 0 || pipe(p2) != 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // ===== FILS =====
        close(p1[1]);  // Fils : ferme écriture p1
        close(p2[0]);  // Fils : ferme lecture p2

        for (int i = 0; i < 5; i++) {
            // Lire entier depuis p1
            read(p1[0], &valeur, sizeof(int));
            printf("Fils reçoit : %d\n", valeur);

            // Calculer le double et envoyer via p2
            double_val = valeur * 2;
            write(p2[1], &double_val, sizeof(int));
        }

        close(p1[0]);
        close(p2[1]);
        exit(0);

    } else {
        // ===== PÈRE =====
        close(p1[0]);  // Père : ferme lecture p1
        close(p2[1]);  // Père : ferme écriture p2

        for (int i = 0; i < 5; i++) {
            // Envoyer entier via p1
            printf("Père envoie : %d\n", entiers[i]);
            write(p1[1], &entiers[i], sizeof(int));

            // Lire le double depuis p2
            read(p2[0], &double_val, sizeof(int));
            printf("Père reçoit le double : %d\n", double_val);
        }

        close(p1[1]);
        close(p2[0]);
    }

    return 0;
}
