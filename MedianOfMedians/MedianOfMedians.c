#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "InsertionSort.h"
#include "MedianOfMedians.h"

//////////////////////////////////////////////////
int medianOfMediansSlave(int *array, int sizeGroup, int leftIndex, int rightIndex);
int medianMOM(int *array, int leftIndex, int rightIndexI);
bool swapMOM(int *array, int indexA, int indexB);

//////////////////////////////////////////////////
//  public
int medianOfMedians(int *array, int length, int sizeGroup, int leftIndex, int rightIndex, MOM_OPTION_e option) {
    // Block illegal parameters.
    if (array == NULL) return INT_MIN;
    if (length <= 0) return INT_MIN;
    if (sizeGroup <= 1) return INT_MIN;
    
    // change to odd number.
    sizeGroup = sizeGroup | 0x00001;
    
    // determine target area.
    if ((MOM_OPTION_RANGE & option) == MOM_OPTION_RANGE_ALL) {
        leftIndex = 0;
        rightIndex = length - 1;
    }
    else {
        if (leftIndex > rightIndex) return INT_MIN;
    }
    
    // if select not-inplace process, create work array.
    if ((MOM_OPTION_PLACE & option) == MOM_OPTION_NOT_INPLACE) {
        int *temp = NULL;
        if ((MOM_OPTION_RANGE & option) == MOM_OPTION_RANGE_ALL) {
            temp = malloc(sizeof(int) * length);
            if (temp == NULL) return -1;
            memcpy(temp, array, sizeof(int) * length);
        }
        else {  // MOM_OPTION_RANGE_PARTIAL
            length = rightIndex - leftIndex + 1;
            temp = malloc(sizeof(int) * length);
            if (temp == NULL) return -1;
            int i = 0;
            for (int j=leftIndex; j<=rightIndex; j++) {
                temp[i] = array[j];
                i++;
            }
            // change target area.
            leftIndex = 0;
            rightIndex = length - 1;
        }
        array = temp;
    }
    
    if ((rightIndex - leftIndex) < sizeGroup) {
        int medianIndex = medianMOM(array, leftIndex, rightIndex);
        int median = array[medianIndex];
        
        // if select not-inplace process, delete work array.
        if ((MOM_OPTION_PLACE & option) == MOM_OPTION_NOT_INPLACE) {
            free(array);
        }
        return median;
    }
    
    int median = medianOfMediansSlave(array, sizeGroup, leftIndex, rightIndex);
    
    // if select not-inplace process, delete work array.
    if ((MOM_OPTION_PLACE & option) == MOM_OPTION_NOT_INPLACE) {
        free(array);
    }
    
    return median;
}

//////////////////////////////////////////////////
//  private
int medianOfMediansSlave(int *array, int sizeGroup, int leftIndex, int rightIndex) {
    if ((rightIndex - leftIndex) < sizeGroup) {
        int medianIndex = medianMOM(array, leftIndex, rightIndex);
        int median = array[medianIndex];
        return median;
    }

    int storeIndex = leftIndex;
    for (int i=leftIndex; i<=rightIndex; i+=sizeGroup) {
        int subRightIndex = i + sizeGroup - 1;
        if (rightIndex < subRightIndex) {
            subRightIndex = rightIndex;
        }
        int medianIndex = medianMOM(array, i, subRightIndex);
        swapMOM(array, storeIndex, medianIndex);
        storeIndex++;
    }

    return medianOfMediansSlave(array, sizeGroup, leftIndex, storeIndex);
}

int medianMOM(int *array, int leftIndex, int rightIndex) {
    insertionSortSimple(&array[leftIndex], (rightIndex - leftIndex + 1), SORT_OPTION_NONE);
    return leftIndex + (rightIndex - leftIndex) / 2;
}

bool swapMOM(int *array, int indexA, int indexB) {
    // Block illegal parameters.
    if (array == NULL) return false;
    
    int temp = array[indexA];
    array[indexA] = array[indexB];
    array[indexB] = temp;
    
    return true;
}

