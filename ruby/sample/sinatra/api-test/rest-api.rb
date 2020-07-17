#!/usr/bin/env ruby

require "sinatra"
require "json"

random = Random.new()

books = {}

get "/ping" do
	content_type :json
	{
		"status": "OK"
	}.to_json
end

get "/books" do
	status 200
	content_type :json
	{
		"id": books.keys
	}.to_json
end

post "/books" do
	content_type_header = request.env["CONTENT_TYPE"]
	if !content_type_header.include?("application/json")
		status 400
	 	content_type :json
		return {
			"error": "invalid content type"
		}.to_json
	end

	params = JSON.parse request.body.read
	if params["title"].nil? || params["author"].nil? || params["price"].nil?
		status 400
	 	content_type :json
		return {
			"error": "invalid parameters"
		}.to_json
	end

	book_id = random.rand(10000)

	books[book_id.to_s] = {}

	content_type :json
	{
		"id": book_id
	}.to_json
end

put "/books/:id" do |book_id|
	content_type_header = request.env["CONTENT_TYPE"]
	if !content_type_header.include?("application/json")
		status 400
		content_type :json
		return {
			"error": "invalid content type"
		}.to_json
	end

	params = JSON.parse request.body.read
	if params["title"].nil? || params["author"].nil? || params["price"].nil?
		status 400
		content_type :json
		return {
			"error": "invalid parameters"
		}.to_json
	end

	unless books.key?(book_id)
		status 404
		content_type :json
		return {
			"error": "not found. book_id = #{book_id}"
		}.to_json
	end

	content_type :json
	{
		"status": "OK"
	}.to_json
end

delete "/books/:id" do |book_id|
	content_type_header = request.env["CONTENT_TYPE"]
	if !content_type_header.include?("application/json")
		status 400
		content_type :json
		return {
			"error": "invalid content type"
		}.to_json
	end

	unless books.key?(book_id)
		status 404
		content_type :json
		return {
			"error": "not found"
		}.to_json
	end

	books.delete(book_id)

	content_type :json
	{
		"status": "OK"
	}.to_json
end

