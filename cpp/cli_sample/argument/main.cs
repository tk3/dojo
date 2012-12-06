using System;
using System.Collections;

class Program
{
    static void Main(string[] arg)
    {
        Console.WriteLine("TestInt = {0}", Foo.TestInt(1, 2, 3, 4, 5));
        Console.WriteLine("TestInt = {0}", Foo.TestInt());

        Foo.TestString("aaa", "bbb", "ccc");

        Foo.TestObject(1, "aaa");

        ArrayList arr = new ArrayList();
        arr.Add("abcd");
        arr.Add(200);
        arr.Add('p');
        Foo.TestArrayList(arr);

        Hashtable ht = new Hashtable();
        ht.Add("one", "100");
        ht.Add("two", "200");
        ht.Add("three", "300");
        Foo.TestHashtable(ht);
    }
}

