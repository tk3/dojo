using System;
using System.Collections;

class Program
{
    static void Main(string[] arg)
    {
        Test01();
        Test02();
        Test03();
        Test04();
        Test05();
    }

    static void Test01()
    {
        Console.WriteLine("TestInt = {0}", Foo.TestInt(1, 2, 3, 4, 5));
        Console.WriteLine("TestInt = {0}", Foo.TestInt());
    }

    static void Test02()
    {
        Foo.TestString("aaa", "bbb", "ccc");
    }

    static void Test03()
    {
        Foo.TestObject(1, "aaa");
    }

    static void Test04()
    {
        ArrayList arr = new ArrayList();
        arr.Add("abcd");
        arr.Add(200);
        arr.Add('p');
        Foo.TestArrayList(arr);
    }

    static void Test05()
    {
        Hashtable ht = new Hashtable();
        ht.Add("one", "100");
        ht.Add("two", "200");
        ht.Add("three", "300");
        ht.Add("four", true);
        Foo.TestHashtable(ht);
    }
}

