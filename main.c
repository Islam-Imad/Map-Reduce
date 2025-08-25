#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mr_sys.h"
#include "mappers.h"
#include "reducers.h"

int main(int argc, char *argv[])
{
    struct MapReduceSystem mr_sys;
    init_MapReduceSystem(&mr_sys, word_count_mapper, word_count_reducer, MR_DefaultHashPartition, 4, 2, 2);
    MR_Run(&mr_sys, argc, argv);
    destroy_MapReduceSystem(&mr_sys);
    return 0;
}
