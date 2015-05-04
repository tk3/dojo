
def base32_encode(s)
  base32_tbl = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ234567'

  s1 = s.unpack('C*')
  num_pad = 5 - s1.length % 5
  num_pad.times do |i|
    s1 << 0
  end

  base32 = ''
  0.step(s1.length - 1, 5) do |i|
    base32 << base32_tbl[(s1[i] & 0xf8) >> 3]
    base32 << base32_tbl[(s1[i] & 0x7) << 2 | (s1[i+1] & 0xc0) >> 6]
    base32 << base32_tbl[(s1[i+1] & 0x3e) >> 1]
    base32 << base32_tbl[(s1[i+1] & 0x1) << 4 | (s1[i+2] & 0xf0) >> 4]
    base32 << base32_tbl[(s1[i+2] & 0xf) << 1 | (s1[i+3] & 0x80) >> 7]
    base32 << base32_tbl[(s1[i+3] & 0x7c) >> 2]
    base32 << base32_tbl[(s1[i+3] & 0x3) << 3 | (s1[i+4] & 0xe0) >> 5]
    base32 << base32_tbl[s1[i+4] & 0x1f]
  end

  puts '>>' + base32
  if num_pad > 0
    n = ((8 * num_pad) / 5 ).floor
    base32 = base32.slice(0, base32.length - n) + '=' * n
  end

  base32
end

d = [
  'ME======',
  'MFQQ====',
  'MFQWC===',
  'MFQWCYI=',
  'MFQWCYLB',
  'MFQWCYLBME======'
]

puts base32_encode 'a'
puts base32_encode 'aa'
puts base32_encode 'aaa'
puts base32_encode 'aaaa'
puts base32_encode 'aaaaa'
