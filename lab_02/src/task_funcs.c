#include "task_funcs.h"
#include "return_codes.h"
#include "additional_funcs.h"
#include "io_funcs.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BUFF_LEN 3

void coeff_a(data_t *data)
{
    for (size_t index = 0; index < data->size; index++)
        data->coeff_a[index + 1] = data->table[index].y;
}

int calc_h(data_t *data)
{
    int rc = OK; // код возврата
    data->h = calloc(data->size,  sizeof(double));

    if (data->h)
    {
        data->h[0] = 0.0;

        for (size_t index = 1; index < data->size; index++)
            data->h[index] = data->table[index].x - data->table[index - 1].x;
    }
    else
    {
        printf("Ошибка! Не удалось выделить память!\n");
        rc = ALLOCATE_ERROR;
    }
    return rc;
}

double newton(data_t *data, const double x, const size_t n)
{
    double *diff = calloc(data->size, sizeof(double));
    double args[11] = {0};
    double value[11] = {0};
    double result = 0;

    if (diff)
    {
        for (size_t index = 0; index < data->size; index++)
        {
            args[index] = data->table[index].x;
            value[index] = data->table[index].y;
        }

        diff[0] = data->table[0].y;
        size_t temp_size = data->size;

        for (size_t index_i = 1; index_i < temp_size; index_i++)
        {
            for (size_t index_j = 0; index_j < temp_size - 1; index_j++)
                value[index_j] = (value[index_j] - value[index_j + 1]) / (args[index_j] - args[index_j + 1]);

            diff[index_i] = value[0];
            temp_size--;
        }
 
        double multiplier = 1;

        for (size_t index = 0; index < n; index++)
        {
            result += diff[index] * multiplier;
            multiplier *= (x - args[index]);
        }
    }
    return result;
}

void start_ratios(data_t *data, double *ksi)
{
    int choice = -1;
    char choice_buf[BUFF_LEN];

    while (choice <= 0)
    {
        print_info();
        printf("Введите граничные условия: ");

        scanf("%s", choice_buf);
        choice = atoi(choice_buf);

        while (!choice)
        {
            printf("\tОшибка: Неправильный ввод!\n");

            printf("Введите граничные условия: ");
            scanf("%s", choice_buf);
            choice = atoi(choice_buf);
        }
        switch(choice)
        {
            case (1):
                break;
            case (2):
                data->coeff_c[1] = newton(data, 0, 3);
                ksi[2] = 1;
                break;
            case (3):
                data->coeff_c[data->size - 1] = newton(data, 0, 3);
                data->coeff_c[1] = newton(data, 10, 3);
                ksi[2] = 1;
                break;
            default:
                break;
        }
    }

}

void straight_walk(double *ksi, double *eta, data_t *data)
{
    double func = 0;
    double deminator = 0;

    for (size_t index = 3; index < data->size; index++)
    {
        func = -3 * ((data->table[index - 1].y - data->table[index - 2].y) / data->h[index - 1] - \
        (data->table[index - 2].y - data->table[index - 3].y) / data->h[index - 2]);
        deminator = -2 * (data->h[index - 1] + data->h[index - 2] - data->h[index - 2] * ksi[index - 1]);
        ksi[index] = data->h[index - 1] / deminator;
        eta[index] = (func + data->h[index - 2] * eta[index - 1]) / deminator;
    }
}

void forward_walk(double *ksi, double *eta, data_t *data)
{
    data->coeff_c[data->size - 2] = eta[data->size - 1];

    for (size_t index = data->size - 2; index > 1; index--)
    {
        data->coeff_c[index] = ksi[index + 1] * data->coeff_c[index + 1] + eta[index + 1]; 
    }
}

void find_ratios(data_t *data)
{
    for (size_t index = 0; index < data->size; index++)
    {
        data->coeff_d[index] = (data->coeff_c[index + 1] - data->coeff_c[index]) / (3 * data->h[index]);
        data->coeff_b[index] = (data->coeff_a[index + 1] - data->coeff_a[index]) /\
        data->h[index] - data->h[index] / 3 * (data->coeff_c[index + 1] + 2 * data->coeff_c[index]);
    }
}

double find_result(const double x, const double a, const double b, const double c,\
const double d, const double x1)
{
    return a + b * (x - x1) + c * pow((x - x1), 2) + d * pow((x - x1), 3);
}

size_t find_selection(data_t *data, const double x)
{
    size_t index = 0;

    if (data->table[0].x - data->table[1].x < 0)
    {
        while (x > data->table[index].x && index < data->size - 1)
            index++;
    }
    else
    {
        while (x > data-> table[index].x && index < data->size - 1)
            index++;
    }
    return index;
}

int calc_splain(data_t *data, const double x)
{
    double *ksi = NULL, *eta = NULL; // прогоночные коэффициенты для метода гаусса
    size_t index = 0;
    int rc = allocate_two_coeff(&ksi, &eta, data->size + 1);

    if (rc == OK)
    {
        index = find_selection(data, x);
        start_ratios(data, eta);

        straight_walk(ksi, eta, data);
        forward_walk(ksi, eta, data);
        find_ratios(data);
        
        data->result = find_result(x, data->coeff_a[index], data->coeff_b[index],\
        data->coeff_c[index], data->coeff_d[index], data->table[index - 1].x);
    }
    return rc;
}

int process_task(data_t *data, const double x)
{
    int rc = allocate_coeff(data);

    if (rc == OK)
    {
        coeff_a(data);
        rc = calc_h(data);

        if (rc == OK)
        {
            rc = calc_splain(data, x);
        }
        free(data->coeff_a);
        free(data->coeff_b);
        free(data->coeff_c);
        free(data->coeff_d);
    }
    return rc;
}