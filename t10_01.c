// 12S23016 - Frank Niroy Siahaan
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./libs/dorm.h"
#include "./libs/student.h"

int main(int _argc, char **_argv)
{
    struct student_t *students = malloc(12 * sizeof(struct student_t));
    struct dorm_t *dorms = malloc(12 * sizeof(struct dorm_t));
    char buffer[100];
    char *token;
    char name[255];
    char id[255];
    char year[255];
    int i = 0;
    int j = 0;
    char named[255];
    int capacity;
    char cmd[255];
    
    FILE *filestd;
    filestd = fopen("./storage/student-repository.txt", "r");
    while (fgets(buffer, 100 , filestd) != NULL)
    {
        token = strtok(buffer, "|");
        strcpy(id, token);

        token = strtok(NULL, "|");
        strcpy(name, token);

        token = strtok(NULL, "|");
        strcpy(year, token);

        token = strtok(NULL, "|");
        if (strcmp(token, "male\n") == 0)
        {
            students[i] = create_student(id, name, year, GENDER_MALE);
        } else if (strcmp(token, "female\n") == 0)
        {
            students[i] = create_student(id, name, year, GENDER_FEMALE);
        }
        i++;
    }
    fclose(filestd);

    FILE *filedrm;
    filedrm = fopen("./storage/dorm-repository.txt", "r");
    while (fgets(buffer, 100 , filedrm) != NULL)
    {
        token = strtok(buffer, "|");
        strcpy(named, token);

        token = strtok(NULL, "|");
        capacity = atoi(token);

        token = strtok(NULL, "|");
        if (strcmp(token, "male\n") == 0)
        {
            dorms[j] = create_dorm(named, capacity, GENDER_MALE);
        } else if (strcmp(token, "female\n") == 0)
        {
            dorms[j] = create_dorm(named, capacity, GENDER_FEMALE);
        }
        j++;
    }
    fclose(filedrm);
    
    while (1)
    {
        fgets(cmd, sizeof(cmd), stdin);    
      
        if (cmd[strlen(cmd) - 1] == '\n' || cmd[strlen(cmd) - 1] == '\r')
        {
            cmd[strlen(cmd) - 1] = '\0';
        }
        if(strcmp(cmd, "---") == 0)
        {
            break;
        }
        else
        {
            if (strcmp(cmd, "dorm-print-all-detail") == 0)
            {
                print_dorm_detail(dorms, j);
            }
            else if(strcmp(cmd, "student-print-all-detail") == 0) 
            {
                print_student_detail(students, i);
            }
            else if (strcmp(cmd, "student-print-all") == 0)
            {
                print_student(students, i);
            }
            else if(strcmp(cmd, "dorm-print-all") == 0) {
                print_dorm(dorms, j);
            }
            
        }
        }

    free(students);
    free(dorms);

    return 0;
}
