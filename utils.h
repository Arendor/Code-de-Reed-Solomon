

#ifndef utils

#define ROW 7
#define COLUMN 8
#define typeOf int

int mod(typeOf n, int premier);

typeOf toPower(typeOf value, int toPower, int premier);
typeOf protectedPow(typeOf value, int toPower, int premier);
typeOf applicationPol(typeOf* pol, int size, int value, int premier);


int invMod(typeOf n, int premier);
int vide(typeOf* array, int size);
void printArray(int* array, int size);

void printMatrice(int a[ROW][COLUMN], int nb_row, int nb_column);
void printMat(typeOf(**a), int nb_row, int nb_column);

void printResult(int(*mat), int size);

#endif // !utils
