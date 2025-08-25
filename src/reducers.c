#include <reducers.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void word_count_reducer(struct MapReduceSystem *mr_sys, char *key, int partition_number)
{
    int count = 0;
    char *value;
    while ((value = MR_Get(mr_sys, key, partition_number)) != NULL)
    {
        count += atoi(value);
    }
    printf("%s : %d\n", key, count);
}
