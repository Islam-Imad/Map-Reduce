#include <stdio.h>
#include <string.h>
#include "mappers.h"

void word_count_mapper(struct MapReduceSystem *mr_sys, char *file_name)
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
            MR_Emit(mr_sys, token, "1");
            token = strtok(NULL, delimiter);
        }
    }
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