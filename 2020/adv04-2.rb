#!/usr/bin/env ruby

#NOTE must add empty line do the end of the input

req = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"]
ecl = ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]
count = 0

#set values for first iteration
fields = [], valid = true
ARGF.each do |line|

  #read passport fields
  end_passport = line.strip.split do |field|
    f = field.split(":")
    key, value = f[0], f[1]
    fields << key

    #check if field is valid
    v_int = value.to_i
    valid &&= case key
    when "byr" then (1920..2002).include? v_int
    when "iyr" then (2010..2020).include? v_int
    when "eyr" then (2020..2030).include? v_int
    when "hgt"
      case value
      when /cm$/ then (150..193).include? v_int
      when /in$/ then (59..76).include? v_int
      end
    when "hcl" then /^#[[:xdigit:]]{6}$/.match? value
    when "ecl" then ecl.include? value
    when "pid" then /^[[:digit:]]{9}$/.match? value
    when "cid" then true
    end
  end.empty?

  #check if passport is valid
  if end_passport
    fields |= [ "cid" ]
    count += ((req - fields).empty? && valid) ? 1 : 0
    fields = [], valid = true
  end

end

puts count
