
def to_crypto_type(crypto)
  if crypto == 'sha256'
    Digest::SHA256
  elsif crypto == 'sha512'
    Digest::SHA512
  else
    # default or hmacsha1
    Digest::SHA1
  end
end

def generate_otp(key, time, return_digits, crypto)
  packed_time_fmt = '%%0%dX'%16
  otp_fmt = '%%0%dd'%return_digits

  packed_time = [packed_time_fmt%time].pack('H*')
  packed_key = [key].pack('H*')
  digest = Digest::HMAC.digest(packed_time, packed_key, to_crypto_type(crypto))
  digest_bin = digest.unpack('C*')
  offset = digest_bin[-1] & 0xf

  otp_bin =
    ((digest_bin[offset] & 0x7f) << 24) |
    ((digest_bin[offset + 1] & 0xff) << 16) |
    ((digest_bin[offset + 2] & 0xff) << 8) |
    (digest_bin[offset + 3] & 0xff)

  otp_fmt%(otp_bin % (10 ** return_digits))
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
t0 = 0

puts '+-------------+----------+--------+-------+'
puts '+  Time(sec)  +   TOTP   +  Mode  + Expect+'
puts '+-------------+----------+--------+-------+'

test_data.each do |data|
  time_counter = ((data[:time] - t0) / time_step).floor

  otp = generate_otp seed, time_counter, 8, 'sha1'
  otp256 = generate_otp seed32, time_counter, 8, 'sha256'
  otp512 = generate_otp seed64, time_counter, 8, 'sha512'

  puts "| %-11s | %s | %-6s | %-5s |"%[data[:time], otp, 'sha1', otp == data[:otp_sha1]]
  puts "| %-11s | %s | %-6s | %-5s |"%[data[:time], otp256, 'sha256', otp256 == data[:otp_sha256]]
  puts "| %-11s | %s | %-6s | %-5s |"%[data[:time], otp512, 'sha512', otp512 == data[:otp_sha512]]
  puts '+-------------+----------+--------+-------+'
end

