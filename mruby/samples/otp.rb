
def generate_otp(key, time, return_digits, crypto)
  packed_time = ['%016X'%time].pack('H*')
  packed_key = [key].pack('H*')
  hash = Digest::HMAC.digest(packed_time, packed_key, Digest::SHA1)

  offset = hash[hash.length - 1].unpack('C')[0] & 0xf

  bin = 
    ((hash[offset].unpack('C')[0] & 0x7f) << 24) |
    ((hash[offset + 1].unpack('C')[0] & 0xff) << 16) |
    ((hash[offset + 2].unpack('C')[0] & 0xff) << 8) |
    (hash[offset + 3].unpack('C')[0] & 0xff)

  otp = bin % (10 ** 8)

  otp = '%08d'%otp
end

test_data = [
  {
    :time => 59, :otp_sha1 => '94287082',
  },
  {
    :time => 1111111109, :otp_sha1 => '07081804',
  },
  {
    :time => 1111111111, :otp_sha1 => '14050471',
  },
  {
    :time => 1234567890, :otp_sha1 => '89005924',
  },
  {
    :time => 2000000000, :otp_sha1 => '69279037',
  },
  {
    :time => 20000000000, :otp_sha1 => '65353130',
  },
]


seed = '3132333435363738393031323334353637383930'
time_step = 30

test_data.each do |data|
  to = 0
  test_time = data[:time]
  t = (test_time / time_step).floor

  otp = generate_otp seed, t, 8, 'hmacsha1'

  puts otp == data[:otp_sha1] ? 'OK' : 'NG'
end

