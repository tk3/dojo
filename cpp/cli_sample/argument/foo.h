#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Runtime::InteropServices;

public ref class Foo
{
private:

public:
//    Foo();
//    ~Foo();
//    !Foo();

    static int TestInt(... array<Int32>^ arr);
    static int TestString(... array<String^>^ arr);
    static int TestObject(... array<Object^>^ arr);
    static int TestArrayList(ArrayList^ arr);
    static int TestHashtable(Hashtable^ ht);
};

