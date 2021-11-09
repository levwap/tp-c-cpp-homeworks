

#include "input.h"

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