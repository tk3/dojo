
class Base32
  def self.encode(s)
    base32_tbl = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ234567'

    s1 = s.unpack('C*')
    num_pad = 5 - s1.length % 5
    if 0 < num_pad && num_pad < 5
      num_pad.times do |i|
        s1 << 0
      end
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

    if 0 < num_pad && num_pad < 5
      n = ((8 * num_pad) / 5).floor
      base32 = base32.slice(0, base32.length - n) + '=' * n
    end

    base32
  end

  def self.decode(s)
    base32_decode_tbl = {
      'A' => 0,  'B' => 1,  'C' => 2,  'D' => 3,  'E' => 4,
      'F' => 5,  'G' => 6,  'H' => 7,  'I' => 8,  'J' => 9,
      'K' => 10, 'L' => 11, 'M' => 12, 'N' => 13, 'O' => 14,
      'P' => 15, 'Q' => 16, 'R' => 17, 'S' => 18, 'T' => 19,
      'U' => 20, 'V' => 21, 'W' => 22, 'X' => 23, 'Y' => 24,
      'Z' => 25, '2' => 26, '3' => 27, '4' => 28, '5' => 29,
      '6' => 30, '7' => 31 }

    keys = []
    s.length.times do |i|
      if s[i] == '='
        keys << 0
      else
        keys << base32_decode_tbl[s[i]]
      end
    end

    bin = []
    0.step(keys.length - 1, 8) do |i|
      bin << (keys[i] << 3 | (keys[i+1] & 0x1c) >> 2)
      bin << ((keys[i+1] & 0x3) << 6 | keys[i+2] << 1 | (keys[i+3] & 0x10) >> 4)
      bin << ((keys[i+3] & 0xf) << 4 | (keys[i+4] & 0x1e) >> 1)
      bin << ((keys[i+4] & 0x1) << 7 | keys[i+5] << 2 | (keys[i+6] & 0x18) >> 3)
      bin << ((keys[i+6] & 0x7) << 5 | keys[i+7])
    end

    bin.pack('C*')
  end
end

d = [
  'ME======',
  'MFQQ====',
  'MFQWC===',
  'MFQWCYI=',
  'MFQWCYLB',
  'MFQWCYLBME======'
]

#puts Base32.encode 'a'
#puts Base32.encode 'a' * 2
#puts Base32.encode 'a' * 3
#puts Base32.encode 'a' * 4
#puts Base32.encode 'a' * 5
#puts Base32.encode 'a' * 6

puts Base32.decode 'MFQWCYLB'
puts Base32.decode 'MFQWC==='

