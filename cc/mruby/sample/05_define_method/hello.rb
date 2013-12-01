
f = Foo.new

puts "class: #{f.class}"

puts f.add(10, 20)

puts f.add(10)    # => ArgumentError

