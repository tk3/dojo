
def int_to_bitstring(n)
  v = ''
  n.each do |i|
    v << "%08b" % i
  end
  v
end

def bitstring_to_int(s)
  v = 0
  s.each_char do |i|
    v <<= 1
    if i == "1"
      v += 1
    end
  end
  v
end

def my_base64_encode(s)
  base64_tbl = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

  bit_string = int_to_bitstring(s.unpack("C*"))
  remainder = bit_string.size % 6
  if 0 < remainder
    bit_string += "0" * (6 - remainder)
  end

  base64 = ""
  0.step(bit_string.length - 1, 6) do |n|
    item = bit_string[n, 6]
    tbl_index = bitstring_to_int("00" + item)
    base64 << base64_tbl[tbl_index]
  end

  base64
end

s = 'user02:$apr1$7EkYqIlu$zP0IETYrGdxLUFGzyvRQs1'
s = 'user01:$apr1$K5S1J1Cw$bT/200cBbpdVb6Hp8vu3W.'

p = s.split(":")

user = p[0]

if p[1] =~ /(\$.+\$)(.+)\$(.+)/
  key = $1
  salt = $2
  hash = $3
end

puts "user: #{user}"
puts "key: #{key}"
puts "salt: #{salt}"
puts "hash: #{hash}"

password = "user01"

# hash #1
h1 = Digest::MD5.new
h1.update(password)
h1.update(key)
h1.update(salt)

# hash #2
h2 = Digest::MD5.new
h2.update(password)
h2.update(salt)
h2.update(password)
final = h2.digest

i = password.length
while 0 < i
  if i < 16
    h1.update(final[0, i])
  else
    h1.update(final)
  end
  i -= 16
end

i = password.length
while 0 < i
  if i & 1 == 1
    h1.update("\0")
  else
    h1.update(password[0])
  end
puts i
  i >>= 1
end
final = h1.digest

1000.times do |i|
  h = Digest::MD5.new

  if i & 1 == 1
    h.update(password)
  else
    h.update(final)
  end

  if i % 3 > 0
    h.update(salt)
  end

  if i % 7 > 0
    h.update(password)
  end

  if i & 1 == 1
    h.update(final)
  else
    h.update(password)
  end

  final = h.digest
end

puts my_base64_encode(final)

