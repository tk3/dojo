#!/usr/bin/env ruby

require "socket"

class Memcached
  class Text
    # set key [flags] [exptime] length [noreply]
    def self.set(key, value, flags: false, expire: 0, noreply: false)
      "set %s 0 0 %d\r\n%s\r\n" % [key, value.length, value]
    end

    # get key1 [key2 .... keyn]
    def self.get(key)
      "get %s\r\n" % [key]
    end

    # delete key
    def self.delete(key)
      "delete %s\r\n" % [key]
    end

    # incr key value [noreply]
    def self.incr(key, value, noreply: false)
      "incr %s %s\r\n" % [key, value]
    end

    # decr key value [noreply]
    def self.decr(key, value, noreply: false)
      "decr %s %s\r\n" % [key, value]
    end
  end
end


sock = TCPSocket.open "localhost", 11211

sock.print Memcached::Text.set "foo", "1"
sock.flush
puts "resp: [#{sock.gets}]"

sock.print Memcached::Text.incr "foo", "10"
sock.flush
puts "resp: [#{sock.gets}]"

sock.print Memcached::Text.decr "foo", "3"
sock.flush
puts "resp: [#{sock.gets}]"

sock.print Memcached::Text.get "foo"
sock.flush
puts "resp: [#{sock.gets}]"

sock.print Memcached::Text.delete "foo"
sock.flush
puts "resp: [#{sock.gets}]"

sock.print Memcached::Text.get "foo"
sock.flush
puts "resp: [#{sock.gets}]"

sock.close

