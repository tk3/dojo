
class Hogen
	def self.desc(usage, description)
		@previous_defined ||= []
		current_defined = instance_methods(false)
		diff = current_defined - @previous_defined
		if diff.length > 0 # TODO: 
			@command_config ||= {}
			@command_config[diff[0]] = @variables
	  	@variables = {}
		end
  	@variables ||= {}
	  @variables[:desc] = {:usage => usage, :description => description}
		@previous_defined = instance_methods(false)
	end

	def self.start(argv = ARGV)
		current_defined = instance_methods(false)
		diff = current_defined - @previous_defined
		if diff.length > 0 # TODO: 
			@command_config ||= {}
			@command_config[diff[0]] = @variables
		end

		cmd = ARGV[0] || ""
		if cmd.empty? || cmd == "help"
			print_help
			return 0
		end

		task = self.new
		if !task.respond_to?(cmd.to_sym)
			$stderr.puts %Q(Could not find command "#{cmd}".)
			return 1
		end

		task_argv = argv.dup.drop(1)
		task.send(cmd.to_sym, *(task_argv))
	rescue ArgumentError => e
		$stderr.puts %Q(ERROR: "#{__FILE__} #{cmd}" was called with arguments #{task_argv})
	end

private
	def self.print_help
		puts "Commands:"
#	@@variables.each_key do |key|
#	  puts "  #{__FILE__} #{desc[0]}  # #{des[1]}"
#	end
		puts @command_config
		@command_config.each_key do |key|
			puts key
			puts %Q(  #{__FILE__} #{desc[:name]})
		end

		puts @command_config
		puts "  #{__FILE__} help [COMMAND]  # Describe available commands or one specific command"
		puts ""
	end
end

class MyCLI < Hogen
	desc "hello NAME", "say hello to NAME"
	def hello(name)
		puts "Hello #{name}"
	end

	desc "foo NAME", "say hello to NAME"
	def foo(name)
		puts "Foo #{name}"
	end
end

MyCLI.start(ARGV)

__END__
class Test1 < Hogen
end

