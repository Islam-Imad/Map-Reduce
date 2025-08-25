#ifndef PARTITION_H
#define PARTITION_H

#include <pair.h>
#include <pthread.h>
struct partition
{
    int next;
    int size;
    int capacity;
    pthread_mutex_t lock;
    struct pair *pairs;
};

void init_partition(struct partition *p, int capacity);

int add_pair(struct partition *p, struct pair *new_pair);

void free_partition(struct partition *p);

void print_partition(struct partition *p);

void sort_partition(struct partition *p);

char *get_next(struct partition *p, char *key);

#endif /* PARTITION_H */