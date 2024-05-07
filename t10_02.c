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
    int student_index = 0;
    int dorm_index = 0;
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
            token = strtok(cmd, "#");

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
            else if(strcmp(token, "student-add") == 0) {
                token = strtok(NULL, "#");
                strcpy(id, token);

                token = strtok(NULL, "#");
                strcpy(name, token);

                token = strtok(NULL, "#");
                strcpy(year, token);

                token = strtok(NULL, "#");
                if (strcmp(token, "male") == 0)
                {
                    students[i] = create_student(id, name, year, GENDER_MALE);
                }
                else if (strcmp(token, "female") == 0)
                {
                    students[i] = create_student(id, name, year, GENDER_FEMALE);
                }
                i++;
            }
            else if(strcmp(token, "dorm-add") == 0) {
                token = strtok(NULL, "#");
                strcpy(name, token);

                token = strtok(NULL, "#");
                capacity = atoi(token);

                token = strtok(NULL, "#");
                 if (strcmp(token, "male") == 0)
                {
                    dorms[j] = create_dorm(name, capacity, GENDER_MALE);
                }
                else if (strcmp(token, "female") == 0)
                {
                    dorms[j] = create_dorm(name, capacity, GENDER_FEMALE);
                }
                j++;
            }
            else if (strcmp(token, "assign-student") == 0) {
                token = strtok(NULL, "#");
                strcpy(id, token);

                token = strtok(NULL, "#");
                strcpy(name, token);

                for (int b = 0; b < i; b++)
                {
                    if (strcmp(students[b].id, id) == 0)
                    {
                        student_index = b;
                    }
                }
                for (int f = 0; f < j; f++)
                {
                    if (strcmp(dorms[f].name, name) == 0)
                    {
                        dorm_index = f;
                    }
                }
                assign_student(&students[student_index], &dorms[dorm_index], id, name);
            } 
            else if (strcmp(token, "move-student") == 0){
                token = strtok(NULL, "#");
                strcpy(id, token);

                token = strtok(NULL, "#");
                strcpy(name, token);

                for (int b = 0; b < i; b++)
                {
                    if (strcmp(students[b].id, id) == 0)
                    {
                        student_index = b;
                    }
                }
                for (int f = 0; f < j; f++)
                {
                    if (strcmp(dorms[f].name, name) == 0)
                    {
                        dorm_index = f;
                    }
                }
                if (students[student_index].dorm == NULL)
                {
                    assign_student(&students[student_index], &dorms[dorm_index], id, name);
                } else {
                    for (int b = 0; b < j; b++)
                    {
                        if (strcmp(students[b].dorm->name, dorms[b].name) == 0)
                        {
                            move_student(&students[student_index], &dorms[dorm_index] ,&dorms[b], id, name);
                        }
                }
                

            }
        }}
    }
    free(students);
    free(dorms);
    
    return 0;
}
