#ifndef PAIR_H
#define PAIR_H

struct pair
{
    char *key;
    char *value;
};

void init_pair(struct pair *p, const char *key, const char *value);
void free_pair(struct pair *p);
void print_pair(struct pair *p);
int pair_cmp(const struct pair *pair_a, const struct pair *pair_b);

#endif /* PAIR_H */