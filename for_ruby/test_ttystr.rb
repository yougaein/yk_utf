#!/usr/bin/env ruby

require 'Yk/TTYStr'

s = IO.read("test.txt")
s = "\x00" + s
ts = Yk::TTYStr.new(s)
p s
i = 0
#h = ts.height 25, 8
#p h
ts.each_line 25, 8, "ネイティブ", Yk::TTYStr::BgCyan | Yk::TTYStr::FgBlack do |ln, j|
	print "#{i}" + " " + ln + "|#{j}"
	print "\n"
	i += 1
	#if i > 50
	#	break
	#end
end

