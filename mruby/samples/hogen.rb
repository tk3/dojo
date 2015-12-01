
def capture(stream)
  begin
  	stream = stream.to_s
	  eval "$#{stream} = StringIO.new"
	  yield
	  result = eval("$#{stream}").string
	ensure
	  eval("$#{stream} = #{stream.upcase}")
	end

	result
end

class Hogen
  @@variables = {}

	def self.method_missing(symbol, *args)
		if symbol == :start
			run
			return
		end

		@@variables[symbol] = {}  unless @@variables.key?(symbol)
		@@variables[symbol] = args
	end

private
  def self.run(argv = ARGV)
		task = self.new
		cmd = ARGV[0] || ""
	  if !task.respond_to?(cmd.to_sym)
			$stderr.puts %Q(Could not find command "#{cmd}".)
			return
		end

		task.send(cmd.to_sym, *(argv.dup.drop(1)))
		#task.send(cmd.to_sym, argv.drop(1).flatten)
		puts "run >> #{cmd}"
  rescue ArgumentError => e
    $stderr.puts %Q(ERROR: "#{__FILE__} #{cmd}" was called with arguments #{argv})
	end
end

class MyCLI < Hogen
	desc "hello NAME", "say hello to NAME"
  def hello(name)
    puts "Hello #{name}"
  end
end

MyCLI.start(ARGV)

__END__
class Test1 < Hogen
end

