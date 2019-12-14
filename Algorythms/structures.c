#include <stdlib.h>
#include <assert.h>
#include "structures.h"

dynamicArr initArr(int init_n) {
    dynamicArr arr;
    arr.capacity = init_n;
    arr.len = 0;
    arr.__size = init_n * sizeof (int);
    arr.ptr = malloc(arr.__size);


    return arr;
}

array_of_integer initArray() {
    array_of_integer arr;
    arr.len = 0;
    arr.elements = malloc(sizeof (int));
    
    return arr;
}
void append(array_of_integer *array, int value) {
    array->elements = realloc(array->elements, sizeof (int)*(++array->len));
    array->elements[array->len - 1] = value;
}

void push(dynamicArr* arrayPointer, int index, int value) {
    if (index > arrayPointer->capacity) {
        arrayPointer->ptr = realloc(arrayPointer->ptr, arrayPointer->__size * 2);
        arrayPointer->capacity += 16;
    }
    if (arrayPointer->len == arrayPointer->capacity) {
        arrayPointer->ptr = realloc(arrayPointer->ptr, arrayPointer->__size * 2);
        arrayPointer->capacity += 16;
    }
    arrayPointer->ptr[index] = value;
    arrayPointer->len++;
}

dynamicArr getSlice(dynamicArr* arr, int firstIndex, int lastIndex) {
    lastIndex = arr->len < lastIndex ? arr->len : lastIndex;

    dynamicArr slicedArr = initArr(lastIndex - firstIndex);

    for (int i = 0; i < lastIndex - firstIndex; i++) {
        push(&slicedArr, i, arr->ptr[firstIndex + i]);
    }

    return slicedArr;
}