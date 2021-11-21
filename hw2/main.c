/*Вариант #32
В вашем распоряжении директория с 500 текстовыми файлами, каждый из которых занимает 1 МБ места на диске.
 Необходимо реализовать последовательную и параллельную программу поиска с использованием нескольких процессов
 топ-5 файлов по текстовому запросу. Принцип ранжирования – наибольшее количество упоминаний слов запроса в тексте.*/

#include "io.h"
#include "lib/static/serial_ranking.h"


int main() {
    char search_request[MAX_REQUEST_SIZE];
    struct top_five *top = NULL;
    if (input_request(search_request))
    {
        top = ranking("../small_data", search_request);
        if (top)
            print_top(top);
    }

    if (top)
        free(top);
    return 0;
}
