#include <stdio.h>
#include <mr_sys.h>
#include <stdlib.h>
#include <string.h>
#include <partition.h>

int MR_DefaultHashPartition(char *key, int num_partitions)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *key++) != '\0')
    {
        hash = hash * 33 + c;
    }
    return hash % num_partitions;
}

void init_MapReduceSystem(struct MapReduceSystem *mr_sys, Mapper map_func, Reducer reduce_func, Partitioner partition_func, int num_partitions)
{
    mr_sys->partitions = (struct partition *)malloc(num_partitions * sizeof(struct partition));
    for (int i = 0; i < num_partitions; ++i)
    {
        init_partition(&mr_sys->partitions[i], 8);
    }
    mr_sys->num_partitions = num_partitions;
    mr_sys->maper = map_func;
    mr_sys->reducer = reduce_func;
    mr_sys->partitioner = partition_func;
}

void destroy_MapReduceSystem(struct MapReduceSystem *mr_sys)
{
    for (int i = 0; i < mr_sys->num_partitions; ++i)
    {
        free_partition(&mr_sys->partitions[i]);
    }
    free(mr_sys->partitions);
}

void MR_Run(struct MapReduceSystem *mr_sys, char *file_name)
{
    mr_sys->maper(mr_sys, file_name);
    for (int i = 0; i < mr_sys->num_partitions; ++i)
    {
        sort_partition(&mr_sys->partitions[i]);
    }
    for (int i = 0; i < mr_sys->num_partitions; ++i)
    {
        MR_BurnPartition(mr_sys, i);
    }
}

void MR_Emit(struct MapReduceSystem *mr_sys, char *key, char *value)
{
    int partition = mr_sys->partitioner(key, mr_sys->num_partitions);
    struct pair new_pair;
    init_pair(&new_pair, key, value);
    add_pair(&mr_sys->partitions[partition], &new_pair);
}

char *MR_Get(struct MapReduceSystem *mr_sys, char *key, int partition_number)
{
    struct partition *current_partiton = &mr_sys->partitions[partition_number];
    return get_next(current_partiton, key);
}

void MR_BurnPartition(struct MapReduceSystem *mr_sys, int partition_number)
{
    struct partition *current_partiton = &mr_sys->partitions[partition_number];
    while (current_partiton->next < current_partiton->size)
    {
        mr_sys->reducer(mr_sys, current_partiton->pairs[current_partiton->next].key, partition_number);
    }
}