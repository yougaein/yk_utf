cmake_minimum_required(VERSION 3.1)
project(
	ykUTF_lib_test
    VERSION 0.1.0
    DESCRIPTION "Yk UTF library test"
    LANGUAGES CXX
)
set(CMAKE_BUILD_TYPE Debug)
add_executable(test_utf_str test_utf_str.cpp)
target_compile_features(test_utf_str PRIVATE cxx_std_11)
target_link_libraries(test_utf_str ykUTF boost_regex)
