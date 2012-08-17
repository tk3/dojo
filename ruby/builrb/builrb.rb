#!/bin/env ruby

require "fileutils"
require "yaml"

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
          puts ">> init"
          opts[:init] = {}
          opts[:init][:tool_home] = argvs[1]
          true
        },
        :config => lambda {|opts, argvs|
          puts ">> config"
          opts[:config] = {}
          opts[:config][:name] = argvs[1]
          opts[:config][:value] = argvs[2]

          return false  unless opts[:config][:name] && opts[:config][:value]

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

      self.init(arg[:init])  unless arg[:init].nil?
      self.config(arg[:config])  unless arg[:config].nil?
      self.list(arg[:list])  unless arg[:list].nil?

    end

    def init(options)
      tool_home = options[:tool_home] || ENV["BUILRB_HOME"] || "#{ENV['HOME']}/.builrb"
      puts ">> tool_home = #{tool_home}"

      FileUtils.mkdir_p(tool_home)  unless FileTest.exist?(tool_home)

      unless FileTest.exist?("#{tool_home}/db")
        yaml = {}
        yaml["version"] = "1.0"
        yaml["config"] = {}
        yaml["installed"] = {}

        File.open("#{tool_home}/db", "w") do |fout|
          YAML.dump(yaml, fout)
        end
      end

      true
    end

    def config(options)
#     puts "config: #{options[:name]}=#{options[:value]}"

      tool_home = ENV["BUILRB_HOME"] || "#{ENV['HOME']}/.builrb"
      tool_db = "#{tool_home}/db"

      return  unless FileTest.exist?("#{tool_home}/db")

      yaml = YAML.load_file(tool_db)

      yaml["config"] = {}  unless yaml.key?("config")

      yaml["config"][options[:name]] = options[:value]

      File.open("#{tool_home}/db", "w") do |fout|
        YAML.dump(yaml, fout)
      end
    end

    def list(options)
      tool_home = ENV["BUILRB_HOME"] || "#{ENV['HOME']}/.builrb"
      tool_db = "#{tool_home}/db"

      return  unless FileTest.exist?("#{tool_home}/db")

      yaml = YAML.load_file(tool_db)

      return  unless yaml.key?("installed")

      yaml["installed"].keys.each do |appname|
        puts "    #{appname}"
      end
    end

    def install(path)
      src_files = Dir.glob("#{path}/**/*")
      appname = File.basename(path)
    end
  end
end


if $0 == __FILE__
  ENV["BUILRB_HOME"] = "conf"

  Builrb::Runner.new.start(ARGV.clone)
end

