#ifndef TASK_FUNCS_H
#define TASK_FUNCS_H

#include "struct.h"

/**
 * \brief coeff_a - Функция, которая записывает все значения у для коэффициента a
 * так, как a[i] == y[i - 1]
 * 
 * \param data Структура таблицы
 */
void coeff_a(data_t *data);

/**
 * \brief calc_h - Функция, которая вычисляет разницы y[i] - y[i - 1]
 * 
 * \param data Структура таблицы
 * \return Код успеха или код ошибки
 */
int calc_h(data_t *data);

/**
 * \brief calc_splain - Функция, которая вычисляет сплайн 
 * 
 * \param data Структура таблицы
 * \param x Аргумент, для которого вычисляется интерполяция
 * \return Код успеха или код ошибки
 */
int calc_splain(data_t *data, const double x);

/**
 * \brief process_task - Функция, с которой начинается вычисление кубического сплайна
 * 
 * \param data Структура таблицы
 * \param x Аргумент, для которого вычисляется интерполяция
 * \return Код успеха или код ошибки
 */
int process_task(data_t *data, const double x);

/**
 * \brief find_selection - Функция, которая находить индекс элемента, который больше аргумента х,
 * для которого вычисляется интерполяция
 * \param data Структура таблицы
 * \param x Аргумент, для которого вычисляется интерполяция
 * \return Индекс элемента, который больше аргумента х,
 * для которого вычисляется интерполяция 
 */
size_t find_selection(data_t *data, const double x);

/**
 * \brief start_ratios Функция, которая вычисляет производные Ньютона
 * 
 * \param data Структура таблицы
 * \param ksi Прогоночный коэффициент
 */
void start_ratios(data_t *data, double *ksi);

/**
 * \brief straight_walk - Прямой ход нужен, чтобы вычислить прогоночные коэффициенты кси и тета
 * для метода гаусса, по дефолту кси и тета = 0 (из условия с1 = 0, в узлах значения многочлена
 * и интерполируемой функции совпадают)
 * 
 * \param ksi Прогоночный коэффициент кси
 * \param eta Прогоночный коэффициент тета
 * \param data Структура таблицы
 */
void straight_walk(double *ksi, double *eta, data_t *data);

/**
 * \brief forward_walk - Oбратный ход нужен, чтобы найти коэффициенты с
 * они зависят от теты и кси, которые мы нашли в прямом ходе
 * 
 * \param ksi Прогоночный коэффициент кси
 * \param eta Прогоночный коэффициент тета
 * \param data Структура таблицы
 */
void forward_walk(double *ksi, double *eta, data_t *data);

/**
 * \brief find_ratios - Функция, которая находит коэффициенты d и b
 * 
 * \param data Структура таблицы
 */
void find_ratios(data_t *data);

#endif // TASK_FUNCS_H