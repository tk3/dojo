
def to_crypto(crypto)
  if crypto == 'hmacsha256'
    Digest::SHA256
  elsif crypto == 'hmacsha512'
    Digest::SHA512
  else
    # default or hmacsha1
    Digest::SHA1
  end
end

def generate_otp(key, time, return_digits, crypto)
  packed_time_fmt = '%%0%dX'%(return_digits * 2)
  packed_time = [packed_time_fmt%time].pack('H*')
  packed_key = [key].pack('H*')
  hash = Digest::HMAC.digest(packed_time, packed_key, to_crypto(crypto))

  offset = hash[hash.length - 1].unpack('C')[0] & 0xf

  bin = 
    ((hash[offset].unpack('C')[0] & 0x7f) << 24) |
    ((hash[offset + 1].unpack('C')[0] & 0xff) << 16) |
    ((hash[offset + 2].unpack('C')[0] & 0xff) << 8) |
    (hash[offset + 3].unpack('C')[0] & 0xff)

  otp = bin % (10 ** return_digits)

  otp_fmt = '%%0%dd'%return_digits
  otp = otp_fmt%otp
end

test_data = [
  {
    :time       => 59,
    :otp_sha1   => '94287082',
    :otp_sha256 => '46119246',
    :otp_sha512 => '90693936',
  },
  {
    :time       => 1111111109,
    :otp_sha1   => '07081804',
    :otp_sha256 => '68084774',
    :otp_sha512 => '25091201',
  },
  {
    :time       => 1111111111,
    :otp_sha1   => '14050471',
    :otp_sha256 => '67062674',
    :otp_sha512 => '99943326',
  },
  {
    :time       => 1234567890,
    :otp_sha1   => '89005924',
    :otp_sha256 => '91819424',
    :otp_sha512 => '93441116',
  },
  {
    :time       => 2000000000,
    :otp_sha1   => '69279037',
    :otp_sha256 => '90698825',
    :otp_sha512 => '38618901',
  },
  {
    :time       => 20000000000,
    :otp_sha1   => '65353130',
    :otp_sha256 => '77737706',
    :otp_sha512 => '47863826',
  },
]


# Seed for HMAC-SHA1 - 20 bytes
seed = '3132333435363738393031323334353637383930'
# Seed for HMAC-SHA256 - 32 bytes
seed32 = '3132333435363738393031323334353637383930' + '313233343536373839303132'
# Seed for HMAC-SHA512 - 64 bytes
seed64 = '3132333435363738393031323334353637383930' * 3 + '31323334'

time_step = 30

test_data.each do |data|
  to = 0
  test_time = data[:time]
  t = (test_time / time_step).floor

  otp = generate_otp seed, t, 8, 'hmacsha1'
  otp_256 = generate_otp seed32, t, 8, 'hmacsha256'
  otp_512 = generate_otp seed64, t, 8, 'hmacsha512'

  puts '========'
  puts otp == data[:otp_sha1] ? 'OK' : 'NG'
  puts otp_256 == data[:otp_sha256] ? 'OK' : 'NG'
  puts otp_512 == data[:otp_sha512] ? 'OK' : 'NG'
  puts '========'
end

