#!/usr/bin/env ruby

require 'dotenv'
require 'net/http'
require 'uri'
require 'date'
require 'fileutils'
require './wakatime'

Dotenv.load

#
# ref. https://wakatime.com/settings/api-key
#
api_key = ENV['WAKATIME_API_KEY']

output_path = "#{ENV['HOME']}/devel/g/tk3.data/wakatime"

#
# API document
# - WakaTime API Docs https://wakatime.com/developers#summaries
#
wakatime_summaries_url = 'https://wakatime.com/api/v1/users/current/summaries'

6.times {|i|
  target_date = Date.today.prev_day(i + 1)
  date_str = target_date.strftime("%Y-%m-%d")


  params = {:start => date_str, :end => date_str}
  client = Wakatime.new
  client.api_key = api_key
  summaries_data = client.summaries(params)


  output_dir = "#{output_path}/#{target_date.year}/"
  output_file = "#{date_str}.json"

  FileUtils.mkdir_p(output_dir)
  File.write("#{output_dir}/#{output_file}", summaries_data)


  sleep(1)
}

exit 0


