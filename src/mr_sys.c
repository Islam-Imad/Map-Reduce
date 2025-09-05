#include <stdio.h>
#include <mr_sys.h>
#include <stdlib.h>
#include <string.h>
#include <partition.h>
#include <thread_pool.h>

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

void init_MapReduceSystem(struct MapReduceSystem *mr_sys, Mapper map_func, Reducer reduce_func, Partitioner partition_func, int num_partitions, int num_mappers, int num_reducers)
{
    mr_sys->partitions = (struct partition *)malloc(num_partitions * sizeof(struct partition));
    for (int i = 0; i < num_partitions; ++i)
    {
        init_partition(&mr_sys->partitions[i], 8);
    }
    mr_sys->num_partitions = num_partitions;
    mr_sys->num_mappers = num_mappers;
    mr_sys->num_reducers = num_reducers;
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

void map_task(void *arg)
{
    struct map_task_args *args = (struct map_task_args *)arg;
    args->mr_sys->maper(args->mr_sys, args->file_name);
    free(args);
}

void reduce_task(void *arg)
{
    struct reduce_task_args *args = (struct reduce_task_args *)arg;
    MR_BurnPartition(args->mr_sys, args->partition_number);
    free(args);
}

void MR_Run(struct MapReduceSystem *mr_sys, int argc, char *argv[])
{
    struct threads_pool map_pool;
    init_threads_pool(&map_pool, mr_sys->num_mappers, argc - 1);

    for (int i = 1; i < argc; i++)
    {
        struct map_task_args *args = malloc(sizeof(struct map_task_args));
        args->mr_sys = mr_sys;
        args->file_name = argv[i];
        task_t task;
        task.function = map_task;
        task.argument = args;
        add_task(&map_pool, task);
    }
    wait_shutdown_threads_pool(&map_pool);
    struct threads_pool reduce_pool;
    init_threads_pool(&reduce_pool, mr_sys->num_reducers, mr_sys->num_partitions);
    for (int i = 0; i < mr_sys->num_partitions; ++i)
    {
        struct reduce_task_args *args = malloc(sizeof(struct reduce_task_args));
        args->mr_sys = mr_sys;
        args->partition_number = i;
        task_t task;
        task.function = reduce_task;
        task.argument = args;
        add_task(&reduce_pool, task);
    }
    wait_shutdown_threads_pool(&reduce_pool);
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
    sort_partition(&mr_sys->partitions[partition_number]);
    struct partition *current_partiton = &mr_sys->partitions[partition_number];
    while (current_partiton->next < current_partiton->size)
    {
        mr_sys->reducer(mr_sys, current_partiton->pairs[current_partiton->next].key, partition_number);
    }
}