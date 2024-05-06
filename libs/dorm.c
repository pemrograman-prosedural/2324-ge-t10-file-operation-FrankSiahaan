#include "dorm.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Define the complete function definition here. Be sure to enlist the prototype of each function
 * defined here in the corresponding header file.
 *
 */
struct dorm_t create_dorm(char *_name, unsigned short _capacity, enum gender_t _gender)
{
    struct dorm_t dorm;
    strcpy(dorm.name, _name);
    dorm.capacity = _capacity;
    dorm.gender = _gender;
    dorm.residents_num = 0;

    return dorm;
}

void print_dorm(struct dorm_t *_dorm, int jumlah)
{
    for (int i = 0; i < jumlah; i++)
    {
        if (_dorm[i].gender == 0)
        {
            printf("%s|%d|male\n", _dorm[i].name, _dorm[i].capacity);
        }else if (_dorm[i].gender == 1) {
            printf("%s|%d|female\n", _dorm[i].name, _dorm[i].capacity);
        }
        
    }
    
}

void print_dorm_detail(struct dorm_t *_dorm, int jumlah)
{
    for (int i = 0; i < jumlah; i++)
    {
        if (_dorm[i].gender == 0)
        {
            printf("%s|%d|male|%d\n", _dorm[i].name, _dorm[i].capacity, _dorm[i].residents_num);
        }else if (_dorm[i].gender == 1) {
            printf("%s|%d|female|%d\n", _dorm[i].name, _dorm[i].capacity, _dorm[i].residents_num);
        }
        
    }
    
}