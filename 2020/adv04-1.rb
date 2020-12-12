#!/usr/bin/env ruby

#NOTE must add empty line do the end of the input

req = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"]
fields = []
valid = 0

ARGF.each do |line|

  end_passport = line.strip.split do |field|
    fields << field.split(":").first
  end.empty?

  if end_passport
    fields |= [ "cid" ]
    valid += (req - fields).empty? ? 1 : 0
    fields = []
  end

end

puts valid
