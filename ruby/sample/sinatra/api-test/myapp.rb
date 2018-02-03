#!/usr/bin/env ruby

require 'sinatra'
require 'json'


def print_client_information(request, params)
  r = ""

  r << "client information ----\n"
  headers = request.env.select {|key, val| !key.match("[A-Z].*").nil?}
  headers.each do |key, val|
    r << "#{key}: #{val}\n"
  end

  r << "query string ----\n"
  params.each do |key, val|
    r << "#{key}: #{val}\n"
  end

  if request.env["sinatra.route"].start_with? "POST"
    request.body.rewind  # in case someone already read it
    r << "body ----\n"
    r << request.body.read
  end

  r
end

get '/echo' do
   print_client_information request, params
end

post '/echo' do
   print_client_information request, params
end

get '/json' do
  content_type 'application/json;charset=utf-8'
  { 
    id: 5,
    name: "foo bar", 
    created: "2008-07-06T15:00:00Z",
  }.to_json
end

get '/foo' do
  status 418
  headers \
    "Allow"   => "BREW, POST, GET, PROPFIND, WHEN",
    "Refresh" => "Refresh: 20; http://www.ietf.org/rfc/rfc2324.txt"
  body "I'm a tea pot!"
end

