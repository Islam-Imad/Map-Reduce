#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mr_sys.h"
#include "mappers.h"
#include "reducers.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <operation> [files...]\n", argv[0]);
        printf("Operations:\n");
        printf("  wordcount   - Count words in files\n");
        printf("  numbersum   - Sum all numbers in files\n");
        printf("  departmax   - Find maximum value per department\n");
        printf("  average     - Calculate average per category\n");
        return 1;
    }

    struct MapReduceSystem mr_sys;

    if (strcmp(argv[1], "wordcount") == 0)
    {
        init_MapReduceSystem(&mr_sys, word_count_mapper, word_count_reducer, MR_DefaultHashPartition, 1, 1, 1);
        printf("Running Word Count MapReduce...\n");
    }
    else if (strcmp(argv[1], "numbersum") == 0)
    {
        init_MapReduceSystem(&mr_sys, number_sum_mapper, number_sum_reducer, MR_DefaultHashPartition, 1, 1, 1);
        printf("Running Number Sum MapReduce...\n");
    }
    else if (strcmp(argv[1], "departmax") == 0)
    {
        init_MapReduceSystem(&mr_sys, department_max_mapper, department_max_reducer, MR_DefaultHashPartition, 1, 1, 1);
        printf("Running Department Maximum MapReduce...\n");
    }
    else if (strcmp(argv[1], "average") == 0)
    {
        init_MapReduceSystem(&mr_sys, average_mapper, average_reducer, MR_DefaultHashPartition, 1, 1, 1);
        printf("Running Average Calculation MapReduce...\n");
    }
    else
    {
        printf("Unknown operation: %s\n", argv[1]);
        return 1;
    }

    // Shift arguments to skip the operation name
    MR_Run(&mr_sys, argc - 1, argv + 1);
    destroy_MapReduceSystem(&mr_sys);
    return 0;
}
