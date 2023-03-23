#include "additional_funcs.h"
#include "return_codes.h"
#include "io_funcs.h"

#include <stdlib.h>

int allocate_array(double *array, const size_t size)
{
    int rc = OK; // код возврата

    array = calloc(size, sizeof(double));

    if (array == NULL)
        rc = ALLOCATE_ERROR;

    return rc;
}

int allocate_table(data_t *data, FILE *file)
{
    int rc = OK; // код возврата

    data->size = count_obj(file);

    if (data->size)
    {
        data->table = malloc(data->size * sizeof(table_t));
        
        if (data->table == NULL)
        {
            printf("Ошибка! Не удалось выделить память!\n");
            rc = ALLOCATE_ERROR;
        }
    }
    else
    {
        printf("Ошибка: Не удалось прочитать данные из файла!\n");
        rc = DATA_ERROR;
    }

    return rc;
}

void swap(data_t *data, const size_t index)
{
    table_t temp_data = data->table[index];
    data->table[index] = data->table[index + 1];
    data->table[index + 1] = temp_data;
}

void sort_table(data_t *data)
{
    for (size_t index_i = 0; index_i < data->size - 1; index_i++)
        for (size_t index_j = 0; index_j < data->size - index_i - 1; index_j++)
            if (data->table[index_j].x > data->table[index_j + 1].x)
                swap(data, index_j);
}

int allocate_two_coeff(double **first_coeff, double **second_coeff, const size_t size)
{
    int rc = OK; // код возврата
    *first_coeff = calloc(size, sizeof(double));

    if (*first_coeff)
    {
        *second_coeff = calloc(size, sizeof(double));

        if (*second_coeff == NULL)
        {
            printf("Ошибка! Не удалось выделить память!\n");
            rc = ALLOCATE_ERROR;
            free(*first_coeff);
        }
    }
    else
    {
        printf("Ошибка! Не удалось выделить память!\n");
        rc = ALLOCATE_ERROR;
    }
    return rc;
}

int allocate_coeff(data_t *data)
{
    int rc = allocate_two_coeff(&data->coeff_a, &data->coeff_b, (size_t)(data->size + 1));
    
    if (rc == OK)
    {
        rc = allocate_two_coeff(&data->coeff_c, &data->coeff_d, (size_t)(data->size + 1));

        if (rc != OK)
        {
            free(data->coeff_a);
            free(data->coeff_b);
        }
    }
    return rc;
}