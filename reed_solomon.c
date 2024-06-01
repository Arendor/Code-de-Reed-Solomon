// reed_solomon.c : définit le point d'entrée de l'application.
//

#include <stdio.h>
#include <stdlib.h>
#include "reed_solomon.h"
#include "utils.h"
#include "lagrange.h"


int main(int argc, const char* argv[]) {


    //lagrange_pols();

    /*
    * How many numbers in the code
    * Inputing the number
    * Modulo which number
    * How many symbols of error correcting
    * 
    * interpolation de lagrange
    * 
    * Result of the computing
    * 
    * Now error
    * 
    * Doing the calculation for n error, n - 1 error etc.
    * Showing the result 
    */

    return 0;
    const int nb_row = ROW;
    const int nb_colum = COLUMN;

     /*
     * 
     * // Dynamic Def
     int** a = (int**) calloc(nb_row, nb_colum * sizeof(int));

     for (int b = 0; b < nb_row; b++) {
        a[b] = (int*) calloc(nb_colum, sizeof(int));
     };
    
     for (int b = 0; b < nb_row; b++) {

         for (int c = 0; c < nb_colum; c++) {
             a[b][c] = rand();
         }

         printf("\n");
     }

     printMat(a, nb_row, nb_colum);

     for (int b = 0; b < nb_row; b++) {
         free(a[b]);
      };

     free(a);*/
    //return 0;

    int i, j, k, n;
	int premier = 11;
	
	int augmented_matrice[ROW][COLUMN] = {
		{1, 1, 1, 1, 1, 7, 7, 7},
        {5,8,4,2,1,5,8,10},
        {4,5,9,3,1,0,0,0},
        {3,9,5,4,1,8,2,10},
        {9,4,3,5,1,5,1,3},
        {9,7,3,6,1,5,10,8},
        {3,2,5,7,1,5,7,2}
    }, x[ROW]={ NULL };

    // We suppose the matrix is (without the +1 line for the result) a square matrix

    // Going through all the row of the matrix
    for (i = 0; i < nb_row /* taille en ligne*/; i++) {

        // If the first is 0, that means is dont have any inverse mod so no calculations
        if (augmented_matrice[i][i] != 0) {
            int multiplier = invMod(augmented_matrice[i][i], premier);

            // Updating the line
            for (j = i; j < nb_colum /* taille en colonne + 1 (matrice augmenté) */; j++) {
                augmented_matrice[i][j] = mod(augmented_matrice[i][j] * multiplier, premier);
            };

            // Doing the calculations for the line belows
            for (j = i + 1; j < nb_row/* taille des lignes */; j++) {
                int coef = augmented_matrice[j][i];

                // For each column
                for (k = i; k < nb_colum /* taille en colonne + 1 (matrice augmenté) */; k++) {
                    augmented_matrice[j][k] = mod(augmented_matrice[j][k] - coef * augmented_matrice[i][k], premier);
                }
            }
        }

        printMatrice(augmented_matrice, nb_row, nb_colum);

        //printf("ligne %d \n", i + 1);

    };

    for (i = nb_row - 2; i >= 0; i--) {
        for (j = i + 1; j < nb_colum - 1; j++) {
            int coef = augmented_matrice[i][j];
            augmented_matrice[i][j] = mod(augmented_matrice[i][j] - coef * augmented_matrice[j][j], premier); // 0;
            augmented_matrice[i][nb_colum - 1] = mod(augmented_matrice[i][nb_colum - 1] - coef * augmented_matrice[j][nb_colum - 1], premier);
        };

    };

    printMatrice(augmented_matrice, nb_row, nb_colum);

    // Doing the synthetic division

    // Number of errors is not always the same(dynamic value)
    int nb_errors = 2;
    int original_size = 3; // nb_row - 2 * nb_errors

    // Pol are defined from the highest degree to the lowest degree
    typeOf* AllPol = calloc(nb_row - nb_errors, sizeof(typeOf));
    typeOf* ErrPol = calloc(nb_errors + 1, sizeof(typeOf));
    typeOf* GenPol = calloc(original_size, sizeof(typeOf));

    // Initialize the Q(x) function

    for (i = 0; i < nb_row - nb_errors; i++) {
        AllPol[i] = augmented_matrice[i][nb_colum - 1];
    };

    // Error function : coefficient of the highest degree is always one, as E(x)=(x-e1)(x-e2)...(x-en)

    ErrPol[0] = 1;

    // Initialize the Error function
    for (i = 0; i < nb_errors; i++) {
        ErrPol[i + 1] = augmented_matrice[i + nb_row - nb_errors][nb_colum - 1];
    };

    //

    for (i = 0; i < nb_row - 2 * nb_errors; i++) {

        // Set the coef of the result as the coef corresponding
        GenPol[i] = AllPol[i];

        // Doing the calculations on the next coef of degree impacted
        for (j = 1; j < nb_errors + 1; j++) {
            AllPol[i + j] = mod(AllPol[i + j] - ErrPol[i + j] * AllPol[i], premier);
        }

        // The pol in the fraction is now a degree less
        AllPol[i] = 0;

    };

    // The one who are left are supposed to be mod k, hence no calculations needed

    printResult(GenPol, original_size);

    // Free all the dynamic arrays 
    free(AllPol);
    free(ErrPol);
    free(GenPol);


    //x[5] /* taille ligne dernier */ = augmented_matrice[5][6];

    /*for (i = 5 - 1; i >= 1; i--) {


        for (j = i; j < 6; j++) {
            int coef = augmented_matrice[i][j];
        }

        sum = 0;
        for (j = i + 1; j <= n; j++)
        {
            sum = sum + A[i][j] * x[j];
        }
        x[i] = (A[i][n + 1] - sum) / A[i][i];
    }*/



    //for (j = 1; j <= n; j++) /* loop for the generation of upper triangular matrix*/
    /* {
        for (i = 1; i <= n; i++)
        {
            if (i > j)
            {
                c = augmented_matrice[i][j] / augmented_matrice[j][j];
                for (k = 1; k <= n + 1; k++)
                {
                    A[i][k] = A[i][k] - c * A[j][k];
                }
            }
        }
    }
    x[n] = A[n][n + 1] / A[n][n];
    /* this loop is for backward substitution*/
    /*for (i = n - 1; i >= 1; i--)
    {
        sum = 0;
        for (j = i + 1; j <= n; j++)
        {
            sum = sum + A[i][j] * x[j];
        }
        x[i] = (A[i][n + 1] - sum) / A[i][i];
    }
    printf("\nThe solution is: \n");
    for (i = 1; i <= n; i++)
    {
        printf("\nx%d=%f\t", i, x[i]); /* x1, x2, x3 are the required solutions*/
    //}



	/*printf("%zd \n", sizeof(x));

	for (int i = 0; i < sizeof(x)/sizeof(x[0]); i++) {
		printf("%d", x[i]);
	};*/

	return 0;
}
