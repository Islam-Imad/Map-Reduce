#ifndef REDUCERS_H
#define REDUCERS_H

#include "mr_sys.h"
void word_count_reducer(struct MapReduceSystem *mr_sys, char *key, int partition_number);
void number_sum_reducer(struct MapReduceSystem *mr_sys, char *key, int partition_number);
void department_max_reducer(struct MapReduceSystem *mr_sys, char *key, int partition_number);
void average_reducer(struct MapReduceSystem *mr_sys, char *key, int partition_number);

#endif /* REDUCERS_H */