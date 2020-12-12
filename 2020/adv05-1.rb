#!/usr/bin/env ruby

def conv(string)
  row = 8 * string[..-4].tr('FB','01').to_i(2)
  column = string[-4..].tr('LR','01').to_i(2)
  return row + column
end

ids = ARGF.to_a.map{ |e| conv e }.sort
puts "part1: " + ids.last.to_s
filled = (ids.first..ids.last).to_a
puts "part2: " + ( filled-ids ).first.to_s
