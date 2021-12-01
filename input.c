#include <stdio.h>

#include "exdata.h"

// Ввод параметров прямоугольника из файла
void InSquare(void *r, FILE *ifst) {
    // Ввод размера матрицы
    fscanf(ifst, "%d", (int*)r);
    // Ключ элемента
    int key = 0;
    for (int i = 0; i < *(int*)r; ++i) {
        for (int j = 0; j < *(int*)r; j++) {
            ++key;
            fscanf(ifst, "%d", (int*)r + key * intSize);
        }
    }
}

// Ввод параметров треугольной матрицы из файла
void InTriangle(void *r, FILE *ifst) {
    // Ввод размера матрицы и шага
    fscanf(ifst, "%d%d", (int*)r, (int*)(r + intSize));
    // Шаг, с помощью которого заполняем элементы ниже диагонали
    int step = *(int*)(r + intSize);
    // Ключ элемента
    int key = 0;
    for (int i = 0; i < *(int*)r; ++i) {
        for (int j = 0; j < *(int*)r; j++) {
            ++key;
            if (i == j) {
                fscanf(ifst, "%d", ((int*)r + key * intSize));
            } else {
                if (j > i) {
                    *((int*)r + key * intSize) = 0;
                } else {
                    *((int*)r + key * intSize) = *((int*)r + key * intSize - 1) + step * key;
                }
            }
        }
    }
}

// Ввод параметров диагональной матрицы из файла
void InDiagonal(void *r, FILE *ifst) {
    // Ввод размера матрицы
    fscanf(ifst, "%d", (int*)r);
    // Ключ элемента
    int key = 0;
    for (int i = 0; i < *(int*)r; ++i) {
        for (int j = 0; j < *(int*)r; j++) {
            ++key;
            if (i == j) {
                fscanf(ifst, "%d", (int*)r + key * intSize);
            } else {
                *((int*)r + key * intSize) = 0;
            }
        }
    }
}

// Ввод параметров матрицы из файла
int InShape(void *s, FILE *ifst) {
    // Условный ключ матрицы
    int k;
    fscanf(ifst, "%d", &k);
    switch(k) {
        case 1:
            *((int*)s) = Square;
            InSquare(s+intSize, ifst);
            return 1;
        case 2:
            *((int*)s) = Triangle;
            InTriangle(s+intSize, ifst);
            return 1;
        case 3:
            *((int*)s) = Diagonal;
            InDiagonal(s+intSize, ifst);
            return 1;
        default:
            return 0;
    }
}

// Ввод содержимого контейнера из указанного файла
void InContainer(void *c, int *len, FILE *ifst) {
    void *tmp = c;
    while(!feof(ifst)) {
        if(InShape(tmp, ifst)) {
            // Увеличиваем на максимальное место матрицы
            tmp = tmp + max_shapeSize;
            (*len)++;
        }
    }
}
