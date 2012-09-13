#include <iostream>

#include "student.h"
#include "StudentWrapper.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;

using namespace MyDojo;

StudentWrapper::StudentWrapper()
{
    cout << "CLI> StudentWrapper#constructor\n";

    obj = alloc_student();
}

StudentWrapper::~StudentWrapper()
{
    cout << "CLI> StudentWrapper#destructor\n";

    free(obj);
}

void StudentWrapper::Name(String^ name)
{
    IntPtr name_ptr;

    name_ptr = Marshal::StringToHGlobalAnsi(name);

    set_name_student(obj, (char *)name_ptr.ToPointer());

    Marshal::FreeHGlobal(name_ptr);
}

String^ StudentWrapper::Name()
{
    return gcnew String(get_name_student(obj));
}

void StudentWrapper::Age(int age)
{
    set_age_student(obj, age);
}

int StudentWrapper::Age()
{
    return get_age_student(obj);
}

void StudentWrapper::Comment(String^ comment)
{
    IntPtr comment_ptr;

    comment_ptr = Marshal::StringToHGlobalAnsi(comment);

    set_comment_student(obj, (char *)comment_ptr.ToPointer());

    Marshal::FreeHGlobal(comment_ptr);
}

String^ StudentWrapper::Comment()
{
    return gcnew String(get_comment_student(obj));
}

void StudentWrapper::Print(void)
{
    print_student(obj);
}
