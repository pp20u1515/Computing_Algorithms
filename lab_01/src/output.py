SIZE_TABLE = 47
SIZE_TABLE_VALUE = 53

def print_task_one():
    print('ЗАДАНИЕ 1')
    print('Получить таблицу значений y(x) при степенях полиномов Ньютона и  \n Эрмита n = 1, 2, 3, 4 и 5 при фиксированном x. Сравнить результаты \n при одинаковых степенях полиномов Ньютона и Эрмита.\n')


def print_task_two():
    print('\nЗАДАНИЕ 2')
    print('Найти корень заданной выше табличной функции с помощью обратной \n интерполяции обоими полиномами.\n')


def print_task_three():
    print('\nЗАДАНИЕ 3')
    print('Решить систему нелинейных уравнений, основываясь на простой идее \n обратной интерполяции.\n')
 

def print_table(points_table):
    """
    Функция выводит на экран считанные
    из файла табличные значения точек
    """
    print("|" + SIZE_TABLE * "-" + "|")
    print(f"|{'X':^15s}|{'Y':^15s}|{'Y`':^15s}|")
    print("|" + SIZE_TABLE * "-" + "|")

    for point in points_table:
        print("| {:^13.3f} | {:^13.3f} | {:^13.3f} |".format(
            point.x,
            point.y,
            point.derivative)
        )

    print("|" + SIZE_TABLE * "-" + "|")

def print_table_value(table_value, x) -> None:
    """
    Функция выводит на экран таблицу значений
    :param table_value: матрица - таблица значений
    :param x: точка интерполяции
    :return:
    """
    print("\nТаблица значений y(x) при степенях "
          "полиномов Ньютона и Эрмита при x = {:<13.3f}".format(x))
    print("|" + SIZE_TABLE_VALUE * "-" + "|")
    print(f"| {'Степень полинома':^17s}|{'Полином Ньютона':^17s}|{'Полином Эрмита':^16s}|")
    print("|" + SIZE_TABLE_VALUE * "-" + "|")

    for i in range(len(table_value)):
        print("| {:^16d} | {:^15.7f} | {:^14.7f} |".format(
            table_value[i][0],
            table_value[i][1],
            table_value[i][2])
        )

    print("|" + SIZE_TABLE_VALUE * "-" + "|")


def print_root(points, root_newton, root_hermit, n) -> None:
    """
    Функция выводит на экран корень таблично заданной функции
    :param points: считанный список точек
    :param root_newton: корень, найденный с помощью полинома Ньютона
    :param root_hermit: корень, найденный с помощью полинома Эрмита
    :param n: степень полиномов
    :return:
    """
    #print("\nТабличная функция, для которой был найден корень:")
    #print_table(points)

    print("Корень, найденный с помощью полинома Ньютона (степень полинома  n = {:}): ".format(n), end='')
    print(f"{root_newton:<13.7f}")

    print("Корень, найденный с помощью полинома Эрмита  (степень полинома  n = {:}): ".format(n), end='')
    print(f"{root_hermit:<13.7f}")


def print_system_root(root_x, root_y, n) -> None:
    """
    Функция выводит на экран корни системы
    :param root_x: абсцисса
    :param root_y: ордината
    :param n: степень полинома
    :return:
    """
    print("\nКорни системы, найденные с помощью полинома Ньютона:")
    print(f"my = {root_y:<13.3f}", f"x = {root_x:<13.3f}", sep='\n')