#!/usr/bin/env ruby

require 'mkmf'

dir_config('TTYStr', "/usr/local")
have_library("stdc++")
have_library("boost_regex")
have_library("ykUTF")
$CXXFLAGS += " -O3 -std=c++1y"
create_makefile("Yk/TTYStr")
