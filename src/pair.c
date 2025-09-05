#include <pair.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_pair(struct pair *p, const char *key, const char *value)
{
    p->key = strdup(key);
    p->value = strdup(value);
}

void free_pair(struct pair *p)
{
    free(p->key);
    free(p->value);
}

void print_pair(struct pair *p)
{
    printf("Key: %s, Value: %s ", p->key, p->value);
}

int pair_cmp(const struct pair *pair_a, const struct pair *pair_b)
{
    return strcmp(pair_a->key, pair_b->key);
}
