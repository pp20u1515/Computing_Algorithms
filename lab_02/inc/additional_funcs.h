#ifndef ADDITIONAL_FUNCS_H
#define ADDITIONAL_FUNCS_H

#include <stdio.h>

#include "struct.h"

/**
 * \brief allocate_array - Функция, которая выделяет память под массивом
 * 
 * \param array Массив
 * \param size Размер массива
 * \return Код успеха или код ошибки
 */
int allocate_array(double *array, const size_t size);

/**
 * \brief allocate_table - Функция, которая выделяет память под таблицой
 * 
 * \param data Структура таблицы
 * \param file Входный файл
 * \return Код успеха или код ошибки
 */
int allocate_table(data_t *data, FILE *file);

/**
 * \brief swap - Функция, которая меняет местами строки таблицы
 * 
 * \param data Структура таблицы
 * \param index Индекс текущей строки
 */
void swap(data_t *data, const size_t index);

/**
 * \brief sort_table - Функция, которая сортирует таблицу по возрастанию
 * 
 * \param data Структура таблицы
 */
void sort_table(data_t *data);

/**
 * \brief allocate_two_coeff - Функция, которая выделяет память под два коэффициента
 * 
 * \param first_coeff Первый коэффициента
 * \param second_coeff Второй коэффициента
 * \param size Размер массива
 * \return Код успеха или код ошибки
 */
int allocate_two_coeff(double **first_coeff, double **second_coeff, const size_t size);

/**
 * \brief allocate_coeff - Функция, которая выделяет памят под коэффициентами
 * 
 * \param data Структура таблицы
 * \return Код успеха или код ошибки
 */
int allocate_coeff(data_t *data);

#endif // ADDITIONAL_FUNCS_H