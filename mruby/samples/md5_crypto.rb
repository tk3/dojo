

def my_base64_encode(s)
  base64_tbl = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
  base64_tbl = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

  bit_string = s.unpack("B*")[0]
  remainder = bit_string.size % 6
  if 0 < remainder
    bit_string += "0" * (6 - remainder)
  end

  base64 = ""
  0.step(bit_string.length - 1, 6) do |n|
    item = bit_string[n, 6]
    tbl_index = ["00" + item].pack("B*").unpack("c")[0]
    base64 << base64_tbl[tbl_index.to_i]
  end

  remainder = base64.length % 4
  if 0 < remainder
    base64 += "=" * (4 - remainder)
  end

  base64
end

s = 'user02:$apr1$7EkYqIlu$zP0IETYrGdxLUFGzyvRQs1'

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

password = "foo"

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
  i >>= 1
end

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

puts Base64::encode(final)
puts my_base64_encode(final)

