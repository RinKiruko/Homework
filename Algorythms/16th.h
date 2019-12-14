#ifndef _16TH_H
#define _16TH_H

#include "structures.h"

void reversePartition(dynamicArr* array, int leftIndex, int rightIndex);
void reverseHoareSorting(dynamicArr* array, int leftIndex, int rightIndex);

void hoareSorting(dynamicArr* array, int leftIndex, int rightIndex, int *counter);
int partition(dynamicArr* array, int leftIndex, int rightIndex, int *counter);

dynamicArr generateSlowTestCase(int size);

int laba16();

#endif /* 16TH_H */

