#!/usr/bin/env ruby

require "oauth2"
require "dotenv"
require "json"

Dotenv.load

client = OAuth2::Client.new(
  ENV["CLIENT_ID"],
  ENV["CLIENT_SECRET"],
  {
    :site => 'https://typetalk.com/',
    :authorize_url => '/oauth2/authorize', 
    :token_url => '/oauth2/access_token'
  })

token = client.client_credentials.get_token({:scope => 'topic.read,topic.post,topic.write,topic.delete,my'})

r = token.get("/api/v1/profile")

j = JSON.parse r.response.body

puts j["account"]["name"]

