#include "ship.h"



static void clean_input() {
    char c = ' ';
    while(c != EOF && c != '\n') {
        scanf("%c", &c);
    }
}

static int safe_int_input(int *number)
{
    long a;
    char buf[32];

    if (!fgets(buf, 32, stdin))
    {
        return 0;
    }

    bool need_clean = strchr(buf, '\n');

    char *end_ptr;

    a = strtol(buf, &end_ptr, 10);
    if (end_ptr == buf)
    {
        return 0;
    }
    if (*end_ptr && *end_ptr != '\n')
    {
        return 0;
    }




    *number = (int) a;
    if ((void *) need_clean == NULL)
        clean_input();
    return 1;
}



bool create_ship(ship **new_ship_p) {
    if (!new_ship_p) {
        return false;
    }
    *new_ship_p = (struct ship *)malloc(sizeof(struct ship));
    if (!*new_ship_p)
        return false;
    ship *new_ship = *new_ship_p;
    new_ship->year = 3000;
    new_ship->crew = 0;
    new_ship->status = NO_INFORMATION;

    char *newline_ptr = NULL;

    printf("Input ship name(if no information press Enter): ");
    fgets(new_ship->name, MAX_SHIP_NAME, stdin);
    newline_ptr = strchr(new_ship->name, '\n');
    if (newline_ptr == NULL)
        clean_input();
    else
        *newline_ptr = 0;

    printf("Input shipyard name(if no information press Enter): ");
    fgets(new_ship->shipyard, MAX_SHIPYARD_NAME, stdin);
    newline_ptr = strchr(new_ship->shipyard, '\n');
    if (newline_ptr == NULL)
        clean_input();
    else
        *newline_ptr = 0;

    printf("Input year of production(if no information input more than 2021): ");
    while (!safe_int_input(&(new_ship->year)));

    printf("Input war history(if no information press Enter): ");
    fgets(new_ship->war_history, MAX_WAR_HISTORY, stdin);
    newline_ptr = strchr(new_ship->war_history, '\n');
    if (newline_ptr == NULL)
        clean_input();
    else
        *newline_ptr = 0;


    int success;
    int crew = -1;
    do {
        printf("Input number of crew(if no information input 0): ");
        success = safe_int_input(&crew);
    } while (success != 1 || crew < 0);
    new_ship->crew = crew;

    int status = -1;
    do {
        printf("Input ship status:\n"
               "No information - 0\n"
               "In operation - 1\n"
               "Is decommissioned - 2\n"
               "On modernisation - 3\n"
               "Under repair - 4\n");
        success = safe_int_input(&status);
    } while (success != 1 || status < 0 || status > 4);
    new_ship->status = (enum status)status;

    return true;
}

size_t create_ships(ship ***ships) {
    if (!ships) {
        return 0;
    }

    *ships = (ship **)malloc(sizeof(ship*) * MAX_COUNT_SHIPS);
    if (!*ships)
        return 0;
    bool success = true;
    char answer = ' ';
    int count = 0;
    for (size_t i = 0; success && count != MAX_COUNT_SHIPS; ++i, ++count) {
        (*ships)[i] = NULL;
        success = create_ship((*ships) + i);

        if (success) {
            printf("Do you want to input one more ship (y/n)? ");
            scanf("%c", &answer);
            clean_input();
            success = false;
            if (answer == 'y')
                success = true;
        }
    }
    return count;


}

//Функция возвращает массив. 0 - не прошел фильтр. 1 - прошел
bool filter(ship ***ships_p, size_t size, bool **flags, ship *pattern) {
    if (!pattern)
        return false;
    if (!ships_p)
        return false;
    if (size == 0)
        return false;
    (*flags) = (bool*)malloc(sizeof(bool) * size);
    if (!(*flags))
        return false;
    ship **ships = *ships_p;
    for (size_t i = 0; i < size; ++i) {
        (*flags)[i] = true;
        if (*(pattern->name))
            if (strcmp(pattern->name, (ships[i])->name) != 0) {
                (*flags)[i] = false;
                continue;
            }

        if (*(pattern->shipyard))
            if (strcmp(pattern->shipyard, (ships[i])->shipyard) != 0){
                (*flags)[i] = false;
                continue;
            }

        if (*(pattern->war_history))
            if (strcmp(pattern->war_history, (ships[i])->war_history) != 0) {
                (*flags)[i] = false;
                continue;
            }

        if (pattern->year < 2021)
            if (pattern->year != (ships[i]->year)) {
                (*flags)[i] = false;
                continue;
            }

        if (pattern->crew)
            if (pattern->crew != (ships[i])->crew) {
                (*flags)[i] = false;
                continue;
            }
        if (pattern->status)
            if (pattern->status != (ships[i])->status) {
                (*flags)[i] = false;
            }
    }
    return true;

}


void print_ships_after_filter(ship **ships, size_t size, const bool *flags) {
    printf("\n\n\n");
    for (size_t i = 0; i < size; ++i) {
        if (flags[i]) {
            if (((ships[i])->name)[0])
                printf("Ship name: %s\n", ((ships[i])->name));
            if (((ships[i])->shipyard)[0])
                printf("Shipyard name: %s\n", ((ships[i])->shipyard));
            if (((ships[i])->year) < 2022)
                printf("Ship year: %d\n", ((ships[i])->year));
            if (((ships[i])->war_history)[0])
                printf("Ship war history: %s\n", ((ships[i])->war_history));
            if (ships[i]->crew)
                printf("Ship count of crew: %zu\n", ships[i]->crew);
            if (ships[i]->status)
                switch (ships[i]->status) {
                    case IN_OPERATION:
                        printf("Ship in operation.\n");
                        break;
                    case IS_DECOMMISSIONED:
                        printf("Ship is decommissioned\n");
                        break;
                    case ON_MODERNISATION:
                        printf("Ship on modernisation\n");
                        break;
                    case UNDER_REPAIR:
                        printf("Ship is under repair\n");
                        break;
                    case NO_INFORMATION:
                        break;
                }
            printf("\n\n\n");
        }
    }
}

void delete_all(ship **ships, bool *flags, ship *pattern, size_t size) {
    if (flags)
        free(flags);
    if (pattern)
        free(pattern);
    if (ships)
    {
        for (size_t i = 0; i < size; i++)
            if (ships[i])
                free(ships[i]);
        free(ships);
    }
}