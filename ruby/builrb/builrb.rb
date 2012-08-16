#!/bin/env ruby

module Builrb
  class Argv
    def initialize(options = {})
      @options = options
    end

    def self.parse(argvs)
      option_spec = {
        :init => lambda {|opts, argvs|
          puts ">> list"
          opts[:name] = argvs[1]
          false
        },
        :list => lambda {|opts, argvs|
          puts ">> list"
          opts[:name] = argvs[1]
          false
        },
        :install => lambda {|opts, argvs|
          puts ">> install"
        },
        :remove => lambda {|opts, argvs|
          puts ">> remove"
        },
      }

      options = {}

      return nil  if argvs.length < 1
      return nil  unless option_spec.key?(argvs[0].to_sym)
      p option_spec[argvs[0].to_sym].call(options, argvs)

      return self
    end
  end
end


if $0 == __FILE__
  p Builrb::Argv.parse(ARGV)
end

