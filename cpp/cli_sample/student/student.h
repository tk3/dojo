#ifndef STUDENT_H
#define STUDENT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char name[128];
    int  age;
    char *comment;
} Student;

Student *alloc_student(void);
char *get_name_student(Student *student);
int get_age_student(Student *student);
char *get_comment_student(Student *student);
int set_name_student(Student *student, char *name);
int set_age_student(Student *student, int age);
int set_comment_student(Student *student, char *comment);
int print_student(Student *student);
void free_student(Student *student);

#ifdef __cplusplus
}
#endif

#endif