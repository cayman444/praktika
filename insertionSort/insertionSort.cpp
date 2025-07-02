#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort_array(int* parg, int size)
{
    for (int i = 1; i < size; i++)
    {
        int a = parg[i];
        int j = i - 1;

        while (j >= 0 && parg[j] > a)
        {
            parg[j + 1] = parg[j];
            j--;
        }
        parg[j + 1] = a;
    }
}

void generate_random_file(char* fileName, int min, int max, int size) {
    FILE* file = fopen(fileName, "w");

    if (file == NULL)
        return;

    srand(time(0));

    fprintf(file, "%d ", size);

    int range = max - min + 1;

    for (int i = 0; i < size; i++) {
        int number = rand() % range + min;
        fprintf(file, "%d ", number);
    }

    fclose(file);
}

int* read_array_from_file(char* fileName, int& size) {
    FILE* file = fopen(fileName, "r");

    if (file == NULL)
        return nullptr;


    fscanf(file, "%d", &size);
    int* array = new int[size];

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &array[i]);
    }

    fclose(file);
    return array;
}

void print_array(int* array, int size) {
    printf("Массив: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void print_menu() {
    printf("\nМеню:\n");
    printf("1. Ручной ввод массива\n");
    printf("2. Чтение массива из файла\n");
    printf("3. Генерация файла со случайными числами\n");
    printf("4. Выход\n");
    printf("Выберите вариант: ");
}


int* input_array_manually(int& size)
{
    printf("\nРучной ввод массива.\nВведите размер: ");
    scanf("%d", &size);

    int* arr = new int[size];

    if (arr == nullptr)
        return nullptr;

    for (int i = 0; i < size; i++)
    {
        printf("Элемент[%d]: ", i);
        scanf("%d", &arr[i]);
        printf("\n");
    }

    return arr;
}

void handle_manual_input() {
    int size;
    int* array = input_array_manually(size);
    if (array == NULL) {
        printf("Ошибка при вводе массива\n");
        return;
    }

    printf("Исходный ");
    print_array(array, size);

    clock_t start = clock();
    sort_array(array, size);
    clock_t end = clock();

    printf("Отсортированный ");
    print_array(array, size);
    printf("Время сортировки: %.6f секунд\n", (double)(end - start) / CLOCKS_PER_SEC);

    delete[] array;
}

void handle_file_input() {
    char filename[256];
    printf("Введите имя файла: ");
    scanf("%255s", filename);

    int size = 0;
    int* array = read_array_from_file(filename, size);
    if (array == NULL) {
        printf("Ошибка при чтении файла\n");
        return;
    }

    printf("Исходный ");
    print_array(array, size);

    clock_t start = clock();
    sort_array(array, size);
    clock_t end = clock();

    printf("Отсортированный ");
    print_array(array, size);
    printf("Время сортировки: %.6f секунд\n", (double)(end - start) / CLOCKS_PER_SEC);

    delete[] array;
}

void handle_file_generation() {
    char filename[256];
    int min, max, count;

    printf("Введите имя файла: ");
    scanf("%255s", filename);
    printf("Введите минимальное значение: ");
    scanf("%d", &min);
    printf("Введите максимальное значение: ");
    scanf("%d", &max);
    printf("Введите количество чисел: ");
    scanf("%d", &count);

    generate_random_file(filename, min, max, count);
    printf("Файл '%s' успешно создан с %d случайными числами от %d до %d\n",
        filename, count, min, max);
}

int main() {
    setlocale(LC_ALL, "rus");

    int choice;
    do {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            handle_manual_input();
            break;
        case 2:
            handle_file_input();
            break;
        case 3:
            handle_file_generation();
            break;
        case 4:
            printf("Выход из программы\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 4);

    return 0;
}