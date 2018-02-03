#!/usr/bin/env ruby

require "oauth2"
require "dotenv"
require "json"

Dotenv.load

client = OAuth2::Client.new(
  ENV["CC_CLIENT_ID"],
  ENV["CC_CLIENT_SECRET"],
  {
    :site => 'https://typetalk.com/',
    :authorize_url => '/oauth2/authorize', 
    :token_url => '/oauth2/access_token'
  })

typetalk_scope_type = %w(topic.read topic.post topic.write topic.delete my)

token = client.client_credentials.get_token({:scope => typetalk_scope_type.join(',')})

response = token.get "/api/v1/profile"

data = JSON.parse response.response.body

puts data["account"]["name"]

