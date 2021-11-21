#ifndef HW2_SERIAL_RANKING_H
#define HW2_SERIAL_RANKING_H

#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_FILE_NAME 30
#define MAX_WORD_IN_FILE 50


struct top_five {
    char first_name[MAX_FILE_NAME];
    char second_name[MAX_FILE_NAME];
    char third_name[MAX_FILE_NAME];
    char fourth_name[MAX_FILE_NAME];
    char fifth_name[MAX_FILE_NAME];
    size_t first;
    size_t second;
    size_t third;
    size_t fourth;
    size_t fifth;
};

bool insert_in_top(struct top_five *topFive);
struct top_five* create_top();



struct top_five* ranking(char directory[], char *search_request);
bool read_word_from_file(FILE *file, char *word);
size_t space_split(char* str, char ***result);

void insert(struct top_five *top, char *new, size_t new_count);
void insert_to_first_place(struct top_five *top, char *new, size_t new_count);
void insert_to_second_place(struct top_five *top, char *new, size_t new_count);
void insert_to_third_place(struct top_five *top, char *new, size_t new_count);
void insert_to_fourth_place(struct top_five *top, char *new, size_t new_count);
void insert_to_fifth_place(struct top_five *top, char *new, size_t new_count);



void delete(char **search_words, size_t count_search_words);

#endif //HW2_SERIAL_RANKING_H
