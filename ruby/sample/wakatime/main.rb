#!/usr/bin/env ruby

require 'dotenv'
require 'net/http'
require 'uri'
require 'date'
require 'fileutils'

Dotenv.load

#client_app_id = ENV['WAKATIME_APP_ID']
#client_app_secret = ENV['WAKATIME_APP_SECRET']

#
# ref. https://wakatime.com/settings/api-key
#
api_key = ENV['WAKATIME_API_KEY']

output_path = "#{ENV['HOME']}/var/wakatime"

#
# API document
# - WakaTime API Docs https://wakatime.com/developers#summaries
#
wakatime_summaries_url = 'https://wakatime.com/api/v1/users/current/summaries'

#1.times {|i|
6.times {|i|
  target_date = Date.today.prev_day(i + 1)
  date_str = target_date.strftime("%Y-%m-%d")

  puts date_str

  uri = URI.parse(wakatime_summaries_url)
  params = {:start => date_str, :end => date_str}
  uri.query = URI.encode_www_form(params)

  req = Net::HTTP::Get.new(uri)
  # ref. WakaTime API Docs https://wakatime.com/developers#authentication
  req.basic_auth("", api_key)

  https = Net::HTTP.new(uri.host, uri.port)
  https.use_ssl = true
  https.verify_mode = OpenSSL::SSL::VERIFY_PEER

  res = https.request(req)

  output_dir = "#{output_path}/#{target_date.year}/"
  output_file = "#{date_str}.json"

  FileUtils.mkdir_p(output_dir)
  File.write("#{output_dir}/#{output_file}", res.body)

  sleep(1)
}

exit 0


