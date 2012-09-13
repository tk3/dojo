#pragma once

using namespace System;

namespace MyDojo
{
    public ref class StudentWrapper
    {
    private:
        Student *obj;
       
    public:
        StudentWrapper();
        ~StudentWrapper();

        void Name(String^ name);
        String^ Name();
        void Age(int age);
        int Age();
        void Comment(String^ comment);
        String^ Comment();

        void Print(void);
    };
}
