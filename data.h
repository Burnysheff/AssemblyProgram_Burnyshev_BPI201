#ifndef __data__
#define __data__

// Описание констант

// Константа, определяющая размер целого числа
int const intSize = sizeof(int);
// Константа, задающая размер для матрицы
int const max_shapeSize = 2 * intSize + (400 * intSize);
// Константа, определяющая размерность массива матриц
int const maxSize = 10000 * max_shapeSize;
// Константа, задающая признак квадратной матрицы
int const Square = 1;
// Константа, задающая признак треугольной матрицы
int const Triangle = 2;
// Константа, задающая признак диагональной матрицы
int const Diagonal = 3;

// Используемые функции

// Ввод содержимого контейнера из указанного файла
void InContainer(void *c, int *len, FILE *ifst);
// Случайный ввод содержимого контейнера
void InRndContainer(void *c, int *len, int size);
// Вывод содержимого контейнера в файл
void OutContainer(void *c, int len, FILE *ofst);
// Вычисление общего среднего арифметического матриц
extern double AverageAll(void *c, int len);
// Сортировка матриц пузырьком по среднему арифметическому
void BubbleSort(void *c, int len);

#endif
