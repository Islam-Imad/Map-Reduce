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
        count += 1;
    }
    printf("%s:%d\n", key, count);
}

void number_sum_reducer(struct MapReduceSystem *mr_sys, char *key, int partition_number)
{
    int sum = 0;
    char *value;
    while ((value = MR_Get(mr_sys, key, partition_number)) != NULL)
    {
        sum += atoi(value);
    }
    printf("Total Sum: %d\n", sum);
}

void department_max_reducer(struct MapReduceSystem *mr_sys, char *key, int partition_number)
{
    int max_value = 0;
    char *value;
    int current_value;

    while ((value = MR_Get(mr_sys, key, partition_number)) != NULL)
    {
        current_value = atoi(value);
        if (current_value > max_value)
        {
            max_value = current_value;
        }
    }
    printf("%s maximum: %d\n", key, max_value);
}

void average_reducer(struct MapReduceSystem *mr_sys, char *key, int partition_number)
{
    double sum = 0.0;
    int count = 0;
    char *value;

    while ((value = MR_Get(mr_sys, key, partition_number)) != NULL)
    {
        sum += atof(value);
        count++;
    }

    if (count > 0)
    {
        printf("%s average: %.2f (count: %d)\n", key, sum / count, count);
    }
    else
    {
        printf("%s: no data\n", key);
    }
}
