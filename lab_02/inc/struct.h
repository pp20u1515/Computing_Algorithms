#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>

typedef struct table_t
{
    double x;
    double y;
}table_t;

typedef struct data_t
{
    double *coeff_a; // коэффициент а
    double *coeff_b; // коэффициент b
    double *coeff_c; // коэффициент c
    double *coeff_d; // коэффициент d
    double result; // результат
    size_t size; // размер таблицы
    double *h; //  h = (x - xi)
    table_t *table; // таблица данных
}data_t;

#endif // STRUCT_H