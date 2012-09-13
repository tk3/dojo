using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using MyDojo;

namespace callStudent
{
    class TestStudent
    {
        static int Main()
        {
            StudentWrapper student01 = new StudentWrapper();

            student01.Name("foo");
            student01.Age(20);
            student01.Comment("Good!");

            student01.Print();


            StudentWrapper student02 = new StudentWrapper();

            student01.Name("bar");
            student01.Age(12);

            System.Console.WriteLine("csharp> Name = " + student02.Name());
            System.Console.WriteLine("csharp> Age = " + student02.Age());
            System.Console.WriteLine("csharp> Comment = " + student02.Comment());

            return 0;
        }
    }
}
