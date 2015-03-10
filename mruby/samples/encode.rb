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
pp r

  r
end

s = "103686d517ca17809d32ae22e7826727"
a = [s].pack("H*")

puts a
puts encode64(a)

"bT/200cBbpdVb6Hp8vu3W."

