#!/usr/bin/env ruby

require "nokogiri"

class Scraper
  class CAPACameranet
    def self.scrape(html)
      doc = Nokogiri::HTML.parse html

      ctx = {}
      data = []

      doc.css("#main .entry-content").children.each do |e|
        case e.name
        when /h2/
          ctx = {}
          ctx[:area] = e.text
        when /h3/
          ctx[:category] = e.text
        when /section/
          ctx[:name] = e.css("div.place h4").text
          ctx[:url] = e.css("div.place li:nth-of-type(1) a")[0].attr("href")
          ctx[:map] = e.css("div.place li:nth-of-type(2) a")[0].attr("href")
          ctx[:description] = e.css("div.place p").text.strip

          # exhibition
          e.css("> ul li").each do |exhibition|
            ctx[:exhibition_title] = exhibition.css("div.date").text
            ctx[:exhibition_period] = exhibition.css("p").text

            data << ctx.dup
          end
        end
      end

      data
    end
  end
end


if __FILE__ == $0

  require "faraday"

  cache_file = "./capacamera.cache.txt"

  html = ""
  unless File.exist?(cache_file)
    url = "https://capa.getnavi.jp/exhibition/tokyo/"
    r = Faraday.get u
    html = r.body

    File.open(cache_file, "w") do |fout|
      fout.puts html
    end
  else
    html = File.read 'capacamera.cache.txt'
  end

  data = Scraper::CAPACameranet.scrape html

  data.each do |d|
    puts "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n" % [
          d[:area],
          d[:category],
          d[:name],
          d[:url],
          d[:map],
          d[:description],
          d[:exhibition_title],
          d[:exhibition_period]]
  end
end

