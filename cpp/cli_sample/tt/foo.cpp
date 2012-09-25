#include "foo.h"
#include <iostream>

using namespace std;

Foo::Foo()
{
    return;
}

Foo::~Foo()
{
    this->!Foo();
}

Foo::!Foo()
{
    return;
}

void Foo::Sample(String^ s)
{
    IntPtr ptr;

    ptr = Marshal::StringToHGlobalAnsi(s);

    cout << "sample: " << (char *)ptr.ToPointer();

    Marshal::FreeHGlobal(ptr);
}
