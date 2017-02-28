#!/usr/bin/env ruby

require "thor"

class MyCLI < Thor
  desc "case1", "command description"
  option :param
  def case1
    puts options
  end

  desc "case2", "command description"
  option :param, :type => :boolean
  def case2
    puts options
  end

  desc "case3", "command description"
  option :param, :desc => "description", :banner => "banner text"
  def case3
    puts options
  end

  desc "case4", "command description"
  option :param, :default => "abcd"
  def case4
    puts options
  end

  desc "case5", "command description"
  option :param, :required => true
  def case5
    puts options
  end

  desc "case6", "command description"
  option :param, :aliases => "-x"
  def case6
    puts options
  end

  desc "case7", "command description"
  option :param, type: :numeric, :enum => [10, 20]
  def case7
    puts options
  end

  desc "case8", "command description"
  option :param #, :lazy_default => true
  def case8
    puts options
  end
end

MyCLI.start(ARGV)

