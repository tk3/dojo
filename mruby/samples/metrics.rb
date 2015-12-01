
module Metrics
  class VmStat
    def run
      io = IO.popen('uname -a')
      io = IO.popen('vmstat -n 1')
      skip_line(io, 2)
      while true
        ret = IO.select([io], nil, nil, 0.5)
        if !ret.nil?
          begin
            puts ret[0][0].readline
          rescue EOFError
            # end of file reacheda
            break
          end
        end
      end
    end

    private
    def skip_line(io, n)
      i = 0
      while true
        begin
          ret = IO.select([io], nil, nil, 0.5)
          if !ret.nil?
            io.readline
            i += 1
            break  if n <= i
          end
        rescue EOFError
          # end of file reacheda
          break
        end
      end
    end
  end
end

#m = Metrics::VmStat.new.run

#memory.inact
#memory.active
col_names = %w(procs.r
procs.b
memory.swpd
memory.free
memory.buff
memory.cache
swap.si
swap.so
io.bi
io.bo
system.in
system.cs
cpu.us
cpu.sy
cpu.id
cpu.wa
cpu.st)
s = " 1  0      0  40380  35088 287560    0    0    20    63   22   52  1  0 99  0  0"

puts col_names
puts values = s.split(' ')

h = {}
col_names.length.times do |i|
  puts i
  h[col_names[i]] = values[i]
end
puts h
puts JSON::stringify(h)

#hash = Hash[col_names.zip values]
#puts JSON::stringify(hash)
#puts JSON.generate(hash)

