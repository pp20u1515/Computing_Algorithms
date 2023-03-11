'''
    Найти корень заданной выше табличной функции с помощью обратной интерполяции
    обоими полиномами.
'''
import interpolation as interpolation
import output as print_data
import copy as cp

def is_change_sign(points) -> bool:
    """
    Проверка на монотонность функции - если True, то нет корней
    Факт наличия корня у функции устанавливается по наличию 
    смены знака у функции при продвижении по строкам таблицы
    :param points: считанный список точек
    :return: True - знак меняется, то есть есть корни, False в противном случае
    """
    prev = points[0].y

    for dot in points:
        cur = dot.y
        if prev * cur < 0:
            return True
        prev = cur

    return False


def swap_abscissa_ordinate(points):
    """
    Функция меняет местами столбцы с аргументом функции и ее значением
    :param points: считанный список точек
    :return: преобразованный список точек
    """
    tmp_points = cp.deepcopy(points)

    for i in range(len(tmp_points)):
        tmp_points[i].x, tmp_points[i].y = tmp_points[i].y, tmp_points[i].x

    return tmp_points


def get_newton_root(points, n):
    """
    Функция вычисляет корень табличной функции с
    помощью обратной интерполяции полинома Ньютона
    :param points: считанный список точек
    :param n: степень полинома
    :return: корень функции
    """
    tmp_points = cp.deepcopy(points)

    tmp_points = swap_abscissa_ordinate(tmp_points)

    tmp_points.sort(key=lambda dot: dot.y)

    tmp_points = interpolation.collect_config(tmp_points, 0, n)

    root = interpolation.polynom(tmp_points, 0, n)

    return root


def get_hermit_root(points, n):
    """
    Функция вычисляет корень табличной функции с
    помощью обратной интерполяции полинома Эрмита
    :param points: считанный список точек
    :param n: степень полинома
    :return: корень функции
    """
    tmp_points = cp.deepcopy(points)
    tmp_points = interpolation.collect_config(tmp_points, 0, n)
    tmp_points = interpolation.get_points_for_hermite(tmp_points)

    #print("\n\tТаблица точек для полинома Эрмита")
    #print_data.print_table(tmp_points)
    
    tmp_points = swap_abscissa_ordinate(tmp_points)

    for dot in tmp_points:
        if not interpolation.float_equal(dot.derivative, 0):
            dot.derivative = 1 / dot.derivative
        else:
            dot.derivative = 0

    tmp_points.sort(key=lambda t: t.y)

    root = interpolation.polynom(tmp_points, 0, n)

    return root


def get_root(points, n):
    """
    Функция вычисляет корень таблично заданной функции
    :param points: считанный список точек
    :param n: степень полинома
    :return: корень
    """
    newton_points = cp.deepcopy(points)
    hermit_points = cp.deepcopy(points)

    root_newton = get_newton_root(newton_points, n)
    root_hermit = get_hermit_root(hermit_points, n)

    return root_newton, root_hermit