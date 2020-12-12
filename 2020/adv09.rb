#!/usr/bin/env ruby

input = ARGF.readlines.map(&:to_i)

#sw = sliding window
sw, msg = input[...25].map { |e| [e,true] }.to_h, input[25..]
#sw, msg = input[...5].map { |e| [e,true] }.to_h, input[5..]

#part 1
invalid = msg.drop_while do |e|
  if sw.keys.filter{ |i| i+i != e && sw[e-i] }.any?
    #add new element, remove oldest
    #NOTE does not work with repeated numbers in the sliding window "whoops"
    sw.shift
    sw[e] = [e, true]
  end
end.first

puts "Part 1: #{invalid}"

#part 2
for i in 0...input.size
  sum = 0
  nv = input[i..].take_while{ |e| sum += e if sum < invalid }
  if sum == invalid
    puts "Part 2: #{nv.min + nv.max}"
    break
  end
end

#alternative that is hard to read, long, and slow, but hey, it fits in one line
p input[(0...input.size).to_a.combination(2).to_a.keep_if { |e| e.first < e.last }.map{|e| e.first...e.last}.drop_while {|e| input[e].sum != invalid }.first].minmax.sum
