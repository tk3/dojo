#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

public ref class Foo
{
private:

public:
    Foo();
    ~Foo();
    !Foo();

    int TestInt(... array<Int32>^ arr);
    int TestString(... array<String^>^ arr);
    int TestObject(... array<Object^>^ arr);
};

