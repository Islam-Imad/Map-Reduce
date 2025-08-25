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