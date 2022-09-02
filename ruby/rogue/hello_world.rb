#!/usr/bin/env ruby

require "curses"

Curses.init_screen
begin
  s = "Hello World!"
  Curses.setpos(Curses.lines / 2, Curses.cols / 2 - (s.length / 2))
  Curses.addstr(s)
  Curses.curs_set(0)
  Curses.refresh
  Curses.getch
ensure
  Curses.close_screen
end

