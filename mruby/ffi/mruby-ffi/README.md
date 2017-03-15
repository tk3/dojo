# mruby-digest-ffi

Message Digest class

# Example

```
md5 = Digest::MD5.new
md5.update "1"
puts md5.hexdigest  # => "c4ca4238a0b923820dcc509a6f75849b"
puts md5.hexdigest == md5.digest.bytes.map{|c| "%02x" % c}.join # => true
```

# Configuration

```
  MRuby::Build.new do |conf|
    ...
    conf.gem :github => 'qtkmz/mruby-digest-ffi'
    ...
  end
```

# License

The MIT License (MIT)
Copyright (c) 2016 qtakamitsu

