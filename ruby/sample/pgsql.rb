#!/usr/bin/env ruby

class Pgbot
  def initialize
	end

	def startup(params)
		msg = ""
		params.each do |k, v|
			msg = msg + "#{k}\0#{v}\0"
    end

		return [msg.length + 4 + 4 + 1].pack("N") +
			[196608].pack("N") +
			[msg].pack("a*") + "\0"
	end

	def query(sql)
		return "Q" +
			[sql.length + 4 + 1].pack("N") +
			sql + "\0"
	end

	def terminate
		return "X" + [4].pack("N")
	end

	def parse(msg)
	end
end

params = {
  :user => 'dbuser',
  :database => 'testdb',
  :application_name => 'psql',
  :client_encoding => 'UTF8'
}

pg = Pgbot.new

requests = []
requests << pg.startup(params)
requests << pg.query("select * from bookshelf;")
requests << pg.terminate

require "socket"

sock = TCPSocket.open("localhost", 5434)

i = 0
while true
  rs, ws, = IO.select([sock], [sock], nil, 0.5)
  if rs[0]
		res = ''
  	r = sock.read(1)
		buf = sock.read(4)
		break  if buf.nil?
		res << r
		res << buf

		len = buf.unpack("N")[0]
		r = sock.read(len - 4)
		res << r

		p res
	elsif ws[0]
    sock.write requests[i]

		puts ">>>>>>>>>>>>>>>>"
    p requests[i]

		i += 1
  end
end

sock.close

