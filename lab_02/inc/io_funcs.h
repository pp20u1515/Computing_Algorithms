#ifndef IO_FUNCS_H
#define IO_FUNCS_H

#include <stdio.h>

#include "struct.h"

/**
 * \brief count_obj - Функция, которая читает количество элементов из файла
 * 
 * \param file Входный файл
 * \return Количество элементов прочитаны из файла
 */
size_t count_obj(FILE *file);

/**
 * \brief fill_table - функция, которая заполняет таблицу данными
 * 
 * \param data Структура таблицы 
 * \param file Входный файл
 * \return Код успеха или код ошибки
 */
int fill_table(data_t *data, FILE *file);

/**
 * \brief read_table - Функция, которая читает таблицу из файла
 * 
 * \param data Структура таблицы
 * \param file_name Название входного файла
 * \return Код успеха или код ошибки
 */
int read_table(data_t *data, const char *file_name);

/**
 * \brief process_input - функция, которая, обработывает ввод
 * 
 * \param data Структура таблицы
 * \param file_name Название входного файла
 * \param x Аргумент, для которого выполняется интерполяция
 * \return Код успеха или код ошибки
 */
int process_input(data_t *data, const char *file_name, double *x);

/**
 * \brief print_table - Вывод таблицы
 * 
 * \param data Структура таблицы
 */
void print_table(const data_t data);

// Граничные условия
void print_info();

#endif // IO_FUNCS_H