#include <stdio.h>
#include <stdlib.h> // для функций rand() и srand()
#include <time.h>   // для функции time()
#include <string.h>

#include "data.h"

//------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    // Контейнер матриц
    unsigned char cont[maxSize];
    // Длина контейнера
    int len = 0;


    // Проверки аргументов командной строки
    if (argc != 5) {
        printf("incorrect command line!\n");
        return 1;
    }

    printf("Start\n");

    // Ввод из файла
    if(!strcmp(argv[1], "file")) {
        FILE* ifst = fopen(argv[2], "r");
        InContainer(cont, &len, ifst);
    }
    // Автоматическая генерация
    else if(!strcmp(argv[1], "auto")) {
        int size = atoi(argv[2]);
        if((size < 1) || (size > 10000)) {
            printf("incorrect number of figures!");
            return 3;
        }
        // Системные часы
        srand((unsigned int)(time(0)));
        // Случайное заполнение
        InRndContainer(cont, &len, size);
    }
    else {
        printf("incorrect qualifier value!");
        return 2;
    }

    // Запуск часов
    clock_t start = clock();
    // Выводим матрицы из контейнера
    FILE* ofst1 = fopen(argv[3], "w");
    fprintf(ofst1, "Filled container:\n");
    OutContainer(cont, len, ofst1);
    fclose(ofst1);

    // Сортируем матрицы и выводим их (еще считаем общее среднее)
    FILE* ofst2 = fopen(argv[4], "w");
    // Общее среднее
    double sum = AverageAll(cont, len);
    // Сортировка
    BubbleSort(cont, len);
    OutContainer(cont, len, ofst2);
    // Конец работы часов
    clock_t end = clock();
    // Результат работы часов
    double calcTime = ((double)(end - start)) / (CLOCKS_PER_SEC + 1.0);

    fprintf(stdout, "Calculaton time = %g\n", calcTime);
    fclose(ofst2);

    // Конец программы
    printf("Stop\n");
    return 0;
}
