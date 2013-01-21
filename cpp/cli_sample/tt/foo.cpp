#include <iostream>

#include "foo.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;

Foo::Foo()
{
    cout << "Foo> StudentWrapper#constructor\n";
}

Foo::~Foo()
{
    cout << "Foo> StudentWrapper#constructor\n";
}

Foo::!Foo()
{
    cout << "Foo> StudentWrapper#constructor\n";
}

void Foo::Func(String ^s)
{
}

