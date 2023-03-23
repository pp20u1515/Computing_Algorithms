#include "io_funcs.h"
#include "return_codes.h"
#include "additional_funcs.h"
#include "task_funcs.h"

int main(int argc, char **argv)
{
    data_t data; // структура таблицы
    double x; // аргумент, для которого выполняется интерполяция
    int rc = OK; // код возврата

    if (argc == 2)
    {
        rc = process_input(&data, argv[1], &x);
        
        if (rc == OK)
        {
            print_table(data);
            sort_table(&data);
            rc = process_task(&data, x);

            if (rc == OK)
                printf("Результат: %.17lf\n", data.result);
        }
    }
    else
    {
        printf("Ошибка! Неправильные аргументы командной строки!\n");
        rc = ARGS_ERROR;
    }

    return rc;
}