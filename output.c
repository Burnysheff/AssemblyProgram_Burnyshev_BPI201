//------------------------------------------------------------------------------
// output.c - единица компиляции, вбирающая в себя все функции вывода данных
//------------------------------------------------------------------------------

#include <stdio.h>

#include "exdata.h"

// Вычисление среднего значения квадратной матрицы
int AverageSquare(void *r);
// Вычисление среднего значения треугольника
int AverageTriangle(void *r);
// Вычисление среднего значения треугольника
int AverageDiagonal(void *r);

// Вывод квадратной матрицы
void OutSquare(void *r, FILE *ofst) {
    fprintf(ofst, "This is square matrix");
    int size = *((int*)r);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fprintf(ofst, "%d ", *((int *) r + i * intSize));
        }
        fprintf(ofst, "\n");
    }
    fprintf(ofst, "\nThe average is: %d", AverageSquare(r));
}

// Вывод треугольной матрицы
void OutTriangle(void *r, FILE *ofst) {
    fprintf(ofst, "This is square matrix");
    int size = *((int*)r);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fprintf(ofst, "%d ", *((int *) r + i * intSize));
        }
        fprintf(ofst, "\n");
    }
    fprintf(ofst, "\nThe average is: %d", AverageTriangle(r));
}

// Вывод диагональной матрицы
void OutDiagonal(void *r, FILE *ofst) {
    fprintf(ofst, "This is square matrix");
    int size = *((int*)r);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fprintf(ofst, "%d ", *((int *) r + i * intSize));
        }
        fprintf(ofst, "\n");
    }
    fprintf(ofst, "\nThe average is: %d", AverageDiagonal(r));
}

// Вывод параметров текущей матрицы
void OutShape(void *s, FILE *ofst) {
    // Получаем ключ матрицы
    int key = *((int*)s);
    if(key == Square) {
        OutSquare(s+intSize, ofst);
    }
    else if(key == Triangle) {
        // Для треугольной умножение на 2, так как там еще есть шаг заполнения
        OutTriangle(s+intSize * 2, ofst);
    }
    else {
        if(key == Diagonal) {
            OutDiagonal(s+intSize, ofst);
        } else {
            fprintf(ofst, "Incorrect figure!\n");
        }
    }
}

// Вывод содержимого контейнера в файл
void OutContainer(void *c, int len, FILE *ofst) {
    void *tmp = c;
    fprintf(ofst, "There is %d element in container: \n", len);
    for(int i = 0; i < len; i++) {
        fprintf(ofst, "%d: ", i);
        OutShape(tmp, ofst);
        tmp = tmp + max_shapeSize;
    }
}
