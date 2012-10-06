using System;
using System.Collections;

class Program
{
    static void Main(string[] arg)
    {
        Foo f = new Foo();

        Console.WriteLine("TestInt = {0}", f.TestInt(1, 2, 3, 4, 5));
        Console.WriteLine("TestInt = {0}", f.TestInt());

        f.TestString("aaa", "bbb", "ccc");

        f.TestObject(1, "aaa");

        ArrayList arr = new ArrayList();
        arr.Add("abcd");
        arr.Add(200);
        arr.Add('p');
        f.TestArrayList(arr);

        Hashtable ht = new Hashtable();
        ht.Add("one", "100");
        ht.Add("two", "200");
        ht.Add("three", "300");
        f.TestHashtable(ht);

    }
}

