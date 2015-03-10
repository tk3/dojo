
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

def encode64(s)
  permutate_tbl = [0, 3, 6, 9, 12, 14, 1, 4, 7, 10, 13, 15, 2, 5, 8, 11]

  tmp1 = Array.new(16)
  s.unpack("C*").each_with_index do |v, i|
    tmp1[permutate_tbl[i]] = v
  end

  bit_string = int_to_bitstring(tmp1)
puts bit_string
  remainder = bit_string.size % 6
  if 0 < remainder
    bit_string += "0" * (6 - remainder)
  end

  ascii_tbl = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
  r = ""
  0.step(bit_string.length - 1, 6) do |n|
    item = bit_string[n, 6]
    tbl_index = bitstring_to_int("00" + item)
    r << ascii_tbl[tbl_index]
  end

  r
end

def md5_crypto(password, hashed_hpassword)
  return ""  unless hashed_hpassword =~ /(\$.+\$)(.+)\$(.+)/
  key = $1
  salt = $2
  hash = $3

  puts "key: #{key}"
  puts "salt: #{salt}"
  puts "hash: #{hash}"

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

  encode64(final)
end

s = 'user02:$apr1$7EkYqIlu$zP0IETYrGdxLUFGzyvRQs1'
s = 'user01:$apr1$K5S1J1Cw$bT/200cBbpdVb6Hp8vu3W.'

p = s.split(":")

user = p[0]

puts md5_crypto("user01", p[1])
