#!/usr/bin/env ruby

$input = [0] + ARGF.readlines.map(&:to_i).sort
$input << $input[-1] + 3

#Part 1
diff = [0,0,0,0]

for i in 0...$input.size-1
  diff[$input[i+1] - $input[i]] += 1
end


puts "Part 1: #{diff[1] * diff[3]}"


#Part 2
$ans = {}
$cfScratch = 0

def waysFrom(head)
  #dict
  return $ans[head] if $ans[head]
  #don't count values not in the array
  return 0 if not $input.index { |x| x == head }
  #base
  return 1 if  head == $input.last
  return 0 if  head > $input.last


  #general case
  $cfScratch += 1

  ways = (1..3).to_a.map { |i| waysFrom(head+i) }
  $ans[head] = ways.sum
  return ways.sum
end

puts "Part 2: #{waysFrom($input.first)}"
