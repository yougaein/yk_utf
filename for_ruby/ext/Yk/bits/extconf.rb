#!/usr/bin/env ruby

require 'mkmf'

dir_config('TTYStr')
have_library("stdc++")
have_library("ykUTF")
have_library("boost_regex")
$CXXFLAGS += " -O3 -std=c++1y "

create_makefile("Yk/bits/TTYStr")
