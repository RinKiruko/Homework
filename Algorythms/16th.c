#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "randomArray.h"
#include "functions.h"
#include <time.h>
#include "16th.h"

void hoareSorting(dynamicArr* array, int leftIndex, int rightIndex, int *counter) {
    int delimeter = partition(array, leftIndex, rightIndex, counter);
    if (leftIndex < rightIndex) {
        hoareSorting(array, leftIndex, delimeter, counter);
        hoareSorting(array, delimeter + 1, rightIndex, counter);
    }
}

int partition(dynamicArr* array, int leftIndex, int rightIndex, int *counter) {
    int sliceLen = rightIndex - leftIndex;
    if (sliceLen < 2) {
        return leftIndex;
    } else if (sliceLen == 2) {
        if (array->ptr[leftIndex] > array->ptr[leftIndex + 1]) {
            *counter += 1;
            swap(&(array->ptr[leftIndex]), &(array->ptr[leftIndex + 1]));
        }
        *counter += 1;
        return leftIndex;
    }

    int i = leftIndex, j = rightIndex - 1;
    int middleElement = array->ptr[leftIndex + (rightIndex - leftIndex) / 2];

    while (i <= j) {
        while (array->ptr[i] < middleElement) {
            *counter += 1;
            i++;
        }
        *counter += 1;

        while (array->ptr[j] > middleElement) {
            *counter += 1;
            j--;
        }
        *counter += 1;

        if (i >= j) {
            break;
        }
        if (array->ptr[i] == array->ptr[j]) {
            *counter += 1;
            i++;
        } else {
            swap(&(array->ptr[i]), &(array->ptr[j]));
            *counter += 1;
        }

    }
    return j;
}

void fillArray(dynamicArr *array, int leftIndex, int rightIndex) {
    int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;
    if ((rightIndex - leftIndex) > 3) {
        fillArray(array, leftIndex, middleIndex);
        fillArray(array, middleIndex, rightIndex);
    } else if ((rightIndex - leftIndex) == 2) {
        swap(&(array->ptr[leftIndex]), &(array->ptr[leftIndex + 1]));
        return;
    }

    int *max;
    max = &(array->ptr[leftIndex]);
    for (int i = leftIndex; i < rightIndex; i++) {
        if (array->ptr[i] > *max) {
            max = &(array->ptr[i]);
        }
    }
    swap(max, &(array->ptr[middleIndex]));
    
}

dynamicArr generateSlowTestCase(int arraySize) {
    dynamicArr array = initArr(arraySize);
    for (int i = 0; i < arraySize; i++) {
        push(&array, i, i + 1);
    }
    fillArray(&array, 0, array.capacity);
    return array;
}

int laba16() {
    int arraySize = 1000000;

    dynamicArr array = generateSlowTestCase(arraySize);
    for (int i = 0; i < array.len; i++) {
        printf("%d\n", array.ptr[i]);
    }

    int counter2 = 0;
    hoareSorting(&array, 0, array.len, &counter2);
    printf("By randomCase: %d \n", counter2);
    free(array.ptr);

}