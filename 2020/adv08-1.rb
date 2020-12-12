#!/usr/bin/env ruby

class Terminated < StandardError; end
class EnteredLoop < StandardError; end

class Program
  attr_accessor :pc, :acc

  def initialize(source_code)
    @pc = 0
    @acc = 0
    @prog = source_code
    @visited = Array.new
  end

  def run()
    comm = @prog[@pc]
    @visited[@pc] = true

    #execute command
    case comm.first
    when "nop"
    when "acc"
      @acc += comm[1]
    when "jmp"
      @pc += comm[1] - 1
    else
      raise "Unsupported command: #{comm}"
    end

    @pc += 1

    #end prog
    raise Terminated if end?
    raise EnteredLoop if @visited[pc]
  end

  def end?()
    @pc >= @prog.size
  end
end

input = ARGF.readlines.map(&:split).map { |x| [x.first, x.last.to_i] }

#part 1
prog = Program.new input

loop do
  begin
    prog.run
  rescue EnteredLoop
    break
  end
end

puts "Part 1: #{prog.acc}"

#part 2
switch = { "jmp" => "nop", "nop" => "jmp" }

#change input until successful exit
input.each_index do |i|
  #change command
  if input[i].first != "acc"
    input[i][0] = switch[input[i][0]]

    #run on new input
    begin
      prog = Program.new input
      while true
        prog.run
      end
    rescue EnteredLoop
      #switch back
      input[i][0] = switch[input[i][0]]
    rescue Terminated
      puts "Part 2: #{prog.acc}"
      exit
    end
  end
end
