#!/usr/bin/env ruby

require './TTYStr'

s = IO.read("../../../../build/test.txt")
ts = Yk::TTYStr.new(s)
p s
i = 0
ts.each_line 25, 8, "ネイティブ", Yk::TTYStr::BgCyan | Yk::TTYStr::FgBlack do |ln|
	print "#{i}" + " " + ln
	print "\n"
	i += 1
	#if i > 50
	#	break
	#end
end

