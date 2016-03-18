#!/usr/bin/env ruby

require "thor"

class MyCLI < Thor
  desc "hello NAME", "say hello to NAME"
  options :from => :required, :yell => :boolean
  def hello(name)
  	output = []
	  output << "from: #{options[:from]}" if options[:from]
	  output << "Hello #{name}"
	  output = output.join("\n")
	  puts options[:yell] ? output.upcase : output
	end
end

MyCLI.start(ARGV)

