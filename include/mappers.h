#ifndef MAPPERS_H
#define MAPPERS_H

#include "mr_sys.h"

void word_count_mapper(struct MapReduceSystem *mr_sys, char *file_name);
void number_sum_mapper(struct MapReduceSystem *mr_sys, char *file_name);
void department_max_mapper(struct MapReduceSystem *mr_sys, char *file_name);
void average_mapper(struct MapReduceSystem *mr_sys, char *file_name);

#endif /* MAPPERS_H */