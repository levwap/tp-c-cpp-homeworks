#include "serial_ranking.h"

struct top_five* ranking(char directory[], char *search_request)
{
    struct top_five *result = create_top();
    if (!result)
        return NULL;

    char **search_words;
    size_t count_search_words = space_split(search_request, &search_words);
    if (!count_search_words)
        return NULL;


    char word[MAX_WORD_IN_FILE];

    size_t count_match;

    DIR *d;
    struct dirent *file;
    d = opendir(directory);
    if (d)
    {
        chdir(directory);
        while ((file = readdir(d)) != NULL)
        {
            if (*file->d_name != '.')
            {
                count_match = 0;
                FILE* f = fopen(file->d_name, "r");
                if (!f)
                    return 0;
                while (read_word_from_file(f, word))
                {
                    for (int i = 0; i < count_search_words; ++i)
                    {
//                        printf("%s ------ %s", word, search_words[i]);
                        if (strcmp(word, search_words[i]) == 0)
                        {
                            ++count_match;
                        }
                    }
                }
                if (count_match > result->fifth)
                    insert(result, file->d_name, count_match);
//                printf("%s\n", word);
                fclose(f);
            }
//            printf("%s\n", file->d_name);

        }
        closedir(d);
    }
    delete(search_words, count_search_words);
    return result;
}

struct top_five* create_top()
{
    struct top_five *top = malloc(sizeof(struct top_five));
    if (!top)
        return NULL;
    top->first = 0;
    top->second = 0;
    top->third = 0;
    top->fourth = 0;
    top->fifth = 0;
    return top;
}

size_t space_split(char* str, char ***result)
{
    *result = NULL;
    size_t count = 0;
    char* tmp = str;
    char delim[3];
    delim[0] = ' ';
    delim[1] = '\n';
    delim[2] = 0;

    int word_flag = 0;


    while (*tmp)
    {
        if (word_flag && *tmp == ' ')
        {
            word_flag = 0;
            ++count;
        }
        else if (*tmp != ' ')
            word_flag = 1;
        ++tmp;
    }
    if (word_flag)
        ++count;
    if (count)
    {
        *result = calloc(count, sizeof(char*));
        if (!(*result))
            return 0;
        size_t index = 0;
        char* token = strtok(str, delim);

        while (token)
        {
            *(*result + index++) = strdup(token);
            token = strtok(0, delim);
        }
    }

//    for (int i = 0; i < count; ++i) {
//        printf("%s\n", result[i]);
//    }

    return count;
}

bool read_word_from_file(FILE *file, char *word)
{
    *word = 0;
    int count = 0;
    char c = (char) fgetc(file);
    //удаляем пробелы и переносы строки в начале
    while (c == '\n' || c == ' ')
        c = (char) fgetc(file);

    while (c != EOF && c != '\n' && c != ' ' && count < MAX_WORD_IN_FILE)
    {
        word[count] = c;
        count++;
        c = (char) fgetc(file);
    }
    if (!count)
        return 0;
    word[count] = 0;
    return 1;
}


//Зачем так сложно? я не знаю)
void insert(struct top_five *top, char *new, size_t new_count) {
    if (new_count > top->first)
        insert_to_first_place(top, new, new_count);
    else if (new_count > top->second)
        insert_to_second_place(top, new, new_count);
    else if (new_count > top->third)
        insert_to_third_place(top, new, new_count);
    else if (new_count > top->fourth)
        insert_to_fourth_place(top, new, new_count);
    else if (new_count > top->fifth)
        insert_to_fifth_place(top, new, new_count);
}

void insert_to_first_place(struct top_five *top, char *new, size_t new_count)
{
    insert_to_second_place(top, top->first_name, top->first);
    memcpy(top->first_name, new, MAX_FILE_NAME);
    top->first = new_count;
}

void insert_to_second_place(struct top_five *top, char *new, size_t new_count)
{
    insert_to_third_place(top, top->second_name, top->second);
    memcpy(top->second_name, new, MAX_FILE_NAME * sizeof(char));
    top->second = new_count;
}

void insert_to_third_place(struct top_five *top, char *new, size_t new_count)
{
    insert_to_fourth_place(top, top->third_name, top->third);
    memcpy(top->third_name, new, MAX_FILE_NAME * sizeof(char));
    top->third = new_count;
}

void insert_to_fourth_place(struct top_five *top, char *new, size_t new_count)
{
    insert_to_fifth_place(top, top->fourth_name, top->fourth);
    memcpy(top->fourth_name, new, MAX_FILE_NAME * sizeof(char));
    top->fourth = new_count;
}

void insert_to_fifth_place(struct top_five *top, char *new, size_t new_count)
{
    memcpy(top->fifth_name, new, MAX_FILE_NAME * sizeof(char));
    top->fifth = new_count;
}

void delete(char **search_words, size_t count_search_words)
{
    for (int i = 0; i < count_search_words; ++i)
    {
        if (search_words[i])
            free(search_words[i]);
    }
    free(search_words);
}