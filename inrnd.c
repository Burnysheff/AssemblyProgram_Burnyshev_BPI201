#include <stdlib.h>

#include "exdata.h"

// rnd.c - содержит генератор случайных чисел в диапазоне от 1 до 20
int Random() {
    return rand() % 20 + 1;
}

// Случайный ввод квадратной матрицы
void InRndSquare(void *r) {
    // Первый символ - размер матрицы
    int size = Random();
    *((int*)r) = size;
    // Ключ элемента
    int key = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            ++key;
            *((int*)r + key * intSize) = Random();
        }
    }
}

// Случайный ввод треугольной матрицы
void InRndTriangle(void *r) {
    // Первый символ - размер матрицы
    int size = Random();
    *((int*)r) = size;
    // Второй символ - шаг матрицы
    int step = Random();
    *((int*)r + intSize) = step;
    // Ключ элемента (2 элемента уже занято)
    int key = 1;
    for (int i = 0; i < *(int*)r; ++i) {
        for (int j = 0; j < *(int*)r; j++) {
            ++key;
            if (i == j) {
                *(int*)(r + key * intSize) = Random();
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

// Случайный ввод диагональной матрицы
void InRndDiagonal(void *r) {
    // Первый символ - размер матрицы
    int size = Random();
    *((int*)r) = size;
    // Ключ элемента
    int key = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            ++key;
            if (i == j) {
                *((int *) r + key * intSize) = Random();
            } else {
                *((int *) r + key * intSize) = 0;
            }
        }
    }
}

// Автоматическая генерация матрицы
int InRndShape(void *s) {
    // Рандомный ключ матрицы
    int k = rand() % 3 + 1;
    switch(k) {
        case 1:
            *((int*)s) = Square;
            InRndSquare(s+intSize);
            return 1;
        case 2:
            *((int*)s) = Triangle;
            InRndTriangle(s+intSize);
            return 1;
        case 3:
            *((int*)s) = Diagonal;
            InRndDiagonal(s+intSize);
            return 1;
        default:
            return 0;
    }
}

// Случайный ввод содержимого контейнера
void InRndContainer(void *c, int *len, int size) {
    void *tmp = c;
    while(*len < size) {
        if(InRndShape(tmp)) {
            tmp = tmp + max_shapeSize;
            (*len)++;
        }
    }
}
