//K-ая статистика

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structures.h"
#include "functions.h"
#include "17th.h"

void mergeArray(array_of_integer *array, int leftIndex, int middle, int rightIndex);

void sortArray(array_of_integer *array, int leftIndex, int rightIndex) {
    if (rightIndex - leftIndex == 2) {
        if (array->elements[leftIndex] > array->elements[rightIndex - 1]) {
            swap(&(array->elements[leftIndex]), &(array->elements[rightIndex - 1]));
        }
    } else if (rightIndex - leftIndex == 1) {
        return;
    } else {

        // Left part
        sortArray(array, leftIndex, leftIndex + (rightIndex - leftIndex) / 2);

        // Right Part
        sortArray(array, leftIndex + (rightIndex - leftIndex) / 2, rightIndex);

        // Merging
        mergeArray(array, leftIndex, leftIndex + (rightIndex - leftIndex) / 2, rightIndex);
    }
}

void mergeArray(array_of_integer *array, int leftIndex, int middle, int rightIndex) {
    int i = 0, j = 0, k = 0;

    int temps[rightIndex - leftIndex];

    while (leftIndex + i < middle || middle + j < rightIndex) {
        if (leftIndex + i == middle) {
            temps[k] = array->elements[middle + j];
            k++;

            j++;
        } else if (middle + j == rightIndex) {
            temps[k] = array->elements[leftIndex + i];
            k++;

            i++;
        } else if (array->elements[leftIndex + i] < array->elements[middle + j]) {
            temps[k] = array->elements[leftIndex + i];
            k++;

            i++;
        } else {
            temps[k] = array->elements[middle + j];
            k++;

            j++;
        }
    }

    for (int i = 0; i < rightIndex - leftIndex; i++) {
        array->elements[leftIndex + i] = temps[i];
    }
}

int pickPivot(array_of_integer *array, int leftIndex, int rightIndex);

int quickSelectMedian(array_of_integer *array) {
    if (array->len <= 5) {
        sortArray(array, 0, array->len);
        return array->elements[array->len / 2];
    }
    int pivot = pickPivot(array, 0, array->len);

    array_of_integer lessOrEqual = initArray(), greatOrEqual = initArray();


    for (int i = 0; i < array->len; i++) {
        append((array->elements[i] > pivot) ? &(greatOrEqual) : &(lessOrEqual), array->elements[i]);
    }

    if (lessOrEqual.len >= array->len / 2) {
        free(greatOrEqual.elements);
        return quickSelectMedian(&lessOrEqual);
    } else {
        free(lessOrEqual.elements);
        return quickSelectMedian(&greatOrEqual);
    }
}

int pickPivot(array_of_integer *array, int leftIndex, int rightIndex) {
    if (rightIndex - leftIndex == 5) {
        array_of_integer copyArray = initArray();
        for (int i = leftIndex; i < rightIndex; i++) {
            append(&copyArray, array->elements[i]);
        }
        sortArray(&copyArray, 0, copyArray.len);
        int result = copyArray.elements[copyArray.len / 2];
        free(copyArray.elements);
        return result;
    } else {
        array_of_integer medians = initArray();
        int prevIndex = 0;
        for (int i = 1; i <= array->len; i++) {
            if (i % 5 == 0 || i == array->len) {
                append(&medians, pickPivot(array, prevIndex, i));
                prevIndex = i;
            }
        }

        return quickSelectMedian(&medians);
    }
}

int laba17() {
    int n, k1, k2, A, B, C, a1, a2;
    FILE *input, *output;
    input = fopen("input.txt.txt", "r");

    fscanf(input, "%d", &n);
    fscanf(input, "%d", &k1);
    fscanf(input, "%d", &k2);

    fscanf(input, "%d", &A);
    fscanf(input, "%d", &B);
    fscanf(input, "%d", &C);
    fscanf(input, "%d", &a1);
    fscanf(input, "%d", &a2);

    fclose(input);

    array_of_integer array = initArray();
    int prev_1, prev_2, element;
    prev_1 = a1, prev_2 = a2;
    append(&array, a1);
    append(&array, a2);
    for (int i = 2; i < n; i++) {
        element = A * prev_1 + B * prev_2 + C;
        prev_1 = prev_2;
        prev_2 = element;
        append(&array, element);
    }
    time_t start = clock();
    printf("start\n");

    int median = quickSelectMedian(&array);

    int i = 0, j = n - 1;
    while (i <= j) {
        while (array.elements[i] < median) {
            i++;
        }

        while (array.elements[j] > median) {
            j--;
        }

        if (i >= j) {
            break;
        }
        swap(&(array.elements[i++]), &(array.elements[j++]));
    }

    array_of_integer slicedArray = initArray();

    --k1, --k2; // Cause it's not indexes
    for (int i = k1; i <= k2; i++) {
        append(&slicedArray, array.elements[i]);
    }
    free(array.elements);
    printf("%lf \n", (double) (clock() - start) / 1000);

    sortArray(&slicedArray, 0, slicedArray.len);

    output = fopen("output.txt", "w");
    for (int i = 0; i < slicedArray.len; i++) {
        if (i % 10 == 0) {
            fprintf(output, "\n");
        }
        fprintf(output, "%d ", slicedArray.elements[i]);
    }

    return (EXIT_SUCCESS);
}