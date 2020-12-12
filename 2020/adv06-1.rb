#!/usr/bin/env ruby

#NOTE must add empty line do the end of the input

questions = ('a'..'z').to_a
count = 0

#set values for first iteration
answered = []

ARGF.each do |line|
  line =  line.strip

  if line.empty?
    #add to count
    count += (questions & answered).size
    #reset values for next group
    answered = []
  else
    answered += line.chars
  end

end

puts count
