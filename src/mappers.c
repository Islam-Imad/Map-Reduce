#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "mappers.h"

/* Helper: strip leading/trailing punctuation in-place.
   Returns pointer to first non-punct char (may be same as s).
   Ensures the returned string is NUL-terminated. */
static char *trim_punct(char *s)
{
    if (!s)
        return s;
    /* trim leading punctuation */
    char *start = s;
    while (*start && ispunct((unsigned char)*start))
        start++;
    /* if everything was punctuation, return empty string */
    if (*start == '\0')
        return start;

    /* trim trailing punctuation */
    char *end = start + strlen(start) - 1;
    while (end >= start && ispunct((unsigned char)*end))
    {
        *end = '\0';
        end--;
    }
    return start;
}

void word_count_mapper(struct MapReduceSystem *mr_sys, char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    char *line = NULL;
    size_t linecap = 0;
    int linelen;
    const char *delim = " \t\r\n";
    while ((linelen = getline(&line, &linecap, file)) != -1)
    {
        char *saveptr = NULL;
        char *token = strtok_r(line, delim, &saveptr);
        while (token != NULL)
        {
            char *word = trim_punct(token);
            if (*word != '\0')
            {
                /* If MR_Emit stores copies of key/value: you may strdup and free.
                   If MR_Emit stores the pointer (takes ownership), DO NOT free.
                   Here we assume MR_Emit copies (common). */
                char *key = strdup(word);
                if (key == NULL)
                {
                    fprintf(stderr, "strdup failed\n");
                    /* decide how to handle: continue or abort */
                }
                else
                {
                    /* emit: value "1" as a string */
                    MR_Emit(mr_sys, key, "1");
                    /* since MR_Emit is assumed to copy, free our duplicate */
                    free(key);
                }
            }
            token = strtok_r(NULL, delim, &saveptr);
        }
    }

    free(line);
    fclose(file);
}

void number_sum_mapper(struct MapReduceSystem *mr_sys, char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    char delimiter[] = " \n";
    char *token;
    char line[4096];
    while (fgets(line, sizeof(line), file))
    {
        token = strtok(line, delimiter);
        while (token != NULL)
        {
            // Emit all numbers with the same key "total" to sum them all
            MR_Emit(mr_sys, "total", token);
            token = strtok(NULL, delimiter);
        }
    }
    fclose(file);
}

void department_max_mapper(struct MapReduceSystem *mr_sys, char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    char line[4096];
    char department[256];
    char value[256];

    while (fgets(line, sizeof(line), file))
    {
        // Parse department and value from each line
        if (sscanf(line, "%s %s", department, value) == 2)
        {
            MR_Emit(mr_sys, department, value);
        }
    }
    fclose(file);
}

void average_mapper(struct MapReduceSystem *mr_sys, char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    char line[4096];
    char category[256];
    char value[256];

    while (fgets(line, sizeof(line), file))
    {
        // Parse category and value from each line
        if (sscanf(line, "%s %s", category, value) == 2)
        {
            MR_Emit(mr_sys, category, value);
        }
    }
    fclose(file);
}