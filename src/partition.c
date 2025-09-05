#include <partition.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_partition(struct partition *p, int capacity)
{
    pthread_mutex_init(&p->lock, NULL);
    p->next = 0;
    p->size = 0;
    p->capacity = capacity;
    p->pairs = (struct pair *)malloc(capacity * sizeof(struct pair));
}

int add_pair(struct partition *p, struct pair *new_pair)
{
    pthread_mutex_lock(&p->lock);
    if (p->size < p->capacity)
    {
        p->pairs[p->size++] = *new_pair;
        pthread_mutex_unlock(&p->lock);
        return 0; // Success
    }
    struct pair *new_pairs = (struct pair *)malloc(p->capacity * 2 * sizeof(struct pair));
    if (new_pairs)
    {
        memcpy(new_pairs, p->pairs, p->size * sizeof(struct pair));
        free(p->pairs);
        p->pairs = new_pairs;
        p->capacity *= 2;
        p->pairs[p->size++] = *new_pair;
        pthread_mutex_unlock(&p->lock);
        return 0; // Success
    }
    perror("Failed to resize partition");
    pthread_mutex_unlock(&p->lock);
    return -1; // Failure
}

void free_partition(struct partition *p)
{
    if (p->pairs != NULL)
    {
        for (int i = 0; i < p->size; i++)
        {
            free_pair(&p->pairs[i]);
        }
        pthread_mutex_destroy(&p->lock);
        free(p->pairs);
        p->pairs = NULL;
    }
}

void print_partition(struct partition *p)
{
    pthread_mutex_lock(&p->lock);
    for (int i = 0; i < p->size; i++)
    {
        print_pair(&p->pairs[i]);
        printf(" :|: ");
    }
    printf("\n");
    pthread_mutex_unlock(&p->lock);
}

void sort_partition(struct partition *p)
{
    pthread_mutex_lock(&p->lock);
    struct pair temp;
    for (int i = 1; i < p->size; ++i)
    {
        int j = i;
        while (j > 0)
        {
            if (pair_cmp(&p->pairs[j], &p->pairs[j - 1]) < 0)
            {
                temp = p->pairs[j];
                p->pairs[j] = p->pairs[j - 1];
                p->pairs[j - 1] = temp;
                j -= 1;
            }
            else
            {
                break;
            }
        }
    }
    pthread_mutex_unlock(&p->lock);
}

char *get_next(struct partition *p, char *key)
{
    char *value = NULL;
    pthread_mutex_lock(&p->lock);
    if ((p->next < p->size) && (strcmp(key, p->pairs[p->next].key) == 0))
    {
        value = p->pairs[p->next].value;
        p->next += 1;
    }
    pthread_mutex_unlock(&p->lock);
    return value;
}