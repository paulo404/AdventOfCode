#!/usr/bin/env ruby

input = ARGF.readlines.map(&:strip)
init_bag = "shiny gold"

#part 1
bag_tree = input.map{ |s| a = s.split(/ bag\D*\d*[ \.]/); [a.first, a[1..]] }.to_h
new_bags = bags = [init_bag]

loop do
  bags = new_bags
  bag_tree.each_pair do |k,v|
    new_bags |= (new_bags & v).empty? ? [] : [k]
  end
  break if bags.size == new_bags.size
end

#count doesn't include initial bag
puts "Part 1: #{bags.size - 1}"


#part 2

# create hash with count
# hash [k=bag, v=[count,bag]]
bag_tree = input.map do |s|
  #remove everything but number of bags and bag name
  a = s.split(/ bag\D*[ \.]/);

  #map s into key,values
  key = a.first
  value = a[1..].map do |e|
    ind = e.index(' ');
    [ e[...ind].to_i, e[ind+1..] ]
  end
  [key, value]

  #create hash
end.to_h

def count_bags(bag,h)
  if h[bag].empty?
    1
  else
    1 + h[bag].map{ |v| v.first * count_bags(v.last, h) }.reduce(:+)
  end
end

puts "Part 2: #{ count_bags(init_bag, bag_tree) - 1 }"
