#include <stdio.h>
#include "14th.h"
#include "structures.h"
#include "randomArray.h"
#include <time.h>


void sortArrayWithPointer(dynamicArr* array, int leftIndex, int rightIndex) {

    if (rightIndex - leftIndex == 2) {
        if (array->ptr[leftIndex] > array->ptr[leftIndex + 1]) {
            int temp = array->ptr[leftIndex];
            array->ptr[leftIndex] = array->ptr[leftIndex + 1];
            array->ptr[leftIndex + 1] = temp;
        }
    } else if (rightIndex - leftIndex == 1) {
        return;
    } else {

        // Left part
        sortArrayWithPointer(array, leftIndex, leftIndex + (rightIndex - leftIndex) / 2);

        // Right Part
        sortArrayWithPointer(array, leftIndex + (rightIndex - leftIndex) / 2, rightIndex);

        // Merging
        mergeArrayWithPointer(array, leftIndex, leftIndex + (rightIndex - leftIndex) / 2, rightIndex);
    }
}

void mergeArrayWithPointer(dynamicArr* array, int leftIndex, int middle, int rightIndex) {
    int i = 0, j = 0, k = 0;

    int temps[rightIndex - leftIndex];

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
            temps[k] = array->ptr[middle + j];
            k++;

            j++;
        }
    }

    for (int i = 0; i < rightIndex - leftIndex; i++) {
        array->ptr[leftIndex + i] = temps[i];
    }
}

int laba14() {
    clock_t begin = clock();
    
    dynamicArr randomArray = initRandomArray(100, 100);

    printf("random array = {");
    for (int i = 0; i < randomArray.len; i++) {
        printf("%d, ", randomArray.ptr[i]);
    }
    printf("}\n");

    printf("sorted array = {");
    //    DynamicArr sortedArray = sortArray(randomArray);
    sortArrayWithPointer(&randomArray, 0, randomArray.len);
    for (int i = 0; i < randomArray.len; i++) {
        printf("%d, ", randomArray.ptr[i]);
    }
    printf("}\n");
    
    clock_t end = clock();
    printf("%lf", (double)(end - begin) / CLOCKS_PER_SEC);

    return 0;
}