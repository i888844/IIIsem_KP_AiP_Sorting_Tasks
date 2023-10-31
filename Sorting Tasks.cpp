#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "windows.h"
#include "locale.h"

#pragma warning(disable: 4996)

#define ANSI_COLOR_RED   "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int* create_array(int lenght)
{
    int* array = (int*)calloc(lenght, sizeof(int));
    return array;
}

void free_array(int* array)
{
    free(array);
}

void output_array(int* array, int lenght)
{
    for (int i = 0; i < lenght; i++)
    {
        printf("%10i", array[i]);
    }
    printf("\n");
}

void output_array_with_colors(int* array, int length, int index1, int index2)
{
    for (int i = 0; i < length; i++)
    {
        if (i == index1 || i == index2)
        {
            printf(ANSI_COLOR_RED "%10i" ANSI_COLOR_RESET, array[i]);
        }
        else
        {
            printf("%10i ", array[i]);
        }
    }
    printf("\n");
}

void fill_array_rand(int* array, int lenght)
{
    srand(time(NULL));
    for (int i = 0; i < lenght; i++)
    {
        array[i] = rand() % 200 - 150;
    }
}

void fill_array_from_keyboard(int* array, int lenght)
{
    printf("Введите элементы массива:\n");
    for (int i = 0; i < lenght; i++)
    {
        printf("Введите элемент в позиции [%i]: ", i);
        scanf("%i", &array[i]);
        printf("\n");
    }
}

void fill_array_from_file(int* array, int lenght, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("[Ошибка]: Не удалось открыть файл.\n");
        exit(1);
    }
    int number = 0;
    for (int i = 0; i < lenght; i++)
    {
        number = 0;
        srand(time(NULL));
        if (fscanf(file, "%i", &number) == 1)
        {
            array[i] = number;
        }
        else
        {
            array[i] = rand() % 200 - 100;
        }
    }
    fclose(file);
}

void delete_positive_numbers(int* array, int* length)
{
    int shift = 0;
    for (int i = 0; i < *length; i++)
    {
        if (array[i] >= 0)
        {
            shift++;
        }
        else
        {
            array[i - shift] = array[i];
        }
    }
    *length -= shift;
}

void selection_sort(int* array, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < length; j++)
        {
            if (array[j] < array[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            output_array_with_colors(array, length, i, min_index);
            int temp = array[i];
            array[i] = array[min_index];
            array[min_index] = temp;
            output_array_with_colors(array, length, i, min_index);
            printf("\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int lenght = 0;
    int cmd = 0;
    printf("Введите длину массива: ");
    scanf_s("%i", &lenght);
    while (lenght <= 0)
    {
        printf("[Ошибка]: длина массива не может быть меньше или равна нулю. Введите длину массива: ");
        scanf_s("%i", &lenght);
    }
    int* array = create_array(lenght);
    printf("Выберите вариант формирования массива:\n");
    printf("1. Сформировать массив случайным образом.\n");
    printf("2. Сформировать массив вводом с клавиатуры.\n");
    printf("3. Сформировать массив данными из файла.\n");
    printf("0. Завершить работу программы.\n");
    printf("Введите номер действия: ");
    scanf_s("%i", &cmd);
    while (cmd < 0 || cmd > 3)
    {
        printf("[Ошибка]: выбран неверный номер действия. Введите номер действия: ");
        scanf_s("%i", &cmd);
    }
    switch (cmd)
    {
        case 0:
        {
            free_array(array);
            return 0;
            break;
        }
        case 1:
        {
            fill_array_rand(array, lenght);
            break;
        }
        case 2:
        {
            fill_array_from_keyboard(array, lenght);
            break;
        }
        case 3:
        {
            char filename[256];
            printf("Введите название файла с форматом (пример: filename.txt): ");
            scanf_s("%255s", &filename, sizeof(filename));
            fill_array_from_file(array, lenght, filename);
            break;
        }
    }
    printf("Первоначальный массив:\n");
    output_array(array, lenght);
    printf("\nИсключаем положительные элементы:\n");
    delete_positive_numbers(array, &lenght);
    output_array(array, lenght);
    printf("\nСортируем методом выбора:\n");
    selection_sort(array, lenght);
    printf("Отсортированный массив:\n");
    output_array(array, lenght);
    return 0;
}