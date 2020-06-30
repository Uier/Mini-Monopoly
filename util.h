#include <stdlib.h>

int randint(int mn, int mx) {
    return mn + rand()%(mx-mn+1);
}