using System;

class Program
{
    static void Main(string[] arg)
    {
        Foo f = new Foo();

        Console.WriteLine("TestInt = {0}", f.TestInt(1, 2, 3, 4, 5));

        f.TestString("aaa", "bbb", "ccc");

        f.TestObject(1, "aaa");
    }
}

