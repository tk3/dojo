#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student *alloc_student(void)
{
    Student *student_new;

    student_new = (Student *)malloc(sizeof(Student));

    student_new->name[0] = '\0';
    student_new->age     = 0;
    student_new->comment = NULL;

    return student_new;
}

char *get_name_student(Student *student)
{
    return student->name;
}

int get_age_student(Student *student)
{
    return student->age;
}

char *get_comment_student(Student *student)
{
    return student->comment;
}

int set_name_student(Student *student, char *name)
{
    strcpy(student->name, name);

    return 0;
}

int set_age_student(Student *student, int age)
{
    student->age = age;

    return 0;
}

int set_comment_student(Student *student, char *comment)
{
    char *comment_new = NULL;

    comment_new = (char *)malloc(strlen(comment) + 1);
    if (!comment_new)    return -1;
    strcpy(comment_new, comment);

    if (student->comment) {
        free(student->comment);
    }

    student->comment = comment_new;

    return 0;
}

int print_student(Student *student)
{
    printf("C> Studen.name = %s\n", student->name);
    printf("C> Studen.age = %d\n", student->age);
    printf("C> Studen.comment = %s\n", student->comment ? student->comment : "(null)");

    return 0;
}

void free_student(Student *student)
{
    free(student);
}
