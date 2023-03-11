'''
    Решить систему нелинейных уравнений, основываясь на простой идее обратной интерполяции

    С помощью интерполяции перестроить приведенные табличные представления
    функций к новой таблице, в которой содержится зависимость разности функций y(x) из
    (1) и (2) от фиксированного набора значений аргумента x, например, такого, как во второй
    таблице, или любого другого из рассматриваемого интервала. Затем применить процедуру
    обратной интерполяции.

    выбираем множество Х для двух функций (удобно взять Х-сы их 2-й таблицы, поскольку Y для них известны)
    Чтобы найти разность Y тебе нужно из значений Y второй таблицы
    вычесть значения Y из первой таблицы, но с помощью интерполяции в тех же x
'''

import interpolation as interpolation
import output as print_data
import input as read
import copy as cp
import point as point
from task_two import swap_abscissa_ordinate, get_newton_root

N = 3

def change_table(points1, points2, n):
    """
    Функция в первой таблице изменяет с помощью интерполяции
    ординаты в соответствии с абсциссами второй таблицы
    :param points1: первая таблица точек
    :param points2: вторая таблица точек
    :param n: степень полинома
    :return: новую первую таблицу
    """
    new_points1 = []

    for i in range(len(points2)):
        tmp_points = cp.deepcopy(points1)

        tmp_points = interpolation.collect_config(tmp_points, points2[i].x, n)
        result_newton = interpolation.polynom(tmp_points, points2[i].x, n)

        new_points1.append(point.Point(points1[i].x, result_newton, 0))

    return new_points1


def get_subtract_table(points1, points2):
    """
    Функция получает новую таблицу, в которой содержится зависимость разности функций y(x) из
    (1) и (2) от фиксированного набора значений аргумента из второй таблицы
    :param points1: первая уже измененная ранее таблица точек
    :param points2: вторая таблица точек
    :return: таблица разностей функций y(x)
    """
    subtract_table = []

    for i in range(len(points2)):
        subtract_table.append(point.Point(points2[i].x, points2[i].y - points1[i].y, 0))

    return subtract_table


def get_system_root(n):
    """
    Функция находит корень системы
    :param n: степень полинома Ньютона
    :return: корень
    """

    points1 = read.read_system_table("../data/system1.txt")

    points2 = read.read_system_table("../data/system2.txt")

    # смена столбцов
    points1 = swap_abscissa_ordinate(points1)

    print("\tПервая считанная таблица Y(X):")
    print_data.print_table(points1)

    print("\n\tВторая считанная таблица Y(X):")
    print_data.print_table(points2)

    # степень полинома len(points1) - 1, поскольку нужно, чтобы все точки участвовали в интерполяции
    points1 = change_table(points1, points2, len(points1) - 1)

    print("\nИнтерполированная первая таблица (Ординаты интерполированы для абсцисс второй таблицы):")
    print_data.print_table(points1)

    table = get_subtract_table(points1, points2)

    print("\nТаблица с разностями абсцисс двух таблиц и ординат второй таблицы")
    print_data.print_table(table)

    root_x = get_newton_root(table, N)

    tmp_points2 = cp.deepcopy(points2)

    config_points2 = interpolation.collect_config(tmp_points2, root_x, N)

    root_y = interpolation.polynom(config_points2, root_x, N)

    return root_x, root_y