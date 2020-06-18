cmake_minimum_required(VERSION 3.1)
project(
	ykUTF_lib
    VERSION 0.1.0
    DESCRIPTION "Yk UTF library"
    LANGUAGES CXX
)
add_library(
	ykUTF
	SHARED 
	./src/canonicalCombiningClass.cpp
	./src/generalCategoryProperty.cpp
	./src/lowerCase.cpp
	./src/upperCase.cpp
	./src/cType.cpp                    
	./src/graphemeProperty.cpp         
	./src/regex_utf.cpp
	./src/decompData.cpp               
	./src/lineBreakProperty.cpp        
	./src/ttyWidth.cpp
	./src/unicodeStr.cpp
)
target_compile_features(ykUTF PRIVATE cxx_std_11)
target_include_directories(ykUTF INTERFACE ./include)
set(CMAKE_BUILD_TYPE Debug)
set_target_properties(
	ykUTF
    PROPERTIES
    VERSION ${PROJECT_VERSION}
)
