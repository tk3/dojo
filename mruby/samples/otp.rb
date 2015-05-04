
def generate_otp(key, time, return_digits, crypto)
  if time.length < 16
    time = '0' * (16 - time.length) + time
  end
end

seed = '3132333435363738393031323334353637383930'

to = 0
test_time = 1111111109
time_step = 30

t = (test_time / time_step).floor
packed_time = ['%016X'%t].pack('H*')
packed_seed = [seed].pack('H*')
hash = Digest::HMAC.digest(packed_time, packed_seed, Digest::SHA1)

offset = hash[hash.length - 1].unpack('C')[0] & 0xf

puts bin = 
  ((hash[offset].unpack('C')[0] & 0x7f) << 24) |
  ((hash[offset + 1].unpack('C')[0] & 0xff) << 16) |
  ((hash[offset + 2].unpack('C')[0] & 0xff) << 8) |
  (hash[offset + 3].unpack('C')[0] & 0xff)

otp = bin % (10 ** 8)

puts otp = '%08d'%otp

puts otp == '07081804'
puts otp


#gerate_otp seed, steps, '8', 'hmacsha1'

