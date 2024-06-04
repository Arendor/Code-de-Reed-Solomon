

#ifndef utils

#define ROW 7
#define COLUMN 8 //6
#define typeOf int

int mod(typeOf n, int premier);

typeOf toPower(typeOf value, int toPower, int premier);
typeOf protectedPow(typeOf value, int toPower, int premier);
typeOf pPow(typeOf value, int powerOf, int premier);

typeOf applicationPol(typeOf* pol, int size, int value, int premier);
void switchLine(typeOf(**matrice), int nb_row, int nb_column, int a, int b);
int findLastNonNullRow(typeOf(**matrice), int nb_row, int nb_column);
int findFirstNonNull(typeOf* array, int size);

void putAtTheEnd(typeOf(**a), int nb_row, int nb_column, int line);

int invMod(typeOf n, int premier);
int vide(typeOf* array, int size);
int nbVide(typeOf(**a), int nb_row, int nb_column);
void printArray(int* array, int size);

void printMatrice(int a[ROW][COLUMN], int nb_row, int nb_column);
void printMat(typeOf(**a), int nb_row, int nb_column);

void printResult(int(*mat), int size);

#endif // !utils
