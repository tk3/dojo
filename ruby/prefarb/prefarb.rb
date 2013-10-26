#!/usr/bin/env ruby

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
#         puts ">> init"
          return false  unless argvs[1]

          opts[:type] = :init
          opts[:args][:install_path] = argvs[1]
          true
        },
        :config => lambda {|opts, argvs|
#         puts ">> config"
          return false  unless argvs[1] && argvs[2]

          opts[:type] = :config
          opts[:args][:name] = argvs[1]
          opts[:args][:value] = argvs[2]


          true
        },
        :list => lambda {|opts, argvs|
#         puts ">> list"
          opts[:type] = :list
          true
        },
        :install => lambda {|opts, argvs|
#         puts ">> install"
          return false  unless argvs[1]

          opts[:type] = :install
          opts[:args][:path] = argvs[1]

          true
        },
        :remove => lambda {|opts, argvs|
#         puts ">> remove"
          return false  unless argvs[1]

          opts[:type] = :remove
          opts[:args][:app_name] = argvs[1]

          true
        },
      }

      options = {:type => nil, :args => {}}

      return nil  if argvs.length < 1
      return nil  unless option_spec.key?(argvs[0].to_sym)
      return nil  unless option_spec[argvs[0].to_sym].call(options, argvs)

      return Builrb::Argv.new(options)
    end
  end

  class Config
    def initialize
      @yaml = {}
      @conf_file = "#{ENV['HOME']}/.prefarb"
    end

    def self.load
      conf = Config.new
      conf.load_file
      conf
    end

    def []=(key, value)
      @yaml["config"][key] = value
    end

    def [](key)
      @yaml["config"][key]
    end

    def list_apps
      @yaml["apps"]
    end

    def get_app(name)
      @yaml["apps"].key?(name) ? @yaml["apps"][name] : {}
    end

    def add_app(name, files)
      @yaml["apps"][name] = {}
      @yaml["apps"][name]["files"] = files
      @yaml["apps"][name]["date"] = DateTime.now
    end

    def remove_app(name)
      @yaml["apps"].delete(name)
    end

    def save
      File.open(@conf_file, "w") do |fout|
        YAML.dump(@yaml, fout)
      end
    end

    def load_file
      if FileTest.exist?(@conf_file)
        @yaml = YAML.load_file(@conf_file)
        # TODO: validate
      else
        yaml = {}
        yaml["version"] = "1.0"
        yaml["config"] = {}
        yaml["apps"] = {}

        File.open(@conf_file, "w") do |fout|
          YAML.dump(yaml, fout)
        end
        @yaml = yaml
      end
    end
  end

  class Runner
    def start(argv)
      arg = Builrb::Argv.parse(argv)
      raise ArgumentError  if arg.nil?

      case arg[:type]
      when :init
        self.init(arg[:args])
      when :config
        self.config(arg[:args])
      when :list
        self.list(arg[:args])
      when :install
        self.install(arg[:args])
      when :remove
        self.remove(arg[:args])
      else
      end

    end

    def init(options)
      install_path = File.expand_path(options[:install_path])

      if FileTest.exist?(install_path) && !FileTest.directory?(install_path)
        raise Errno::EEXIST
      end
      FileUtils.mkdir_p(install_path)

      conf = Config.load
      conf["install_path"] = install_path
      conf.save

      true
    end

    def config(options)
      true
    end

    def list(options)
      conf = Config.load
      conf.list_apps.keys.each do |app_name|
        puts "    #{app_name}"
      end
    end

    def install(options)
      path = options[:path]
      puts "install> path=#{path}"

      src_files = Dir.glob("#{path}/**/*")
      if src_files.empty?
        STDERR.puts "Error: cannot install files."
        return false
      end

      app_name = File.basename(path)
      puts "install> app_name=#{app_name}"

      conf = Config.load
      install_path = conf["install_path"]

      if install_path.start_with?(File.expand_path(path))
        STDERR.puts "Error: Overlap path."
        return false
      end

      unless conf.get_app(app_name).empty?
        STDERR.puts "Error: already installed."
        return false
      end

      unless check_if_already_installed(src_files, install_path)
        STDERR.puts "Error: already installed."
        return false
      end

      link_files(src_files, install_path)

      conf.add_app(app_name, src_files)
      conf.save

      return true
    end

    def check_if_already_installed(files, install_path)
      base = File.dirname(files[0])

      files.all? do |f|
        if FileTest.directory?(f)
          true
        else
          n = f.sub(/^#{base}/, '')
          if FileTest.exist?("#{install_path}#{n}")
            false
          else
            true
          end
        end
      end
    end

    def link_files(files, install_path)
      base = File.dirname(files[0])

      files.each do |f|
        n = f.sub(/^#{base}/, '')
        if FileTest.directory?(f)
          FileUtils.mkdir_p("#{install_path}#{n}")
          puts "mkdir_p: #{install_path}#{n}"
        else
          FileUtils.ln_s(f, "#{install_path}#{n}")
          puts "ln: #{f} -> #{install_path}#{n}"
        end
      end
    end

    def remove(options)
      app_name = options[:app_name]
      puts "remove> app_name=#{app_name}"

      conf = Config.load
      install_path = conf["install_path"]

      app_info = conf.get_app(app_name)
      if app_info.empty?
        STDERR.puts "Error: not installed."
        return false
      end

      src_files = app_info["files"]
      unless check_if_link_files_exist(src_files, install_path)
        STDERR.puts "Error: not installed."
        return false
      end

      remove_link_files(src_files, install_path)

      conf.remove_app(app_name)
      conf.save
    end

    def check_if_link_files_exist(files, install_path)
      base = File.dirname(files[0])

      files.all? do |f|
        if FileTest.directory?(f)
          true
        else
          n = f.sub(/^#{base}/, '')
          FileTest.symlink?("#{install_path}#{n}")
        end
      end
    end

    def remove_link_files(files, install_path)
      base = File.dirname(files[0])

      files.each do |f|
        n = f.sub(/^#{base}/, '')
        if FileTest.symlink?("#{install_path}#{n}")
#         puts "remove ... #{install_path}#{n}"
          FileUtils.rm("#{install_path}#{n}")
        end
      end
    end
  end
end


if $0 == __FILE__
  Builrb::Runner.new.start(ARGV.clone)
end

