#!/usr/bin/env ruby

require "thor"

class MyCLI < Thor
  option :param1
  option :param2, :type => :boolean
  option :param3, :desc => "description", :banner => "banner text"
  option :param4, :default => "abcd"
  option :param5, :required => true
  option :param6, :aliases => "-x"
	option :param7, type: :numeric, :enum => [10, 20]
  desc "hello", "command description"
  def hello
    puts options
  end
end

MyCLI.start(ARGV)

