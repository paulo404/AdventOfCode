#!/usr/bin/env ruby

init = ARGF.readlines.map(&:strip).map(&:chars)
#part 1
def inside(pos, grid)
  ny, nx = pos
  ny >= 0 && ny < grid.size && nx >= 0 && nx < grid.first.size
end

countAdj = Proc.new do |pos, delta, grid|
  y,x = pos
  dx, dy = delta
  nx, ny = x+dx, y+dy
  inside([ny, nx], grid) && grid[ny][nx] == "#" && !(nx == x && ny == y) ? 1 : 0
end

def updateRule(pos, grid, countFunc, emptyThresh)
  y, x = pos
  p adj = (-1..1).to_a.repeated_permutation(2).map{ |d| countFunc.call(pos,d,grid) }
  adj = adj.sum
  v = grid[y][x]

  case v
  when "." then "."
  when "L"
    adj == 0 ? "#" : v
  when "#"
    adj >= emptyThresh ? "L" : v
  end
end

def run(init, f, emptyThresh=4)
  every_pos = (0...init.size).to_a.product( (0...init.first.size).to_a )

  old = init.map(&:dup)
  new = old.map(&:dup)
  loop do
    every_pos.each { |pos| y,x = pos ; new[y][x] = updateRule(pos,old, f, emptyThresh) }
    #puts new.map(&:join).map { |s| s.tr(".L#"," .#") }.join("\n")
    break if old == new
    old = new.map(&:dup)
  end
  new
end

#finished = run(init, countAdj)
#occupied = finished.map{ |r| r.tally["#"] }.compact.sum
#puts "Part 1: #{occupied}"

#part 2

def countSeen(pos, delta, grid)
  y,x = pos
  dx, dy = delta
  nx, ny = x+dx, y+dy

  return 0 if (dx == 0 && dy == 0)

  loop do
    if ! inside([ny, nx], grid)
      return 0
    end
    if grid[ny][nx] == "L"
      return 0
    end
    if grid[ny][nx] == "#"
      return 1
    end
    nx, ny = nx+dx, ny+dy
  end
end

def updateRule2(pos, grid)
  y, x = pos
  adj = (-1..1).to_a.repeated_permutation(2).map{ |d| countSeen(pos,d,grid) }.sum
  v = grid[y][x]

  case v
  when "." then "."
  when "L"
    adj == 0 ? "#" : v
  when "#"
    adj >= 5 ? "L" : v
  end
end

def run2(init)
  every_pos = (0...init.size).to_a.product( (0...init.first.size).to_a )

  old = init.map(&:dup)
  new = old.map(&:dup)
  loop do
    every_pos.each { |pos| y,x = pos ; new[y][x] = updateRule2(pos,old) }
    #puts new.map(&:join).map { |s| s.tr(".L#"," .#") }.join("\n")
    break if old == new
    old = new.map(&:dup)
  end
  new
end

#p adj = (-1..1).to_a.repeated_permutation(2).map{ |d| countSeen.call(pos,d,init) }

finished = run2(init)
occupied = finished.map{ |r| r.tally["#"] }.compact.sum
puts "Part 2: #{occupied}"
