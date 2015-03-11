class MD5Crypt
  def self.encrypt(password, hashed_hpassword)
    return ""  unless hashed_hpassword =~ /(\$.+\$)(.+)\$(.+)/
    key = $1
    salt = $2
    hash = $3

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

    self.encode64(final)
  end

  def self.encode64(s)
    ascii_tbl = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

    a = s.unpack("C*")

    tmp = []
    tmp << ((a[0]<<16) | (a[6]<<8) | a[12])
    tmp << ((a[1]<<16) | (a[7]<<8) | a[13])
    tmp << ((a[2]<<16) | (a[8]<<8) | a[14])
    tmp << ((a[3]<<16) | (a[9]<<8) | a[15])
    tmp << ((a[4]<<16) | (a[10]<<8) | a[5])
    tmp << ((1<<12) | a[11])

    r = ""
    tmp.each do |i|
      n = i
      while 0 < n
        r << ascii_tbl[n & 0x3f]
        n >>= 6
      end
    end
    r[0, 22]
  end
end

s = 'user02:$apr1$7EkYqIlu$zP0IETYrGdxLUFGzyvRQs1'
s = 'user01:$apr1$K5S1J1Cw$bT/200cBbpdVb6Hp8vu3W.'

p = s.split(":")
user = p[0]
r = MD5Crypto.encrypt("user01", p[1])
puts r

