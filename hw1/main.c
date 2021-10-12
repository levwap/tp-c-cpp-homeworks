#include <stdio.h>
#include "ship.h"



//zamenit stdchr na shtucku c samenoi \n na 0
// naiti bug c ne ochistkoy (skoree vsego s pomoshu testov)
// ne rabotaet proga na 3 korablyah

int main() {
    ship **ships = NULL;
    bool *flags = NULL;
    ship *pattern = NULL;
    size_t size = 0;

    size = create_ships(&ships);
    if (size)
        if (create_ship(&pattern))
            if (filter(&ships, size, &flags, pattern))
                print_ships_after_filter(ships, size, flags);
    delete(ships, flags, pattern, size);


    return 0;
}
