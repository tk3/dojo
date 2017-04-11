#!/usr/bin/env ruby

#puts ENV['CLIENT_ID']

require 'faraday'
require 'faraday_middleware'

client_id = ENV['CLIENT_ID']
client_secret = ENV['CLIENT_SECRET']
url = 'https://typetalk.in'

# b.response :json, :content_type => /\bjson$/
conn = Faraday.new(url: url) do |faraday|
  faraday.request :json
  faraday.response :json
  faraday.adapter Faraday.default_adapter
end

# 
r = conn.post do |req|
  req.url '/oauth2/access_token'
  req.body = { :client_id => client_id,
               :client_secret => client_secret,
               :grant_type => "client_credentials",
               :scope => "my,topic.read,topic.post"}
end
if r.status == 200
  access_token = r.body['access_token']
  refresh_token = r.body['refresh_token']
  conn.authorization :Bearer, r.body['access_token']
end

r = conn.get do |req|
  req.url '/api/v1/profile'
end

p r.body

