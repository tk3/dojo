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
          opts[:install][:path] = argvs[1]

          return false  unless opts[:install][:path]

          true
        },
        :remove => lambda {|opts, argvs|
          puts ">> remove"
          opts[:remove] = {}
          opts[:remove][:app_name] = argvs[1]

          return false  unless opts[:remove][:app_name]

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
      self.install(arg[:install])  unless arg[:install].nil?
      self.remove(arg[:remove])  unless arg[:remove].nil?

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

      yaml["installed"].keys.each do |app_name|
        puts "    #{app_name}"
      end
    end

    def install(options)
      path = options[:path]
      puts "install> path=#{path}"

      src_files = Dir.glob("#{path}/**/*")
      return  if src_files.empty?

      app_name = File.basename(path)
      puts "install> app_name=#{app_name}"

      tool_home = ENV["BUILRB_HOME"] || "#{ENV['HOME']}/.builrb"
      tool_db = "#{tool_home}/db"

      return  unless FileTest.exist?("#{tool_home}/db")

      yaml = YAML.load_file(tool_db)
      return  unless yaml.key?("config")
      install_dir = yaml["config"]["install_dir"] || "/usr/local"
      puts "install> install_dir=#{install_dir}"

      FileUtils.mkdir_p(install_dir)  unless FileTest.directory?(install_dir)

      return  if check_if_already_installed(src_files, install_dir) == false

      link_files(src_files, install_dir)

      yaml["installed"][app_name] = {}
      yaml["installed"][app_name]["files"] = src_files

      File.open("#{tool_home}/db", "w") do |fout|
        YAML.dump(yaml, fout)
      end
    end

    def check_if_already_installed(files, install_dir)
      base = File.dirname(files[0])

      files.all? do |f|
        if FileTest.directory?(f)
          true
        else
          n = f.sub(/^#{base}/, '')
          if FileTest.exist?("#{install_dir}#{n}")
            false
          else
            true
          end
        end
      end
    end

    def link_files(files, install_dir)
      base = File.dirname(files[0])

      files.each do |f|
        n = f.sub(/^#{base}/, '')
        if FileTest.directory?(f)
          FileUtils.mkdir_p("#{install_dir}#{n}")
          puts "mkdir_p: #{install_dir}#{n}"
        else
          FileUtils.ln_s(f, "#{install_dir}#{n}")
          puts "ln: #{f} -> #{install_dir}#{n}"
        end
      end
    end

    def remove(options)
      app_name = options[:app_name]
      puts "remove> app_name=#{app_name}"

      tool_home = ENV["BUILRB_HOME"] || "#{ENV['HOME']}/.builrb"
      tool_db = "#{tool_home}/db"

      return  unless FileTest.exist?("#{tool_home}/db")

      yaml = YAML.load_file(tool_db)
      return  unless yaml.key?("config")
      install_dir = yaml["config"]["install_dir"] || "/usr/local"
      puts "remove> install_dir=#{install_dir}"

      return  unless yaml.key?("installed")
      return  unless yaml["installed"].key?(app_name)
      return  unless yaml["installed"][app_name].key?("files")

      src_files = yaml["installed"][app_name]["files"]

      return  if check_if_link_files_exist(src_files, install_dir) == false

      remove_link_files(src_files, install_dir)

      yaml["installed"].delete(app_name)

      File.open("#{tool_home}/db", "w") do |fout|
        YAML.dump(yaml, fout)
      end
    end

    def check_if_link_files_exist(files, install_dir)
      base = File.dirname(files[0])

      files.all? do |f|
        if FileTest.directory?(f)
          true
        else
          n = f.sub(/^#{base}/, '')
          FileTest.symlink?("#{install_dir}#{n}")
        end
      end
    end

    def remove_link_files(files, install_dir)
      base = File.dirname(files[0])

      files.each do |f|
        n = f.sub(/^#{base}/, '')
        if FileTest.symlink?("#{install_dir}#{n}")
#         puts "remove ... #{install_dir}#{n}"
          FileUtils.rm("#{install_dir}#{n}")
        end
      end
    end
  end
end


if $0 == __FILE__
  ENV["BUILRB_HOME"] = "conf"

  Builrb::Runner.new.start(ARGV.clone)
end

