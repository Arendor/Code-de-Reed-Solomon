

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "decode.h"
#include "reed_solomon.h"

int** solve(typeOf(**augmented_matrice), int nb_row, int nb_column, int premier) {

	int i, j, k, modifier = 0, adjusted_column = 0;

    for (i = 0; i < nb_row /* taille en ligne*/; i++) {

        adjusted_column = i + modifier;

        // If the first is 0, that means is dont have any inverse mod so no calculations
        if (i + 1 < nb_column && augmented_matrice[i][adjusted_column] != 0) {
            int multiplier = invMod(augmented_matrice[i][adjusted_column], premier);

            // Updating the line
            for (j = adjusted_column; j < nb_column /* taille en colonne + 1 (matrice augmenté) */; j++) {
                augmented_matrice[i][j] = mod(augmented_matrice[i][j] * multiplier, premier);
            };

            // Doing the calculations for the line belows
            for (j = i + 1; j < nb_row/* taille des lignes */; j++) {
                int coef = augmented_matrice[j][adjusted_column];

                // For each column
                for (k = adjusted_column; k < nb_column /* taille en colonne + 1 (matrice augmenté) */; k++) {
                    augmented_matrice[j][k] = mod(augmented_matrice[j][k] - coef * augmented_matrice[i][k], premier);
                }
            }
        }
        else {
            modifier -= 1;
        }

        printMat(augmented_matrice, nb_row, nb_column);

    };

    return augmented_matrice;

}

int decode_funct() {



}