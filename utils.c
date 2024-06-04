
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typeOf mod(typeOf n, int premier) {

    /*while (!(0 <= n && n < premier)) {

        if (n > 0) {
            n -= premier;
        } else n += premier;

    }*/

    n = n % premier;
    if (n < 0) return n + premier;
    else return n;

}

typeOf toPower(typeOf value, int powerOf, int premier) {

    return mod((typeOf)pow((double)value, (double)powerOf), premier);
}

typeOf pPow(typeOf value, int powerOf, int premier) {

    if (powerOf * log(value) > log(INT_MAX)) return protectedPow(value, powerOf, premier);
    else return toPower(value, powerOf, premier);

}

typeOf protectedPow(typeOf value, int toPower, int premier) {

    int res = 1;

    for (int i = 0; i < toPower; i++) {
        res = mod(res * value, premier);
    };

    return res;
}

typeOf applicationPol(typeOf* pol, int size, int value, int premier) {
    typeOf sum = 0;

    //printf("-size : %d-", size);

    for (int i = 1; i < size + 1; i++) {
        if ((size - i) * log(value) > log(INT_MAX)) sum = mod(sum + pol[i - 1] *  protectedPow(value, size - i, premier), premier);
        else sum = mod(sum + pol[i - 1] * (int)pow((double)value, (double)(size - i)), premier);
        //printf("-%d %d-", i, (int)pow((double)value, (double)(size - i)) );
    }

    return sum;
}

void putAtTheEnd(typeOf (**a), int nb_row, int nb_column, int line) {

    for (int i = 0; i < nb_column; i++) {
        int save = a[line][i];

        for (int j = line + 1; j < nb_row - 1; j++) {
            a[j][i] = a[j + 1][i];
        };

        a[nb_row - 1][i] = save;

    }

    return;

}

int findFirstNonNull(typeOf* array, int size) {

    for (int i = 0; i < size; i++) {
        if (array[i] != 0) return i;
    }

    printf("\n-1\n");

    return -1;
}

int findLastNonNullRow(typeOf(**matrice), int nb_row, int nb_column) {

    for (int i = nb_row - 1; i >= 0; i--) {

        if (vide(matrice[i], nb_column) == 0) return i;

    };

    printf("\nNo non empty row in the matrice\n");
    printMat(matrice, nb_row, nb_column);

    return -1;

}

// Will switch line a and b
void switchLine(typeOf(**matrice), int nb_row, int nb_column, int a, int b) {

    typeOf save;

    for (int i = 0; i < nb_column; i++) {
        save = matrice[a][i];
        matrice[a][i] = matrice[b][i];
        matrice[b][i] = save;
    }

    return;
}

int invMod(typeOf n, int premier) {

    int inv = 1;

    while (mod(n * inv, premier) != 1) {
        inv += 1;
    };

    return inv;

}

int nbVide(typeOf(**a), int nb_row, int nb_column) {
    int sum = 0;

    for (int i = 0; i < nb_row; i++) sum += vide(a[i], nb_column);

    return sum;
}

int vide(typeOf* array, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] != 0) return 0;
    };

    return 1;
}

void printMatrice(int a[ROW][COLUMN], int nb_row, int nb_column) {

    printf("-------------------------------------------\n");

    for (int i = 0; i < nb_row; i++) {
        for (int j = 0; j < nb_column; j++)
        {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    };

    printf("-------------------------------------------\n");

    return;
}

void printMat(typeOf(**a), int nb_row, int nb_column) {

    printf("-------------------------------------------\n");

    for (int i = 0; i < nb_row; i++) {
        for (int j = 0; j < nb_column; j++)
        {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    };

    printf("-------------------------------------------\n");

    return;

}

void printArray(int* array, int size) {

    printf("-------------------------------------------\n[\t");    

    for (int i = 0; i < size; i++) {
        printf("%d \t", array[i]);
    }

    printf("]\n-------------------------------------------\n");
}

void printResult(int(*mat), int size) {

    for (int i = 0; i < size; i++) {

        if (mat[i] == 1) switch (size - i - 1) {
        case 1:
            printf("x");
            break;

        case 0:
            printf("1");
            break;

        default:
            printf("x^%d", size - i - 1);
            break;
        }
        else switch (size - i - 1) {
        case 1:
            printf("%dx", mat[i]);
            break;

        case 0:
            printf("%d", mat[i]);
            break;

        default:
            printf("%dx^%d", mat[i], size - i - 1);
            break;
        }


        if (i + 1 != size) printf(" + ");
    };
}