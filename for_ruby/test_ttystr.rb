#!/usr/bin/env ruby

require 'Yk/TTYStr'

s = IO.read("test.txt")
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

