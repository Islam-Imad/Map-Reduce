#ifndef PARTITION_H
#define PARTITION_H

#include <pair.h>

struct partition
{
    int next;
    int size;
    int capacity;
    struct pair *pairs;
};

void init_partition(struct partition *p, int capacity);

int add_pair(struct partition *p, struct pair *new_pair);

void free_partition(struct partition *p);

void print_partition(const struct partition *p);

void sort_partition(struct partition *p);

char *get_next(struct partition *p, char *key);

#endif /* PARTITION_H */