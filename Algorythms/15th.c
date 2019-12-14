#include "15th.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "randomArray.h"
#include <math.h>

void checkInversion(dynamicArr* array, int* Counter, int leftIndex, int rightIndex) {
    if (rightIndex - leftIndex == 2) {
        if (array->ptr[leftIndex] > array->ptr[leftIndex + 1]) {
            int temp = array->ptr[leftIndex];
            array->ptr[leftIndex] = array->ptr[leftIndex + 1];
            array->ptr[leftIndex + 1] = temp;
            *Counter += 1;
        }
    } else if (rightIndex - leftIndex == 1) {
        return;
    } else {

        // Left part
        checkInversion(array, Counter, leftIndex, leftIndex + (rightIndex - leftIndex) / 2);

        // Right Part
        checkInversion(array, Counter, leftIndex + (rightIndex - leftIndex) / 2, rightIndex);

        checking(array, Counter, leftIndex, leftIndex + (rightIndex - leftIndex) / 2, rightIndex);
    }
}

void checking(dynamicArr* array, int* Counter, int leftIndex, int middle, int rightIndex) {
    int i = 0, j = 0, k = 0;

    int temps[rightIndex - leftIndex];
    int startLess;

    while (leftIndex + i < middle || middle + j < rightIndex) {
        if (leftIndex + i == middle) {
            temps[k] = array->ptr[middle + j];
            k++;

            j++;
        } else if (middle + j == rightIndex) {
            temps[k] = array->ptr[leftIndex + i];
            k++;

            i++;
        } else if (array->ptr[leftIndex + i] < array->ptr[middle + j]) {
            temps[k] = array->ptr[leftIndex + i];
            k++;

            i++;
        } else {
            *Counter += middle - (leftIndex + i);
            temps[k] = array->ptr[middle + j];
            k++;

            j++;
        }
    }
    for (int i = 0; i < rightIndex - leftIndex; i++) {
        array->ptr[leftIndex + i] = temps[i];
    }
}

int laba15() {
    int array_size = 10000;
    dynamicArr randomArray = initRandomArray(array_size, (int) pow((double) 10, (double) 9));
    dynamicArr copy = initArr(array_size);

    for (int i = 0; i < randomArray.len; i++) {
        push(&copy, i, randomArray.ptr[i]);
    }

    int counter = 0;
    clock_t start = clock();
    checkInversion(&randomArray, &counter, 0, randomArray.len);
    printf("%lf milliseconds\n", (double) (clock() - start) / 1000);

    printf(" by_merging: %d \n", counter);

    int on2_counter = 0;
    for (int i = 0; i < copy.len; i++) {
        for (int j = i + 1; j < copy.len; j++) {
            if (copy.ptr[i] > copy.ptr[j]) {
                on2_counter++;
            }
        }
    }
    printf(" by_on2: %d \n", on2_counter);

    return (EXIT_SUCCESS);
}