
//  [Type.InvokeMember メソッド (System)]
//  http://msdn.microsoft.com/ja-jp/library/bese341c(v=vs.100).aspx
//
//  [Type.AssemblyQualifiedName プロパティ (System)]
//  http://msdn.microsoft.com/ja-jp/library/system.type.assemblyqualifiedname(v=vs.100).aspx

using System;
using System.Reflection;

public class User01
{
    public static void Say()
    {
        Console.WriteLine("I'm user01.");
    }
}

namespace NameRoot
{
    public class Group01
    {
        class User02
        {
            public static void Say()
            {
                Console.WriteLine("I'm user02.");
            }
        }
    }
}

public class Program02
{
    public static void Say()
    {
        Console.WriteLine("I'm Program02.");
    }

    public class User03
    {
        public static void Say()
        {
            Console.WriteLine("I'm user03.");
        }
    }

    static void Main()
    {
        Type t1 = Type.GetType("User01");
        Type t2 = Type.GetType("NameRoot.Group01+User02");
        Type t3 = Type.GetType("Program02");
        Type t4 = Type.GetType("Program02+User03");

        Console.WriteLine("Full name: {0}.", t1.FullName);
        Console.WriteLine("Full name: {0}.", t2.FullName);
        Console.WriteLine("Full name: {0}.", t3.FullName);
        Console.WriteLine("Full name: {0}.", t4.FullName);

        Assembly[] asms = AppDomain.CurrentDomain.GetAssemblies();
        foreach (Assembly a in asms)
            Console.WriteLine(a.FullName);

        t1.InvokeMember("Say",
                BindingFlags.InvokeMethod|BindingFlags.Static|BindingFlags.Public,
                null, null, null);
        t2.InvokeMember("Say",
                BindingFlags.InvokeMethod|BindingFlags.Static|BindingFlags.Public,
                null, null, null);
        t3.InvokeMember("Say",
                BindingFlags.InvokeMethod|BindingFlags.Static|BindingFlags.Public,
                null, null, null);
        t4.InvokeMember("Say",
                BindingFlags.InvokeMethod|BindingFlags.Static|BindingFlags.Public,
                null, null, null);
    }

}

