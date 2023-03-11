import input as read
import output as print_data
import task_one as task_one
import task_two as task_two
import task_three as task_three

SIZE = 75

def main():

    filename = "../data/data.txt"

    print_data.print_task_one()
    points = read.read_table(filename)

    print("\t\tИсходная таблица данных:")
    print_data.print_table(points)
    n = read.read_degree()
    x = read.read_x()

    table_value = task_one.get_table_value(x, points)
    print_data.print_table_value(table_value, x)

    print_data.print_task_two()
    if task_two.is_change_sign(points):
        root_newton, root_hermit = task_two.get_root(points, n)
        print_data.print_root(points, root_newton, root_hermit, n)
    else:
        print("Функция не имеет корней!")

    print_data.print_task_three()
    root_system_x, root_system_y = task_three.get_system_root(n)
    print_data.print_system_root(root_system_x, root_system_y, n)


if __name__ == "__main__":
    main()