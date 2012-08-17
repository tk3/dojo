#!/bin/env ruby

module Builrb
  class Argv
    def initialize(options = {})
      @options = options
    end

    def [](key)
      @options[key]
    end

    def self.parse(argvs)
      option_spec = {
        :init => lambda {|opts, argvs|
          puts ">> list"
          opts[:init] = {}
          true
        },
        :list => lambda {|opts, argvs|
          puts ">> list"
          opts[:list] = {}
          true
        },
        :install => lambda {|opts, argvs|
          puts ">> install"
          opts[:install] = {}
          true
        },
        :remove => lambda {|opts, argvs|
          puts ">> remove"
          opts[:remove] = {}
          true
        },
      }

      options = {}

      return nil  if argvs.length < 1
      return nil  unless option_spec.key?(argvs[0].to_sym)
      return nil  unless option_spec[argvs[0].to_sym].call(options, argvs)

      return Builrb::Argv.new(options)
    end
  end

  class Runner
    def initialize
    end

    def start(argv)
      arg = Builrb::Argv.parse(argv)
      return  if arg.nil?

      unless arg[:init].nil?
        self.init
      end

    end

    def init
      require "yaml"

      ENV["BUILRB_HOME"] = "conf"
      tool_home = ENV["BUILRB_HOME"] || "#{ENV['HOME']}/.builrb"

      FileUtils.mkdir_p(tool_home)  unless FileTest.exist?(tool_home)

      unless FileTest.exist?("#{tool_home}/db")
        yaml = {}
        yaml["version"] = "1.0"
        yaml["installed"] = {}

        File.open("#{tool_home}/db", "w") do |fout|
          YAML.dump(yaml, fout)
        end
      end

      true
    end
  end
end


if $0 == __FILE__
  Builrb::Runner.new.start(ARGV.clone)
end

