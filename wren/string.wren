#!/usr/bin/env wren

System.print("- - - - -")
System.print("aa")

System.print("- - - - -")
System.print("bb" + "cc")

System.print("- - - - -")
System.print("ddddd".byteCount_)

System.print("- - - - -")
System.print("012345"[2])
System.print("- - - - -")
System.print("012345"[2..4])

System.print("- - - - -")
System.print("abcdef".byteAt_(2))

System.print("- - - - -")
System.print("ABCDEF".iteratorValue(2))

System.print("- - - - -")
var s1 = "あいうえお"
System.print(s1.iterate(0))
System.print(s1.iterate(1))
System.print(s1.iterate(2))
System.print(s1.iterate(3))
System.print(s1.iterate(6))
System.print(s1[3])
System.print(s1[6])

System.print("- - - - -")
System.print(s1.iterateByte_(0))
System.print(s1.iterateByte_(1))
System.print(s1.iterateByte_(2))

