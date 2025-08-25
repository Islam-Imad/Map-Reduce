#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mr_sys.h"
#include "mappers.h"
#include "reducers.h"

int main()
{
    struct MapReduceSystem MR;
    init_MapReduceSystem(&MR, word_count_mapper, word_count_reducer, MR_DefaultHashPartition, 4);
    MR_Run(&MR, "../samples/01.txt");
    destroy_MapReduceSystem(&MR);
    return 0;
}
