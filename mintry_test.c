#include "mintry.h"
//
#include <stdlib.h>

static int test1 () {
    int x = 0;
    TRY (top) {
        THROW (3);
        ++x;
    } CATCH (top, 3) {
        ++x;
        return EXIT_SUCCESS;
    } FINALLY (top) {
        ++x;
    }
    if (x == 3) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

static int test2 () {
    int x = 0;
    TRY (top) {
        THROW (2);
    } CATCH (top, 1) {
        x = 1;
    } CATCH (top, 2) {
        x = 2;
    } CATCH (top, 3) {
        x = 3;
    } CATCHALL (top) {
        x = 4;
    }
    if (x == 2) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

int main () {
    if (EXIT_FAILURE == (test1 ())) {
        return EXIT_FAILURE;
    }
    if (EXIT_FAILURE == (test2 ())) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
