exit(0) if ARGV.length < 1

puts "PLAIN : " + ARGV[0]
puts "MD5   : " + Base64::encode(Digest::MD5.digest(ARGV[0]))
puts "SHA1  : " + Base64::encode(Digest::SHA1.digest(ARGV[0]))
puts "SHA256: " + Base64::encode(Digest::SHA256.digest(ARGV[0]))
puts "SHA384: " + Base64::encode(Digest::SHA384.digest(ARGV[0]))
puts "SHA512: " + Base64::encode(Digest::SHA512.digest(ARGV[0]))
