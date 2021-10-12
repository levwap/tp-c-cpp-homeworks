

#ifndef HW1_SHIP_H
#define HW1_SHIP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_COUNT_SHIPS 10


#define MAX_SHIP_NAME 4
#define MAX_SHIPYARD_NAME 51
#define MAX_WAR_HISTORY_LENGTH 101

//Неизвестно, В эксплуатации, списан, на модернизации, в ремонте.
enum status {NO_INFORMATION, IN_OPERATION, IS_DECOMMISSIONED,
        ON_MODERNISATION,  UNDER_REPAIR};

typedef struct ship {
    char name[MAX_SHIP_NAME];
    char shipyard[MAX_SHIPYARD_NAME];
    int year;
    char war_history[MAX_WAR_HISTORY_LENGTH];
    size_t crew;
    enum status status;
} ship;


bool create_ship(ship **new_ship_p);
size_t create_ships(ship ***ships);
bool filter(ship ***ships_p, size_t size, bool **flags, ship *pattern);
void print_ships_after_filter(ship **ships, size_t size, const bool *flags);
void delete(ship **ships, bool *flags, ship *pattern, size_t size);




#endif