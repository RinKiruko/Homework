#ifndef DYNAMICARR_H
#define DYNAMICARR_H

typedef struct {
    int len;
    int *elements;
} array_of_integer;

array_of_integer initArray();
void append(array_of_integer *array, int value);

typedef struct {
    int *ptr;
    int len;
    int capacity;
    int __size;
} dynamicArr;

dynamicArr initArr(int n);

dynamicArr getSlice(dynamicArr* arr, int firstIndex, int lastIndex);

void push(dynamicArr* arr, int index, int value);


#endif // DYNAMICARR_H