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

int Foo::TestInt(... array<Int32>^ arr)
{
    int sum = 0;
    int n = arr->GetLength(0);

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    return sum;
}

int Foo::TestString(... array<String^>^ arr)
{
    int n = arr->GetLength(0);

    for (int i = 0; i < n; i++) {
        IntPtr ptr;

        ptr = Marshal::StringToHGlobalAnsi(arr[i]);

        cout << "TestString [" << i << "]: " << (char *)ptr.ToPointer() << endl; 

        Marshal::FreeHGlobal(ptr);
    }

    return 0;
}

int Foo::TestObject(... array<Object^>^ arr)
{

    return 0;
}
