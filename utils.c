
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