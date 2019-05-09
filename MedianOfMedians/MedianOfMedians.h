#ifndef MedianOfMedians_h
#define MedianOfMedians_h

#include <stdbool.h>

//////////////////////////////////////////////////
typedef enum MOMOption {
    MOM_OPTION_NONE = 0,
    
    MOM_OPTION_RANGE = 0x0002,
    MOM_OPTION_PLACE = 0x0004,
    
    MOM_OPTION_RANGE_ALL = 0x0000,
    MOM_OPTION_RANGE_PARTIAL = 0x0002,

    MOM_OPTION_INPLACE = 0x0000,
    MOM_OPTION_NOT_INPLACE = 0x0004
    
} MOM_OPTION_e;

//////////////////////////////////////////////////
int medianOfMedians(int *array, int length, int sizeGroup, int leftIndex, int rightIndex, MOM_OPTION_e option);

#endif
