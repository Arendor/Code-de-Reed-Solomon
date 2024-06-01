

#include <stdio.h>
#include <stdlib.h>
#include "lagrange.h"
#include "utils.h"


int lagrange_pols() {

	int i, j, k, nb, premier = 0, error_symbols;
	printf("Combien de valeurs ? : ");
	scanf("%d", &nb);
	
	int* numbers = malloc(nb * sizeof(int));

	for (i = 0; i < nb; i++) {
		printf("number[%d] : ", i + 1);
		scanf("%d", &numbers[i]);
		//printf("\n");
	};

	while (!(premier > 0 && premier > nb)) {
		printf("Modulo k : ");
		scanf("%d", &premier);
		//printf("\n");
	};

	printf("Combien d'erreur à corriger ? : ");
	scanf("%d", &error_symbols);
	printf("\n");
	printf("--------------------------------------\n\n");

	error_symbols *= 2;


	int** LagPols = malloc(nb * nb * sizeof(int));
	int* up = calloc(nb, sizeof(int));
	int* interPol = calloc(nb, sizeof(int));


	// Iterate throug all the lagrange pols
	for (i = 0; i < nb; i++) {
		LagPols[i] = (int*)calloc(nb, sizeof(int));
		//LagPols[i][nb - 1] = 1;
		//LagPols[i][nb - 2] = 1;
		int sum = 1;

		// Calculate the value necessary for the inverse of the matrix
		for (j = 0; j < nb; j++) {
			if (i != j) {
				sum = mod((i - j) * sum, premier);
			}
		}

		// This value

		//printf("Somme : %d", sum);

		int value = mod(invMod(sum, premier) * numbers[i], premier);

		//printf("A : %d\n", value);

		for (j = 1; j < nb +1; j++) {
			
			if (i + 1 != j) {

				
				// Creating an upper matrix with everything being augmented of one

				for (k = 0; k < nb - 1; k++) {

					up[k] = LagPols[i][k + 1];
					
				}

				up[nb - 1] = 0;

				//printArray(up, nb);

				// Computing the calculations

				// For the first one, it must be non 0
				// There may be a faster way to go
				if (vide(LagPols[i], nb)) {
					LagPols[i][nb - 1] = -j;
					LagPols[i][nb - 2] = 1;
				} else for (k = 0; k < nb; k++) {

					// Making the multiplication of two polynomials, one being a linear of the form x - a

					LagPols[i][k] = mod((up[k] - j * LagPols[i][k]), premier);
				};

				//printArray(LagPols[i], nb);
				
			}
		}

		// Multipling all with our inv found to get the value at the special index i + 1
		for (j = 0; j < nb; j++) {
			LagPols[i][j] = mod(LagPols[i][j] * value, premier);
		};

	};

	//printMat(LagPols, nb, nb);
	
	for (i = 0; i < nb; i++) {
		for (j = 0; j < nb; j++) {
			interPol[i] = interPol[i] + LagPols[j][i];
		};

		// This can have before the modulo, a maximum size of (premier - 1) * nb, which could be huge
		interPol[i] = mod(interPol[i], premier);
	}

	printResult(interPol, nb);

	printf("\nValeurs a renvoyer : ");

	for (i = 0; i < nb; i++) {
		printf("%d ", numbers[i]);;
	};

	for (i = 1; i < error_symbols + 1; i++) {
		printf("%d ", applicationPol(interPol, nb, nb + i, premier));
	};

	/*printf("\n");

	for (i = 1; i < nb + error_symbols + 1; i++) {
		printf("%d ", applicationPol(interPol, nb, i, premier));
	}*/

	for (i = 0; i < nb; i++) free(LagPols[i]);
	free(up);
	free(numbers);
	free(LagPols);
	free(interPol);

	return 0;
}