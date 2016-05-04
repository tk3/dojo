#!/usr/bin/env wren

class Foo {
  construct new() {}

  say() {
    return "Hey!"
  }
}

System.print(Foo.new().say())
