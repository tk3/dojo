require 'net/http'
require 'uri'

class Wakatime
  attr_accessor :api_key

  #
  # API document
  # - WakaTime API Docs https://wakatime.com/developers#summaries
  #
  WAKATIME_SUMMARIES_URL = 'https://wakatime.com/api/v1/users/current/summaries'

  def summaries(params = {})
    uri = URI.parse(WAKATIME_SUMMARIES_URL)
    uri.query = URI.encode_www_form(params)

    req = Net::HTTP::Get.new(uri)
    # ref. WakaTime API Docs https://wakatime.com/developers#authentication
    req.basic_auth("", @api_key)

    https = Net::HTTP.new(uri.host, uri.port)
    https.use_ssl = true
    https.verify_mode = OpenSSL::SSL::VERIFY_PEER

    res = https.request(req)
    res.body
  end
end

