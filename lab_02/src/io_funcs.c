#include "io_funcs.h"
#include "return_codes.h"
#include "additional_funcs.h"

#include <stdlib.h>

size_t count_obj(FILE *file)
{
    size_t count = 0; // счетчик
    double x, y; // аргументы
    int flag = 0; // флаг
    
    while (flag == 0 && !feof(file))
    {
        if (fscanf(file, "%lf%lf", &x, &y) == 2)
            count++;
        else
            flag = 1;
    }
    
    if (flag == 1) // если обнаружили ошибку при чтением файла
        count = 0;

    return count;
}

int fill_table(data_t *data, FILE *file)
{
    int rc = OK; // код возврата

    rewind(file);
    
    for(size_t index = 0; rc == OK && index < data->size; index++)
    {
        if (fscanf(file, "%lf%lf", &data->table[index].x, &data->table[index].y) != 2)
            rc = DATA_ERROR;   
    }

    if (rc == DATA_ERROR)
        printf("Ошибка! Неправильные данные!\n");

    return rc;

}

int read_table(data_t *data, const char *file_name)
{
    int rc = OK; // код возврата
    FILE *f_open = fopen(file_name, "r");

    if (f_open)
    {
        rc = allocate_table(data, f_open);
        
        if (rc == OK)
        {
            rc = fill_table(data, f_open);

            if (rc != OK)
                free(data->table);
        }

        fclose(f_open);
    }
    else
    {
        printf("Ошибка: Не удалось открыть файл!\n");
        rc = FREAD_ERROR;
    }
    return rc;
}

int process_input(data_t *data, const char *file_name, double *x)
{
    int rc = read_table(data, file_name);

    if (rc == OK)
    {
        printf("Введите значение для х: ");
        if (scanf("%lf", x) != 1)
        {
            printf("Ошибка: Неправильно ввели значение для х\n");
            rc = DATA_ERROR;
        }
    }
    return rc;
}

void print_table(const data_t data)
{
    printf("\nИсходная таблица\n");
    printf("+-----+-----+\n");
    printf("|  x  |  y  |\n");
    printf("|-----|-----|\n");

    for (size_t index = 0; index < data.size; index++)
    {
        printf("|%.3lf|%.3lf|\n", data.table[index].x, data.table[index].y);

        if (index != data.size - 1)
            printf("|-----|-----|\n");
        else
            printf("+-----+-----+\n");
    }
}

void print_info()
{
    printf("Граничные условия:\n\
    1: x0 = 0\n" // вторая производная сплайна в левом краевом узле равна 0\n'
    "  xn = 0\n" // вторая производная сплайна в правом краевом узле равна 0\n'
    "2: x0 = P3''(x0)\n" // вторая производная сплайна в левом краевом узле равна\n'
                        // второй производной полинома Ньютона третьей степени\n'
    "xn = 0\n" // вторая производная сплайна в правом краевом узле равна 0\n'
    "3: x0 = P3''(x0)\n" // вторая производная сплайна в левом краевом узле равна\n'
                        // второй производной полинома Ньютона третьей степени\n'
    "xn = P3``(xn)\n"); // вторая производная сплайна в правом краевом узле равна\n'
                        // второй производной полинома Ньютона третьей степени\n'");
}