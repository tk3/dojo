#!/usr/bin/env ruby

require 'sql-parser'

parser = SQLParser::Parser.new

ast = parser.scan_str('SELECT * FROM users WHERE id = 1')


require "pp"

pp ast

