#include <stdlib.h>

#include "randomArray.h"
#include "structures.h"

dynamicArr initRandomArray(int n, int max_num) {

    dynamicArr arr = initArr(n);

    for (int i = 0; i < n; i++) {
        push(&arr, i, rand() % max_num);
    }

    return arr;
}