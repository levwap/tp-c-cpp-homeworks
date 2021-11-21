

#include "io.h"

static void clean_input() {
    char c = ' ';
    while(c != EOF && c != '\n') {
        scanf("%c", &c);
    }
}

bool input_request(char *request)
{
    printf("Input your search request: ");
    fgets(request, MAX_REQUEST_SIZE, stdin);
    char *newline_ptr = NULL;
    newline_ptr = strchr(request, '\n');
    if (newline_ptr == NULL)
        clean_input();
}

void print_top(struct top_five *top)
{
    if (!top->first)
    {
        printf("No match\n");
        return;
    }
    else
        printf("1. %s. Count - %zu\n", top->first_name, top->first);

    if (top->second)
        printf("2. %s. Count - %zu\n", top->second_name, top->second);

    if (top->third)
        printf("3. %s. Count - %zu\n", top->third_name, top->third);

    if (top->fourth)
        printf("4. %s. Count - %zu\n", top->fourth_name, top->fourth);

    if (top->fifth)
        printf("5. %s. Count - %zu\n", top->fifth_name, top->fifth);;
}