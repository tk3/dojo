#!/usr/bin/env ruby

require "faraday"
require "nokogiri"

class Scraper
  class CAPACameranet
    def self.scrape(html)
      doc = Nokogiri::HTML.parse html

      ctx = {}
      data = []
      doc.css("#column").children.each do |e|
        case e.name
        when "h2"
          ctx[:title] = e.text
        when "h3"
          ctx[:area] = e.text
        when "p"
          ctx[:category] = e.text
        when "h4"
          ctx[:building_name] = e.text
          ctx[:building_url] = e.css("a").attr("href").value
        when "h6"
          ctx[:room_name] = e.text
        when "table"
          e.css("tr").each do |tr|
            td = tr.css "td"
            ctx[:exhibition_name] = td[0].text
            ctx[:held_for_days] = td[1].text
          end
          data << ctx.dup
        end
      end
      data
    end
  end
end

#u = "http://capacamera.net/exhibition/04.html"
#r = Faraday.get u
#html = r.body

html = File.read 'capacamera.cache.txt'

puts Scraper::CAPACameranet.scrape html


