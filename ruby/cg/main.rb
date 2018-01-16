#!/usr/bin/env ruby

require "thor"

$: << "./lib"
require "client.rb"

class MyCLI < Thor
  desc "crawl HOST_URL API_KEY USERID", "crawl"
  option :url, :required => true
  option :api_key, :required => true
  option :user_id, :required => true
  option :from
  def crawl
    require "date"

    if options[:from]
      from = Time.parse options[:from]
    else
      from = (Date.today << 3).to_time
    end

    user_id = options[:user_id]
    client = Client.new options[:url], options[:api_key]

    r = client.get_activities(user_id, {:count => 1})
    next_max_id = r.first["id"]
    c = Date.today.to_s

    while from <= Time.parse(c).localtime
      r = client.get_activities(user_id, {:count => 20, :maxId => next_max_id})
      r.each do |e|
        puts "#{e['id']},#{e['created']},#{e['type']}"
      end

      next_max_id = r.last["id"]
      c = r.last["created"]

      sleep 4
    end
  end

  desc "convert CSV_FILE", "convert csv file to contribute graph json"
  def convert(csv_file)
    require "csv"
    require "time"
    require "json"

    c = CSV.read csv_file
    d = c.map {|a|
      [a[0], Time.parse(Time.parse(a[1]).localtime.strftime("%Y%m%d")).to_i, a[2]]
    }.inject(Hash.new(0)){|hash, a| hash[a[1].to_s] += 1; hash}
    print "var data = #{JSON.dump(d)}"
  end

  desc "users", "list users"
  option :url, :required => true
  option :api_key, :required => true
  def users
    require "json"

    client = Client.new options[:url], options[:api_key]

    puts JSON.dump(client.get_users)
  end
end

MyCLI.start ARGV