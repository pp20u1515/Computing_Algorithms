'''
    Получить таблицу значений y(x) при степенях полиномов Ньютона и Эрмита n = 1, 2, 3, 
    4 и 5 при фиксированном x, например, x=0.675 (середина интервала 0.6 - 0.75). Сравнить 
    результаты при одинаковых степенях .полиномов Ньютона и Эрмита.
'''
import interpolation as interpolation

def get_table_value(x, points):
    """
    Функция получает таблицу значений при разных степенях полиномов
    и при фиксированном x
    :param x: точка интерполирования
    :param points: считанный список точек
    :return: таблица значений
    """
    table_value = []

    for i in range(1, 6):
        config_points = interpolation.collect_config(points, x, i)
        result_newton = interpolation.polynom(config_points, x, i)
        config_points = interpolation.get_points_for_hermite(config_points)
        result_hermit = interpolation.polynom(config_points, x, i)
        table_value.append([i, result_newton, result_hermit])

    return table_value