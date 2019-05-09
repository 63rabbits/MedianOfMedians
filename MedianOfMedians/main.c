#include <unistd.h>
//#define checkMemoryLeak

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "InsertionSort.h"
#include "MedianOfMedians.h"

//////////////////////////////////////////////////
typedef struct Element {
    int value;
} Element_t;

//////////////////////////////////////////////////
void test(void);
Element_t *createElement(int value);
bool destroyElement(Element_t *element);
int comp(void *elementA, void *elementB);
int *intRandNoDudplication(int digit, int length);

//////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    srand((unsigned) time(NULL));
    
#ifdef checkMemoryLeak
    while (true) {
        test();
        sleep(1);
    }
#else
    test();
#endif
    
    return EXIT_SUCCESS;
}

void test() {
    int testCount = 10;
    int subTestCount = 3;
    int numElement = 21;
    int sizeGroup = 5;
    int p30 = numElement * 0.3;
    int p70 = ceil(numElement * 0.7);
    
    int beginOfPartial = 5;
    int endOfPartial = 16;
    
    int array[numElement];
    
    for (int testNo=0; testNo<testCount; testNo++) {
        printf("\n=== [Test #%d] === ", testNo+1);
        
        switch (testNo) {
            case 0:
                printf("Standard\n");
            {
                for (int i=0; i<subTestCount; i++) {
                    printf("input              : ");
                    for (int j=0; j<numElement; j++) {
                        array[j] = rand()%100;
                        if (j == p30) printf("      ");
                        if (j == p70) printf("      ");
                        printf("%02d, ", array[j]);
                    }
                    printf("\n");
                    
                    int median = medianOfMedians(array, numElement, sizeGroup, 0, numElement-1, MOM_OPTION_NONE);
                    if (median == INT_MIN) {
                        printf("error [%s] : could not get the median.\n", __func__);
                        break;
                    }
                    
                    bool check = insertionSortSimple(array, numElement, SORT_OPTION_ASCENDING_ORDER);
                    if (!check) {
                        printf("error [%s] : could not sort.\n", __func__);
                        break;
                    }
                    printf("sort and median(*) : ");
                    for (int j=0; j<numElement; j++) {
                        if (j == p30) printf("<30%%  ");
                        if (j == p70) printf("<70%%  ");
                        if (array[j] == median) {
                            printf("*%02d,", array[j]);
                        }
                        else {
                            printf("%02d, ", array[j]);
                        }
                    }
                    printf("\n");
                    printf("\n");
                }
            }
                break;
            case 1:
                printf("Partial\n");
                printf("begin index = %d\n", beginOfPartial);
                printf("end   index = %d\n", endOfPartial);
                printf("\n");
                for (int i=0; i<subTestCount; i++) {
                    printf("input              : ");
                    for (int j=0; j<numElement; j++) {
                        array[j] = rand()%100;
                        if (j == beginOfPartial) printf("      ");
                        if (j == endOfPartial) printf("      ");
                        printf("%02d, ", array[j]);
                    }
                    printf("\n");
                    
                    int median = medianOfMedians(array, numElement, sizeGroup, beginOfPartial, endOfPartial, MOM_OPTION_RANGE_PARTIAL | MOM_OPTION_NOT_INPLACE);
                    if (median == INT_MIN) {
                        printf("error [%s] : could not get the median.\n", __func__);
                        break;
                    }
                    
                    bool check = insertionSort(array, numElement, beginOfPartial, endOfPartial, SORT_OPTION_RANGE_PARTIAL);
                    if (!check) {
                        printf("error [%s] : could not sort.\n", __func__);
                        break;
                    }
                    printf("sort and median(*) : ");
                    for (int j=0; j<numElement; j++) {
                        if (j == beginOfPartial) printf("      ");
                        if (j == endOfPartial) printf("      ");
                        if ((j >= beginOfPartial) &&
                            (j <= endOfPartial) &&
                            (array[j] == median)) {
                            printf("*%02d,", array[j]);
                        }
                        else {
                            printf("%02d, ", array[j]);
                        }
                    }
                    printf("\n");
                    printf("\n");
                }
                // *************************************
                testNo = INT_MAX - 1;        // stop loop.
                // *************************************
                break;
            default:
                break;
        }
    }
}

Element_t *createElement(int value) {
    Element_t *element = malloc(sizeof(Element_t));
    if (element == NULL) return NULL;
    element->value = value;
    return element;
}

bool destroyElement(Element_t *element) {
    // Block illegal parameters.
    if (element == NULL) return false;
    free(element);
    return true;
}

int comp(void *elementA, void *elementB) {
    Element_t *element1 = elementA;
    Element_t *element2 = elementB;
    return element1->value - element2->value;
}

int *intRandNoDudplication(int digit, int length) {
    int denominator = (int)pow(10, digit);
    if (denominator < length) return NULL;
    int *randTable = calloc(length, sizeof(int));
    if (randTable == NULL) return NULL;
    
    int index = 0;
    while (true) {
        int value = rand() % denominator;
        bool exist = false;
        for (int i=0; i<length; i++) {
            if (randTable[i] == value) {
                exist = true;
                break;
            }
        }
        if (!exist) {
            randTable[index] = value;
            index++;
        }
        if (index >= length) break;
    }
    
    return randTable;
}
