#!/usr/bin/env ruby

require "rexml/document"

doc = REXML::Document.new(File.read("xxxx"))

def foo(elements, depth = 1)
  data = {}
  elements.each do |e|
#   puts "%s%s" % [" " *depth,  e.name]
    if e.has_elements?
      val = foo(e.elements, depth + 1)
      data[e.name] = val
    end
    if e.has_text? && !e.text.strip.empty?
      data[e.name] = e.text
#     puts "%s%s" % [" " * (depth + 1),  e.text]
    end
  end
  data
end

v = foo doc.elements
pp v

