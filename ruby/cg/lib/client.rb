require "faraday"
require "faraday_middleware"
require "time"

class Client
  def initialize(host, api_key)
    @api_key = api_key
    @conn = Faraday.new(host) do |faraday|
      faraday.request :json
      faraday.response :json, :content_type => /\bjson$/
      faraday.adapter Faraday.default_adapter
    end
  end

  def get_myself
    r = @conn.get do |req|
      req.url "/api/v2/users/myself"
      req.params[:apiKey] = @api_key
    end
    r.body
  end

  def get_users
    r = @conn.get do |req|
      req.url "/api/v2/users"
      req.params[:apiKey] = @api_key
    end
    r.body
  end

  def get_activities(user_id, params = {})
    r = @conn.get do |req|
      req.url "/api/v2/users/#{user_id}/activities"
      req.params[:apiKey] = @api_key
      req.params[:count] = params[:count]  if params.key?(:count)
      req.params[:maxId] = params[:maxId]  if params.key?(:maxId)
    end
    r.body
  end
end