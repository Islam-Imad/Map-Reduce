#ifndef MR_SYS_H
#define MR_SYS_H

#include <partition.h>

struct MapReduceSystem;

typedef void (*Mapper)(struct MapReduceSystem *mr_sys, char *file_name);
typedef void (*Reducer)(struct MapReduceSystem *mr_sys, char *key, int partition_number);
typedef int (*Partitioner)(char *key, int num_partitions);

struct MapReduceSystem
{
    int num_partitions;
    struct partition *partitions;
    Mapper maper;
    Reducer reducer;
    Partitioner partitioner;
};

int MR_DefaultHashPartition(char *key, int num_partitions);
void init_MapReduceSystem(struct MapReduceSystem *mr_sys, Mapper map_func, Reducer reduce_func, Partitioner partition_func, int num_partitions);
void destroy_MapReduceSystem(struct MapReduceSystem *mr_sys);

void MR_Emit(struct MapReduceSystem *mr_sys, char *key, char *value);
char *MR_Get(struct MapReduceSystem *mr_sys, char *key, int partition_number);
void MR_BurnPartition(struct MapReduceSystem *mr_sys, int partiton_number);
void MR_Run(struct MapReduceSystem *mr_sys, char *file_name);

#endif /* MR_SYS_H */